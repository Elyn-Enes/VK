
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/glew.h>

#include "VKDisplay.h"
#include "GLDisplay.h"
#include "Time.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <objloader\objloader.h>
#undef TINYOBJLOADER_IMPLEMENTATION

#define STB_IMAGE_IMPLEMENTATION
#include <image/stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

#define WIDTH 800
#define HEIGHT 800
#define CLONE_COUNT 50

int main(int argc, char *argv[]) {

	bool DO_VULKAN = true;

	Time time;
	unsigned int time_passed_as_micros = 0;
	unsigned int seconds_passed = 0;
	unsigned int frames_in_last_second = 0;

	if ( ! DO_VULKAN ) {

		GLDisplay displayGL( WIDTH, HEIGHT, "GL" );

		while ( ! glfwWindowShouldClose( displayGL.getWindow() ) ) {

			glfwPollEvents();

			displayGL.updateUniformBuffer();
			unsigned int delta_as_nanos = time.getDelta();
			time_passed_as_micros += delta_as_nanos * 0.0001f;
		
			if (  ( time_passed_as_micros / 100000 ) > seconds_passed + 1 ) { 
				std::cout << "FPS: " << frames_in_last_second << std::endl;
				frames_in_last_second = 0;
				seconds_passed++;
			}

			displayGL.drawFrame();
			frames_in_last_second++;

		}

	} else {

		VKDisplay displayVK( WIDTH, HEIGHT, "VK" );

		while ( ! glfwWindowShouldClose( displayVK.getWindow() ) ) {

			glfwPollEvents();
			displayVK.updateUniformBuffer();
			unsigned int delta_as_nanos = time.getDelta();
			time_passed_as_micros += delta_as_nanos * 0.0001f;
		
			if (  ( time_passed_as_micros / 100000 ) > seconds_passed + 1 ) { 
				std::cout << "FPS: " << frames_in_last_second << std::endl;
				frames_in_last_second = 0;
				seconds_passed++;
			}

			displayVK.drawFrame();
			frames_in_last_second++;

		}

		vkDeviceWaitIdle( displayVK.device );

	}

	return 0;
	

}