#pragma once
#include <string>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "VKVertex.h"
#include <glm/glm.hpp>
#include <glm\gtx\transform.hpp>

#include <objloader\objloader.h>
#include <image\stb_image.h>

const std::vector<const char*> validationLayers = {
    "VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};


class VKDisplay {

	public:

		VKDisplay( int width, int height, const std::string &title );
		virtual ~VKDisplay();

		inline GLFWwindow* getWindow() { return this->window; };
		void Clear( float r, float g, float b, float a );
		void Update();
		bool IsClosed();
		bool IsDeviceSuitable( VkPhysicalDevice device );
		void VKDisplay::createInstance( const std::string& title );
		std::vector<const char*> getRequiredExtensions();

		void VKDisplay::setupDebugCallback();
		void VKDisplay::createSurface();
		void VKDisplay::pickPhysicalDevice();
		void VKDisplay::createLogicalDevice();
		void VKDisplay::createSwapChain();
		void VKDisplay::createImageViews();
		void VKDisplay::createRenderPass();
		void VKDisplay::createGraphicsPipeline();
		void VKDisplay::createCommandPool();
		void VKDisplay::createCommandBuffers();
		void VKDisplay::createSemaphores();
		void VKDisplay::drawFrame();
		void VKDisplay::recreateSwapChain();
		void VKDisplay::cleanupSwapChain();
		void VKDisplay::createVertexBuffer();
		void VKDisplay::createBuffer( VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory );
		void VKDisplay::copyBuffer( VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size );
		void VKDisplay::createIndexBuffer();
		void VKDisplay::createUniformBuffer();
		void VKDisplay::createDescriptorPool();
		void VKDisplay::createDescriptorSet();
		void VKDisplay::createDescriptorSetLayout();
		void VKDisplay::updateUniformBuffer();
		void VKDisplay::createTextureImage();
		void VKDisplay::createFramebuffers();
		void VKDisplay::createTextureImageView();
		void VKDisplay::createTextureSampler();
		void VKDisplay::createImage( uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory );
		void VKDisplay::transitionImageLayout( VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout );
		void VKDisplay::copyBufferToImage( VkBuffer buffer, VkImage image, uint32_t width, uint32_t height );
		void VKDisplay::createDepthResources();
		bool VKDisplay::hasStencilComponent( VkFormat format );

		VkFormat VKDisplay::findSupportedFormat( const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features );
	    VkFormat VKDisplay::findDepthFormat();

		VkCommandBuffer VKDisplay::beginSingleTimeCommands();
		void VKDisplay::endSingleTimeCommands( VkCommandBuffer commandBuffer );
		VkShaderModule VKDisplay::createShaderModule( const std::vector<char>& code );
		uint32_t VKDisplay::findMemoryType( uint32_t typeFilter, VkMemoryPropertyFlags properties );
		VkExtent2D VKDisplay::chooseSwapExtent( const VkSurfaceCapabilitiesKHR& capabilities );
		VkImageView VKDisplay::createImageView( VkImage image, VkFormat format, VkImageAspectFlags aspectFlags );

		static VkPresentModeKHR VKDisplay::chooseSwapPresentMode( const std::vector<VkPresentModeKHR> availablePresentModes );
		static VkSurfaceFormatKHR VKDisplay::chooseSwapSurfaceFormat( const std::vector<VkSurfaceFormatKHR>& availableFormats );
		static std::vector<char> VKDisplay::readFile( const std::string& filename );

		int width;
		int height;
		VkDevice device;
		std::vector<uint32_t> indices;
		std::vector<VKVertex> vertices;

	protected:
	private:

		GLFWwindow* window;
		VkInstance instance;

		bool isClosed;

		uint32_t extensionCount = 0;
		std::vector<VkExtensionProperties> extensions;

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		uint32_t deviceCount = 0;
		std::vector<VkPhysicalDevice> devices;

		VkQueue graphicsQueue;
	    VkQueue presentQueue;

		VkSurfaceKHR surface;
		VkDebugReportCallbackEXT callback;

		VkSwapchainKHR swapChain;
		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		std::vector<VkImageView> swapChainImageViews;
		std::vector<VkFramebuffer> swapChainFramebuffers;

		VkRenderPass renderPass;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;
		VkDescriptorSetLayout descriptorSetLayout;

		 VkImage textureImage;
		VkDeviceMemory textureImageMemory;
		VkImageView textureImageView;
		VkSampler textureSampler;

		VkCommandPool commandPool;
		 VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		std::vector<VkCommandBuffer> commandBuffers;

		VkImage depthImage;
		VkDeviceMemory depthImageMemory;
		VkImageView depthImageView;

		VkBuffer indexBuffer;
		VkDeviceMemory indexBufferMemory;

		VkSemaphore imageAvailableSemaphore;
		VkSemaphore renderFinishedSemaphore;

		VkBuffer uniformBuffer;
		VkDeviceMemory uniformBufferMemory;

		VkDescriptorPool descriptorPool;
		VkDescriptorSet descriptorSet;
		
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback( VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData ) {
			std::cout << "validation layer: " << msg << std::endl;
			return VK_FALSE;
		}


};
