#pragma once

#include "ObjectLoader.h"
#include "Mesh.h"

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm\gtx\transform.hpp>
#include <image\stb_image.h>


class GLDisplay {

	public:

		GLFWwindow* window;
		GLDisplay::GLDisplay( int width, int height, const std::string& title );
		inline GLFWwindow* getWindow() { return this->window; };
		void GLDisplay::updateUniformBuffer();
		void GLDisplay::drawFrame();

		GLuint GLDisplay::createShader( const std::string& text, unsigned int type );
		void GLDisplay::createShaderPrograms();
		std::string GLDisplay::loadShader( const std::string &file_name );
		void GLDisplay::checkShaderErrors( GLuint shader, GLuint flag, bool isProgram, const std::string& message );
		GLDisplay::~GLDisplay();
		void GLDisplay::initMesh();
		void GLDisplay::bindTexture();

	private:

		int width;
		int height;

		enum {
			MODEL_U,
			VIEW_U,
			PROJ_U,
			NUM_UNIFORMS
		};

		IndexedModel model;

		GLuint program;

		static const unsigned int NUM_SHADERS = 2;

		GLuint shaders[ NUM_SHADERS ];
		GLuint uniforms[ NUM_UNIFORMS ];

		enum {
			POSITION_VB,
			TEXCOORD_VB,
			NORMAL_VB,
			INDEX_VB,
			NUM_BUFFERS
		};

		GLuint transform_vb;

		GLuint vertexArrayObject;
		GLuint vertexArrayBuffers[ NUM_BUFFERS ];
		GLuint texture;
		unsigned int drawCount;


};
