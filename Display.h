#pragma once
#include <string>
#include <SDL2/SDL.h>

class Display {

	public:

		Display( int width, int height, const std::string &title );
		virtual ~Display();

		void Clear( float r, float g, float b, float a );
		void Update();
		bool IsClosed();

	protected:
	private:
		Display( const Display& other ) {}
		Display& operator=( const Display& other ) {}

		SDL_Window *window;
		SDL_GLContext glContext;
		bool isClosed;

};
