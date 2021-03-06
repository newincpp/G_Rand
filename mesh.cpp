#include <istream>
#include <fstream>
#include <iostream>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "assimp/ProgressHandler.hpp"
#include <fstream>
#include "AssimpProgressHandlerOverload.hh"

#include "mesh.hh"

GRand::Controller GRand::Mesh::_static_defaultControler;

GRand::Mesh::Mesh(Core* e_, Material& m_) : _core(e_), _material(m_), _glVertexArray(0), _remote(&_static_defaultControler) {
    if (!e_) {
	std::cout << "\e[31;1mgiving null as a pointer to Core will result to a segmentation fault\e0m" << std::endl;
    }
}

void GRand::Mesh::set(const GPUBuffer& b_) {
    _gb = b_;
    _core->queueIntruction(std::bind(&Mesh::_uploadBuffer, this));
    _core->addPersistantInstruction(std::bind(&Mesh::_render, this));
}

void GRand::Mesh::fromFile(const std::string& fname_) {
    Assimp::Importer importer;

    std::ifstream fin(fname_.c_str());
    if (!fin.fail()) {
	fin.close();
    } else {
	std::cout << "Couldn't open file: " << fname_ << std::endl;
	return;
    }
    importer.SetProgressHandler(new AssimpProgressHandlerOverload(" " + fname_));
    const aiScene* scene = importer.ReadFile(fname_.c_str(), aiProcessPreset_TargetRealtime_Quality | aiProcess_Triangulate);
    if (!scene) {
	std::cout << importer.GetErrorString() << std::endl;
	return;
    }

    //_gb.getVertexArray().clear();
    //_gb.getElementArray().clear();
    _vertexArray.clear();
    _elementArray.clear();
    _getAllFaces(scene, scene->mRootNode);
    importer.FreeScene();

    //_gb.setBuffer();
    _core->queueIntruction(std::bind(&Mesh::_uploadBuffer, this));
    _core->addPersistantInstruction(std::bind(&Mesh::_render, this));
}

void GRand::Mesh::_getAllFaces(const struct aiScene *sc, const struct aiNode* nd) {
    if (!_vertexArray.empty()) {
	return;
    }
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
	    if (mesh->HasNormals()) {
		_vertexArray.push_back(mesh->mNormals[i].z);
		_vertexArray.push_back(mesh->mNormals[i].y);
		_vertexArray.push_back(mesh->mNormals[i].x);
		_gb.setHasNormals(true);
	    }
	    if (mesh->HasTextureCoords(0)) {
		_vertexArray.push_back(mesh->mTextureCoords[0][i].x);
		_vertexArray.push_back(mesh->mTextureCoords[0][i].y);
		_gb.setHasTexture(true);
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

GRand::Controller* GRand::Mesh::genController() {
    _remote = new Controller();
    return _remote;
}

GRand::Controller* GRand::Mesh::getController() {
    return _remote;
}

void GRand::Mesh::setExistantController(GRand::Controller* c_) {
    _remote = c_;
}

GRand::Mesh::~Mesh() {
}

void GRand::Mesh::_render() const {
    _material.use();
    _remote->refresh();
    _gb.draw(GL_TRIANGLES);
}

void GRand::Mesh::_uploadBuffer() {
    std::cout << "material in use: " << _material.getShaderProgram() << std::endl;
    if (!_glVertexArray) {
	glGenVertexArrays(1, &_glVertexArray);
    }
    glBindVertexArray(_glVertexArray);
    _gb.regenVboEbo(_vertexArray, _elementArray);
}
