#pragma once
#include <string>
#include <GL\glew.h>
#include <glm/glm.hpp>
#include <glm\gtx\transform.hpp>
#include <chrono>
#include "Transform.h"
#include "Camera.h"
#include "Lights.h"

class Shader
{
	public:

		Shader( const std::string &file );
		virtual ~Shader();
		void Bind();
		void Update();
		static std::string LoadShader( const std::string &file );
		static void CheckShaderErrors( GLuint shader, GLuint flag, bool isProgram, const std::string &message );
		static GLuint Shader::CreateShader( const std::string& text, unsigned int type );
		inline GLuint getProgram() { return program; };
		void SetLight( Light& light );


	protected:
	private:

		enum {
			MODEL_U,
			VIEW_U,
			PROJ_U,
			NUM_UNIFORMS
		};

		Light light;
		static const unsigned int NUM_SHADERS = 2;
		Shader( const Shader& other ) {}
		GLuint program;
		GLuint shaders[ NUM_SHADERS ];
		GLuint uniforms[ NUM_UNIFORMS ];


};

