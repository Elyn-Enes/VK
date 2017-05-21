#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "GLDisplay.h"
#include "UBO.h"
#include "ObjLoader.h"

#include <image\stb_image.h>
#include <iostream>
#include <set>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <unordered_map>

GLDisplay::GLDisplay( int width, int height, const std::string& title ) {

	glfwInit();

	this->window = glfwCreateWindow( width, height, title.c_str(), NULL, NULL );
	glfwMakeContextCurrent( window );
	this->width = width;
	this->height = height;

	GLenum status = glewInit();
	if ( status != 0 ) {
		std::cerr << "Glew failed to initialize!" << std::endl;
	} else {
		std::cerr << "Glew OK" << std::endl;
	}

	this->model = OBJModel( "./_res/chalet.obj" ).ToIndexedModel();

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );


	createShaderPrograms();
	initMesh();
	bindTexture();

}

void GLDisplay::drawFrame() {

	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) ;

	glBindVertexArray( this->vertexArrayObject );
	glDrawElements( GL_TRIANGLES, this->drawCount, GL_UNSIGNED_INT, 0 );
	glBindVertexArray(0);

	glfwSwapBuffers( window );

}

void GLDisplay::initMesh() {
	
	this->drawCount = model.indices.size();
	
	glGenVertexArrays( 1, &this->vertexArrayObject );
	glBindVertexArray( this->vertexArrayObject );

	glGenBuffers( this->NUM_BUFFERS, this->vertexArrayBuffers );

	glBindBuffer( GL_ARRAY_BUFFER, this->vertexArrayBuffers[ this->POSITION_VB ] );
	glBufferData( GL_ARRAY_BUFFER, model.positions.size() * sizeof( model.positions[0] ), &model.positions[0], GL_STATIC_DRAW );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ARRAY_BUFFER, this->vertexArrayBuffers[ this->TEXCOORD_VB ] );
	glBufferData( GL_ARRAY_BUFFER, model.positions.size() * sizeof( model.texCoords[0] ), &model.texCoords[0], GL_STATIC_DRAW );
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ARRAY_BUFFER, this->vertexArrayBuffers[ this->NORMAL_VB ] );
	glBufferData( GL_ARRAY_BUFFER, model.normals.size() * sizeof( model.normals[0] ), &model.normals[0], GL_STATIC_DRAW );
	glEnableVertexAttribArray( 2 );
	glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, 0 );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->vertexArrayBuffers[ this->INDEX_VB ] );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, model.positions.size() * sizeof( model.indices[0] ), &model.indices[0], GL_STATIC_DRAW );

	glBindVertexArray( 0 );

}

GLDisplay::~GLDisplay() {

}

void GLDisplay::updateUniformBuffer() {

	static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0f;

	glm::mat4 model = glm::rotate(glm::mat4(), time * glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);

	glUniformMatrix4fv( this->uniforms[ MODEL_U ], 1, GL_FALSE, &model[0][0] );
	glUniformMatrix4fv( this->uniforms[ VIEW_U ], 1, GL_FALSE, &view[0][0] );
	glUniformMatrix4fv( this->uniforms[ PROJ_U ], 1, GL_FALSE, &proj[0][0] );

}

void GLDisplay::bindTexture() {

	int width, height, component_count;

	unsigned char* image_data = stbi_load( "./_res/chalet.jpg", &width, &height, &component_count, 4 );

	glGenTextures( 1, &this->texture );
	glBindTexture( GL_TEXTURE_2D, this->texture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data );
	stbi_image_free( image_data );

	glActiveTexture( GL_TEXTURE0 + 0 );
	glBindTexture( GL_TEXTURE_2D, this->texture );

}

void GLDisplay::createShaderPrograms() {

	this->program = glCreateProgram();
	this->shaders[ 0 ] = createShader( loadShader( "./_res/basicShader.vs" ), GL_VERTEX_SHADER );
	this->shaders[ 1 ] = createShader( loadShader( "./_res/basicShader.fs" ), GL_FRAGMENT_SHADER );

	for ( unsigned int i = 0; i<this->NUM_SHADERS; i++ ) {
		glAttachShader( this->program, this->shaders[ i ] );
	}

	glBindAttribLocation( this->program, 0, "inPosition" );
	glBindAttribLocation( this->program, 1, "inTexCoord" );
	glBindAttribLocation( this->program, 2, "inNormal" );

	glLinkProgram( this->program );
	this->checkShaderErrors( this->program, GL_LINK_STATUS, true, "Error: Program failed to link!");

	glValidateProgram( this->program );
	this->checkShaderErrors( this->program, GL_VALIDATE_STATUS, true, "Error: Program failed to validate!");

	glUseProgram( this->program );

	this->uniforms[ MODEL_U ] = glGetUniformLocation( this->program, "model" );
	this->uniforms[ VIEW_U ] = glGetUniformLocation( this->program, "view" );
	this->uniforms[ PROJ_U ] = glGetUniformLocation( this->program, "proj" );


}

std::string GLDisplay::loadShader( const std::string &file_name ) {

	std::ifstream file;
	file.open( file_name.c_str() );

	std::string output;
	std::string line;

	if ( file.is_open() ) {
		while ( file.good() ) {
			getline( file, line );
			output.append( line + "\n" );
		}
	} else {
		std::cerr << "Unable to load shader: " << file_name << std::endl;
	}

	return output;

}

GLuint GLDisplay::createShader( const std::string& text, unsigned int type ) {

    GLuint shader = glCreateShader( type );

    if ( shader == 0 ) {
		std::cerr << "Error compiling shader type " << type << std::endl;
	}

    const GLchar* p[ 1 ];
    p[0] = text.c_str();
    GLint lengths[ 1 ];
    lengths[ 0 ] = text.length();

    glShaderSource( shader, 1, p, lengths );
    glCompileShader( shader );

    checkShaderErrors( shader, GL_COMPILE_STATUS, false, "Error compiling shader!" );

    return shader;

}

void GLDisplay::checkShaderErrors( GLuint shader, GLuint flag, bool isProgram, const std::string& message ) {
	
	GLint success      = 0;
    GLchar error[1024] = { 0 };

	if( isProgram ) {
        glGetProgramiv( shader, flag, &success );
	} else {
        glGetShaderiv( shader, flag, &success );
	}

    if ( success == GL_FALSE ) {

        if ( isProgram ) {
            glGetProgramInfoLog( shader, sizeof( error ), NULL, error );
		} else {
            glGetShaderInfoLog( shader, sizeof( error ), NULL, error );
		}

        std::cerr << message << ": '" << error << "'" << std::endl;
    }

}