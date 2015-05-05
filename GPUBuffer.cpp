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
    return true;
}

void GRand::GPUBuffer::getAllFaces(const struct aiScene *sc, const struct aiNode* nd) {
    unsigned int n = 0;

    for (; n < nd->mNumMeshes; ++n) {
	const struct aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];
	unsigned int *faceArray;
	faceArray = (unsigned int *)malloc(sizeof(unsigned int) * mesh->mNumFaces * 3);
	unsigned int faceIndex = 0;
	if (_vertexArray.size() + mesh->mNumFaces * 6 > _vertexArray.capacity()) {
	    _vertexArray.reserve(_vertexArray.capacity() + mesh->mNumFaces * 6);
	}
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
	    //std::cout << i << ":" << mesh->mVertices[i].x << " " << mesh->mVertices[i].y << " " << mesh->mVertices[i].z << std::endl;
	    _vertexArray.push_back(mesh->mVertices[i].x);
	    _vertexArray.push_back(mesh->mVertices[i].y);
	    _vertexArray.push_back(mesh->mVertices[i].z);
	}
	if (_elementArray.size() + mesh->mNumFaces > _elementArray.capacity()) {
	    _elementArray.reserve(_elementArray.capacity() + mesh->mNumFaces);
	}
	for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
	    const struct aiFace* face = &mesh->mFaces[t];
	    for (unsigned int i = 0; i < face->mNumIndices; i++) { // go through all vertices in face
		//if (find(_index.begin(), _index.end(), face->mIndices[i]) == _index.end()) {
		//    int vertexIndex = face->mIndices[i]; // get group index for current index
		//    //_vertexArray.push_back(mesh->mNormals[vertexIndex].x);
		//    //_vertexArray.push_back(mesh->mNormals[vertexIndex].y);
		//    //_vertexArray.push_back(mesh->mNormals[vertexIndex].z);
		//    _vertexArray.push_back(mesh->mVertices[vertexIndex].x);
		//    _vertexArray.push_back(mesh->mVertices[vertexIndex].y);
		//    _vertexArray.push_back(mesh->mVertices[vertexIndex].z);
		//    _index.push_back(face->mIndices[i]);
		//    //std::cout << vertexIndex << ":" << mesh->mVertices[vertexIndex].x << " " << mesh->mVertices[vertexIndex].y << " " << mesh->mVertices[vertexIndex].z << std::endl;
		//}
		_elementArray.push_back(face->mIndices[i]);
		//std::cout << "ea:" << face->mIndices[i] << std::endl;
	    }
	    //memcpy(&faceArray[faceIndex], face->mIndices,3 * sizeof(unsigned int));
	    //faceIndex += 3;
	}
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->mNumFaces * 3, faceArray, GL_STATIC_DRAW);
    }
    for (n = 0; n < nd->mNumChildren; ++n) {
	getAllFaces(sc, nd->mChildren[n]);
    }
}

void GRand::GPUBuffer::generateVBOAndVertexArray() {
    GLfloat vertices[] = {
	-0.5f,  0.5f, // Top-left
	0.5f,  0.5f, // Top-right
	0.5f, -0.5f, // Bottom-right
	-0.5f, -0.5f // Bottom-left
    };
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    if (_vbo) {
	glDeleteBuffers(1, &_vbo);
    }
    //_vertexArray = b_;
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    //glBufferData(GL_ARRAY_BUFFER, _vertexArray.size() * sizeof(decltype(_vertexArray)::value_type), &_vertexArray[0], GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &_ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, _elementArray.size() * sizeof(decltype(_vertexArray)::value_type), &(_elementArray[0]), GL_STATIC_DRAW);
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
    //glDrawElements(drawStyle_, _elementArray.size(), GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
