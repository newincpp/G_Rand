#include <istream>
#include <iostream>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <fstream>
#include "GPUBuffer.hh"

GRand::GPUBuffer::GPUBuffer() : _vbo(0), _ebo(0) {
}

GRand::GPUBuffer::GPUBuffer(const GPUBuffer& o_) : _vbo(o_._vbo), _ebo(o_._ebo) {
    if (_vbo == 0) {
	_vertexArray = o_._vertexArray;
    }
    if (_ebo == 0) {
	_elementArray = o_._elementArray;
    }
}

void GRand::GPUBuffer::operator=(const GPUBuffer& o_) {
    _vbo = o_._vbo;
    _ebo = o_._ebo;
    if (_vbo) {
	return;
    }
    _vertexArray = o_._vertexArray;
    _elementArray = o_._elementArray;
}

bool GRand::GPUBuffer::loadFile(std::string const &name) {
    Assimp::Importer importer;

    std::cout << "loading:" << name << std::endl;
    std::ifstream fin(name.c_str());
    if (!fin.fail()) {
	fin.close();
    } else {
	std::cout << "Couldn't open file: " << name << std::endl;
	return false;
    }
    const aiScene* scene = importer.ReadFile(name.c_str(), aiProcessPreset_TargetRealtime_Quality | aiProcess_Triangulate);
    if (!scene) {
	std::cout << importer.GetErrorString() << std::endl;
	return false;
    }
    std::cout << "file read" << std::endl;
    _vertexArray.clear();
    _elementArray.clear();
    _getAllFaces(scene, scene->mRootNode);
    std::cout << "loading finished" << std::endl;
    return true;
}

void GRand::GPUBuffer::_getAllFaces(const struct aiScene *sc, const struct aiNode* nd) {
    unsigned int n = 0;

    for (; n < nd->mNumMeshes; ++n) {
	const struct aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];
	if (_vertexArray.size() + mesh->mNumFaces * 6 > _vertexArray.capacity()) {
	    _vertexArray.reserve(_vertexArray.capacity() + mesh->mNumFaces * 9);
	}
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
	    _vertexArray.push_back(mesh->mVertices[i].z);
	    _vertexArray.push_back(mesh->mVertices[i].y);
	    _vertexArray.push_back(mesh->mVertices[i].x);
	    _vertexArray.push_back(mesh->mNormals[i].z);
	    _vertexArray.push_back(mesh->mNormals[i].y);
	    _vertexArray.push_back(mesh->mNormals[i].x);
	    if (mesh->HasTextureCoords(0)) {
		_vertexArray.push_back(mesh->mTextureCoords[0][i].y);
		_vertexArray.push_back(mesh->mTextureCoords[0][i].x);
	    } else {
		_vertexArray.push_back(0);
		_vertexArray.push_back(0);
	    }
	}
	if (_elementArray.size() + mesh->mNumFaces > _elementArray.capacity()) {
	    _elementArray.reserve(_elementArray.capacity() + mesh->mNumFaces);
	}
	for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
	    const struct aiFace* face = &mesh->mFaces[t];
	    for (unsigned int i = 0; i < face->mNumIndices; i++) { // go through all vertices in face
		unsigned int tmp = face->mIndices[i];
		_elementArray.push_back(tmp);
	    }
	}
    }
    for (n = 0; n < nd->mNumChildren; ++n) {
	_getAllFaces(sc, nd->mChildren[n]);
    }
}

void GRand::GPUBuffer::regenVboEbo() {
    if (_vbo) {
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
    }
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertexArray.size() * sizeof(decltype(_vertexArray)::value_type), &(_vertexArray[0]), GL_STATIC_DRAW);

    glGenBuffers(1, &_ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _elementArray.size() * sizeof(decltype(_vertexArray)::value_type), &(_elementArray[0]), GL_STATIC_DRAW);
}

void GRand::GPUBuffer::setBuffer(const decltype(_vertexArray)& v_, const decltype(_elementArray)& e_) {
    if (_vbo) {
	glDeleteBuffers(1, &_vbo);
    }
    _vertexArray = v_;
    _elementArray = e_;
    regenVboEbo();
}

GRand::GPUBuffer::~GPUBuffer() {
    GPUFree();
}

void GRand::GPUBuffer::GPUFree() {
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}

void GRand::GPUBuffer::CPUFree() {
    _vertexArray.clear();
    _elementArray.clear();
}

void GRand::GPUBuffer::draw(GLenum drawStyle_) const noexcept {
    std::cout << "draw" << _vbo << std::endl;
    glEnableVertexAttribArray(2); // enable vertex shader parameter value
    glEnableVertexAttribArray(3); // enable normal shader parameter value
    glEnableVertexAttribArray(4); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    // when normal enabled
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(decltype(_vertexArray)::value_type), (void*)0); // vertex
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(decltype(_vertexArray)::value_type), (void*)(3 * sizeof(decltype(_vertexArray)::value_type))); //normal
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(decltype(_vertexArray)::value_type), (void*)(6 * sizeof(decltype(_vertexArray)::value_type))); //uv

    // draw the polygon with the shader on the OpenGL draw buffer
    glDrawElements(drawStyle_, _elementArray.size(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);
}
