#pragma once

#include <string>
#include <memory>
#include <map>

namespace Render
{
	class ShaderProgram;
}

class ResourceManager {
public:
	ResourceManager(const std::string& executablePath);
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&& ShaderProgram) = delete;
	
	std::shared_ptr<Render::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Render::ShaderProgram> getShaderProgram(const std::string& shaderName);

private:
	std::string GetFileString(const std::string& relativeFilePath) const;

	typedef std::map<const std::string, std::shared_ptr<Render::ShaderProgram>> ShaderProgramMap;
	ShaderProgramMap m_ShaderPrograms;

	std::string m_Path;
};