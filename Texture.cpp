#include "Texture.h"
#include <cassert>
#include <iostream>
#include <image\stb_image.h>


Texture::Texture( const std::string& filename ) {

	int width, height, component_count;

	unsigned char* image_data = stbi_load( filename.c_str(), &width, &height, &component_count, 4 );
	if ( image_data == NULL ) {
		std::cout << "Texture loading failed for filename: " << filename << std::endl;
	}


	glGenTextures( 1, &this->texture );
	glBindTexture( GL_TEXTURE_2D, this->texture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data );
	stbi_image_free( image_data );
}


Texture::~Texture() {
	glDeleteTextures( 1, &this->texture );
}

void Texture::Bind( unsigned int unit ) {
	assert( unit >= 0 && unit <= 31 );
	glActiveTexture( GL_TEXTURE0 + unit );
	glBindTexture( GL_TEXTURE_2D, this->texture );
}