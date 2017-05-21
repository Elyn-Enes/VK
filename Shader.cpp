#include "Shader.h"
#include <string>
#include <fstream>
#include <iostream>


Shader::Shader( const std::string &file_name ){

	this->program = glCreateProgram();
	this->shaders[ 0 ] = CreateShader( LoadShader( file_name + ".vs" ), GL_VERTEX_SHADER );
	this->shaders[ 1 ] = CreateShader( LoadShader( file_name + ".fs" ), GL_FRAGMENT_SHADER );

	for ( unsigned int i = 0; i<this->NUM_SHADERS; i++ ) {
		glAttachShader( this->program, this->shaders[ i ] );
	}

	glBindAttribLocation( this->program, 0, "inPosition" );
	glBindAttribLocation( this->program, 1, "inTexCoord" );
	glBindAttribLocation( this->program, 2, "inNormal" );

	glLinkProgram( this->program );
	this->CheckShaderErrors( this->program, GL_LINK_STATUS, true, "Error: Program failed to link!");

	glValidateProgram( this->program );
	this->CheckShaderErrors( this->program, GL_VALIDATE_STATUS, true, "Error: Program failed to validate!");

	this->uniforms[ MODEL_U ] = glGetUniformLocation( this->program, "model" );
	this->uniforms[ VIEW_U ] = glGetUniformLocation( this->program, "view" );
	this->uniforms[ PROJ_U ] = glGetUniformLocation( this->program, "proj" );

		
}

Shader::~Shader(){
	for ( unsigned int i = 0; i<this->NUM_SHADERS; i++ ) {
		glDetachShader( this->program, this->shaders[ i ] );
		glDeleteShader( this->shaders[ i ] );
	}
	glDeleteProgram( this->program );
}

void Shader::Bind() {
	glUseProgram( this->program );
}

void Shader::Update() {

	static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0f;

	glm::mat4 model = glm::rotate(glm::mat4(), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);

	glUniformMatrix4fv( this->uniforms[ MODEL_U ], 1, GL_FALSE, &model[0][0] );
	glUniformMatrix4fv( this->uniforms[ VIEW_U ], 1, GL_FALSE, &view[0][0] );
	glUniformMatrix4fv( this->uniforms[ PROJ_U ], 1, GL_FALSE, &proj[0][0] );

}

void Shader::SetLight( Light& light ) {

}

std::string Shader::LoadShader( const std::string &file_name ) {

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

void Shader::CheckShaderErrors( GLuint shader, GLuint flag, bool isProgram, const std::string& message ) {
	
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

GLuint Shader::CreateShader( const std::string& text, unsigned int type ) {

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

    CheckShaderErrors( shader, GL_COMPILE_STATUS, false, "Error compiling shader!" );

    return shader;

}