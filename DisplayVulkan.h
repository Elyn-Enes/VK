#pragma once
#include <string>

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

		bool isClosed;

};
