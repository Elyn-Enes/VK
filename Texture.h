#pragma once

#include <string>
#include <gl\glew.h>

class Texture
{
	public:

		Texture( const std::string& filename );
		void Bind( unsigned int unit );
		virtual ~Texture();
		
	protected:
	private:

		Texture( const Texture& other ) {}
		Texture& operator=( const Texture& other );
		GLuint texture;

};

