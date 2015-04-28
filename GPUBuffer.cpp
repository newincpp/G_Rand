#include "GPUBuffer.hh"

GRand::GPUBuffer::GPUBuffer() : _vbo(0), _scene(NULL) {
}

GRand::GPUBuffer::GPUBuffer(const GPUBuffer& o_) : _vbo(o_._vbo) {
}

void GRand::GPUBuffer::operator=(const GPUBuffer& o_) {
    _vbo = o_._vbo;
}

bool GRand::GPUBuffer::loadFile(std::string const &name) {
    Assimp::Importer importer;

    std::ifstream fin(name.c_str());
    if (!fin.fail()) {
	fin.close();
    } else {
	std::cout << "Couldn't open file: " << pFile << std::endl;
	std::cout << "It seems to work better with absolute path." << std::endl;
	return false;
    }
    _scene = importer.ReadFile(pFile, aiProcessPreset_TargetRealtime_Quality);
    if (!_scene) {
	std::cout << importer.GetErrorString() << std::endl;
	return false;
    }
    return true;
}

void GRand::GPUBuffer::getAllFaces(const struct aiNode* nd) {
    unsigned int n = 0;
    const struct aiMesh* mesh;
    unsigned int faceIndex;

    for (; n < nd->mNumMeshes; ++n) {
	mesh = _scene->mMeshes[nd->mMeshes[n]];
	unsigned int *faceArray;
	faceArray = (unsigned int *)malloc(sizeof(unsigned int) * mesh->mNumFaces * 3);
	faceIndex = 0;
	if (_vertexArray.size() + face->mNumFaces * 6 > _vertexArray.capacity()) {
	    _vertexArray.reserve(_vertexArray.capacity() + face->mNumFaces * 6);
	}

	for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
	    const struct aiFace* face = &mesh->mFaces[t];
	    for (unsigned int i = 0; i < face->mNumIndices; i++) { // go through all vertices in face
		int vertexIndex = face->mIndices[i]; // get group index for current index
		_vertexArray.push_back(mesh->mNormals[vertexIndex].x);
		_vertexArray.push_back(mesh->mNormals[vertexIndex].y);
		_vertexArray.push_back(mesh->mNormals[vertexIndex].z);
		_vertexArray.push_back(mesh->mVertices[vertexIndex].x);
		_vertexArray.push_back(mesh->mVertices[vertexIndex].y);
		_vertexArray.push_back(mesh->mVertices[vertexIndex].z);
	    }
	    //the element array is in face->mIndices
	    memcpy(&faceArray[faceIndex], face->mIndices,3 * sizeof(unsigned int));
	    faceIndex += 3;
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->mNumFaces * 3, faceArray, GL_STATIC_DRAW);
    }
    for (n = 0; n < nd->mNumChildren; ++n) {
	getAllFaces(nd->mChildren[n]);
    }
}

void GRand::GPUBuffer::generateVBOAndVertexArray() {
    if (_vbo) {
	glDeleteBuffers(1, &_vbo);
    }
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo);
    getAllFaces(_scene->mRootNode);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void GRand::GPUBuffer::setBuffer(const std::vector<GLfloat>& b_) {
    if (_vbo) {
        glDeleteBuffers(1, &_vbo);
    }
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, b_.size(), &b_[0], GL_STATIC_DRAW);
}

GRand::GPUBuffer::~GPUBuffer() {
}
