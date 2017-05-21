#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class VKSwapChainSupportDetails {

	public:

		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;

		static VKSwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR &surface ) {
			VKSwapChainSupportDetails details;

			vkGetPhysicalDeviceSurfaceCapabilitiesKHR( device, surface, &details.capabilities );

			uint32_t formatCount;
			vkGetPhysicalDeviceSurfaceFormatsKHR( device, surface, &formatCount, nullptr );

			if ( formatCount != 0) {
				details.formats.resize(formatCount);
				vkGetPhysicalDeviceSurfaceFormatsKHR( device, surface, &formatCount, details.formats.data() );
			}

			uint32_t presentModeCount;
			vkGetPhysicalDeviceSurfacePresentModesKHR( device, surface, &presentModeCount, nullptr );

			if ( presentModeCount != 0) {
				details.presentModes.resize( presentModeCount );
				vkGetPhysicalDeviceSurfacePresentModesKHR( device, surface, &presentModeCount, details.presentModes.data() );
			}

			return details;
		}
};

