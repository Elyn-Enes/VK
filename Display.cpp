#include "Display.h"
#include <iostream>
#include <GL/glew.h>


Display::Display( int width, int height, const std::string& title ) {

	SDL_Init( SDL_INIT_EVERYTHING );

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );	
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );	
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	this->window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL );
	this->glContext = SDL_GL_CreateContext( this->window );

	GLenum status = glewInit();
	if ( status != GLEW_OK ) {
		std::cerr << "Glew failed to initialize!" << std::endl;
	} else {
		std::cerr << "Glew OK" << std::endl;
		this->isClosed = false;
	}

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );

}

Display::~Display() {
	SDL_GL_DeleteContext( this->glContext	);
	SDL_Quit();
}

void Display::Update() {
	SDL_GL_SwapWindow( this->window );
	SDL_Event e;
	while ( SDL_PollEvent( &e ) ) {
		if ( e.type == SDL_QUIT ) {
			this->isClosed = true;
		}
	}
}

bool Display::IsClosed() {
	return this->isClosed;
}

void Display::Clear( float r, float g, float b, float a ) {
	glClearColor( r, g, b, a );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ) ;
}