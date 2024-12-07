#include "ResourceManager.h"
#include "../Render/ShaderProgram.h"

#include <sstream>
#include <iostream>
#include <fstream>

ResourceManager::ResourceManager(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	m_Path = executablePath.substr(0, found);
}

std::string ResourceManager::GetFileString(const std::string& relativeFilePath) const
{
	std::ifstream f;
	f.open(m_Path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		std::cerr << "Failed to open file" << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}

std::shared_ptr<Render::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexString = GetFileString(vertexPath);
	if (vertexPath.empty())
	{
		std::cerr << "no vertex shader" << std::endl;
		return nullptr;
	}

	std::string fragmentString = GetFileString(fragmentPath);
	if (fragmentPath.empty())
	{
		std::cerr << "no fragment shader" << std::endl;
		return nullptr;
	}

	std::shared_ptr < Render::ShaderProgram>& newShader = m_ShaderPrograms.emplace(shaderName, std::make_shared<Render::ShaderProgram>(vertexString, fragmentString)).first->second;

	if (newShader->isCompiled())
	{
		return newShader;
	}

	std::cerr << "Cant load shader program\n"
		<< "Vertex: " << vertexPath << "\n"
		<< "Fragment: " << fragmentPath << std::endl;
	return nullptr;
}

std::shared_ptr<Render::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{
	ShaderProgramMap::const_iterator it = m_ShaderPrograms.find(shaderName);
	if (it != m_ShaderPrograms.end())
	{
		return it->second;
	}
	std::cerr << "Cant find the shader program: " << shaderName << std::endl;
	return nullptr;
}