#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <vector>
namespace DEngine {

	class ShadersComp {
	public:
		ShadersComp();
		~ShadersComp();
		//funkcija za compilanje shaderjev
		void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);
		void linkShaders();
		void use();
		void unuse();
		GLint returnColorIndex();
		const GLuint returnProgramID() { return m_programID; }
		void set4f(const std::string &name, glm::vec4 v);
		void set3f(const std::string &name, glm::vec3 v);
		void set2f(const std::string &name, glm::vec2 v);
		void set1f(const std::string &name, float v);

		//	void unuse();
	private:
		void compileShader(GLuint id, std::string shaderPath);
		GLuint m_vertexShaderID;
		GLuint m_fragmentShaderID;
		GLuint m_programID;
	};

} //namespace