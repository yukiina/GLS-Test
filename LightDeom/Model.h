#pragma once
#include <string>
#include <vector>
#include "Mesh.h"
#include "ShaderProgram.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>

class Model
{
public:
	Model(const std::string& path);
	void Draw(ShaderProgram& shader);
	~Model();
private:
	std::vector<Mesh> meshes;
	std::string directory;
	void loadModel(const std::string& path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

};

