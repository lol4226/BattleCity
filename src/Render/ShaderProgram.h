#pragma once

#include<iostream>
#include<string>

#include<glad/glad.h>

namespace Render {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertext_shader, const std::string& fragment_shader);
		~ShaderProgram();
		bool isCompiled() const { return m_isCompiled; }
		void use() const;

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&&) noexcept; 
		ShaderProgram(ShaderProgram&& ShaderProgram) noexcept;
	
	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool m_isCompiled = false;
		GLuint m_ID = 0;
	};
}