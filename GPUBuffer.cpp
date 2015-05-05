#include <istream>
#include <iostream>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <fstream>
#include "GPUBuffer.hh"

GRand::GPUBuffer::GPUBuffer() : _vbo(0), _scene(NULL) {
}

GRand::GPUBuffer::GPUBuffer(const GPUBuffer& o_) : _vbo(o_._vbo) {
    if (_vbo == 0) {
	_vertexArray = o_._vertexArray;
    }
}

void GRand::GPUBuffer::operator=(const GPUBuffer& o_) {
    _vbo = o_._vbo;
    if (_vbo) {
	return;
    }
    _vertexArray = o_._vertexArray;
}

bool GRand::GPUBuffer::loadFile(std::string const &name) {
    Assimp::Importer importer;

    std::ifstream fin(name.c_str());
    if (!fin.fail()) {
	fin.close();
    } else {
	std::cout << "Couldn't open file: " << name << std::endl;
	return false;
    }
    _scene = importer.ReadFile(name.c_str(), aiProcessPreset_TargetRealtime_Quality | aiProcess_Triangulate);
    if (!_scene) {
	std::cout << importer.GetErrorString() << std::endl;
	return false;
    }
    getAllFaces(_scene, _scene->mRootNode);
    std::cout << "ea size once file loaded:" << _elementArray.size() << std::endl;
    return true;
}

void GRand::GPUBuffer::getAllFaces(const struct aiScene *sc, const struct aiNode* nd) {
    unsigned int n = 0;

    for (; n < nd->mNumMeshes; ++n) {
	const struct aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];
	unsigned int *faceArray;
	faceArray = (unsigned int *)malloc(sizeof(unsigned int) * mesh->mNumFaces * 3);
	if (_vertexArray.size() + mesh->mNumFaces * 6 > _vertexArray.capacity()) {
	    _vertexArray.reserve(_vertexArray.capacity() + mesh->mNumFaces * 6);
	}
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
//	    std::cout << i << ":" << mesh->mVertices[i].x << " " << mesh->mVertices[i].y << " " << mesh->mVertices[i].z << std::endl;
	    _vertexArray.push_back(mesh->mVertices[i].x);
	    _vertexArray.push_back(mesh->mVertices[i].y);
	    _vertexArray.push_back(mesh->mVertices[i].z);
	    //_vertexArray.push_back(mesh->mNormals[i].x);
	    //_vertexArray.push_back(mesh->mNormals[i].y);
	    //_vertexArray.push_back(mesh->mNormals[i].z);
	}
	//if (_elementArray.size() + mesh->mNumFaces > _elementArray.capacity()) {
	//    _elementArray.reserve(_elementArray.capacity() + mesh->mNumFaces);
	//}
	for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
	    const struct aiFace* face = &mesh->mFaces[t];
	    for (unsigned int i = 0; i < face->mNumIndices; i++) { // go through all vertices in face
		unsigned int tmp = face->mIndices[i];
		_elementArray.push_back(tmp);
	    }
	}
    }
    for (n = 0; n < nd->mNumChildren; ++n) {
	getAllFaces(sc, nd->mChildren[n]);
    }
}

void GRand::GPUBuffer::generateVBOAndVertexArray() {
    /*GLfloat vertices[] = {
	-0.5f,  0.5f, 0.f, // Top-left
	0.5f,  0.5f, 0.f, // Top-right
	0.5f, -0.5f, 0.f, // Bottom-right
	-0.5f, -0.5f, 0.f // Bottom-left
    };
    GLuint elements[] = {
    0, 1, 2, 18, 0, 2, 3, 4, 5, 19, 3, 5, 6, 7, 8, 20, 6, 8, 9, 10, 11, 21, 9, 11, 12, 13, 14, 22, 12, 14, 15, 16, 17, 23, 15, 17
    };*/
    if (_vbo) {
	glDeleteBuffers(1, &_vbo);
    }
    std::cout << "ea size on generate ebo:" << _elementArray.size() << std::endl;
    //_vertexArray = b_;
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertexArray.size() * sizeof(decltype(_vertexArray)::value_type), &(_vertexArray[0]), GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &_ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _elementArray.size() * sizeof(decltype(_vertexArray)::value_type), &(_elementArray[0]), GL_STATIC_DRAW);
    std::cout << "ELEMENT ARRAY:";
    for (std::vector<GLuint>::iterator it = _elementArray.begin(); it != _elementArray.end(); it++) {
	std::cout << *it << " ";
    }
    std::cout << std::endl;
    /*int i = 0;
    for (std::vector<GLfloat>::iterator it = _vertexArray.begin(); it != _vertexArray.end(); it++) {
	i++;
	std::cout << *it << " ";
	if (i % 3 == 0) {
	    std::cout << std::endl;
	}
    }*/
}

void GRand::GPUBuffer::setBuffer(const decltype(_vertexArray)& b_) {
    if (_vbo) {
	glDeleteBuffers(1, &_vbo);
    }
    _vertexArray = b_;
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertexArray.size() * sizeof(decltype(_vertexArray)::value_type), &_vertexArray[0], GL_STATIC_DRAW);
}

GRand::GPUBuffer::~GPUBuffer() {
}

void GRand::GPUBuffer::draw(GLenum drawStyle_) const noexcept {
    glEnableVertexAttribArray(0); // enable vertex shader parameter value
    glEnableVertexAttribArray(1); // enable normal shader parameter value
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(decltype(_vertexArray)::value_type), (void*)0);

    // when normal enabled
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(decltype(_vertexArray)::value_type), (void*)0); // vertex
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(decltype(_vertexArray)::value_type), 3 * sizeof(decltype(_vertexArray)::value_type)); //normal

    // with vertex color enabled
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(decltype(_vertexArray)::value_type), (void*)0); // vertex
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(decltype(_vertexArray)::value_type), 3 * sizeof(decltype(_vertexArray)::value_type)); // normal
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(decltype(_vertexArray)::value_type), 6 * sizeof(decltype(_vertexArray)::value_type)); // vertex color

    // draw the polygon with the shader on the OpenGL draw buffer
    //glDrawArrays(drawStyle_, 0, _vertexArray.size());
    //std::cout << "ea size:" << _elementArray.size() << std::endl;
    glDrawElements(drawStyle_, _elementArray.size(), GL_UNSIGNED_INT, 0);
    //glDrawElements(drawStyle_, 6, GL_UNSIGNED_INT, 0);
    //glDrawArrays(drawStyle_, 0, 4);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
