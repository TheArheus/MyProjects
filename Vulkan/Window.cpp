//
// Created by Артём on 20.01.2018.
//

#include "Window.h"

Window::Window(Render * render, uint32_t size_x, uint32_t size_y, std::string name) {
    r = render;
    _surface_size_x = size_x;
    _surface_size_y = size_y;
    _window_name = name;
    _InitOSWindow();
    _InitSurface();
    _InitSwapchain();
}

Window::~Window() {
    _DeInitSwapchain();
    _DeInitSurface();
    _DeInitOSWindow();
}

bool Window::Update() {
    _UpdateOSWindow();
    return windowShouldRun;
}

void Window::Close() {
    windowShouldRun = false;
}

void Window::_InitSurface() {
    _InitOSSurface();

    VkBool32 WSI_Support;
    auto gpu = r->GetVulkanPhysicalDevice();

    vkGetPhysicalDeviceSurfaceSupportKHR(gpu, r->GetVulkanGraphicsQueueFamilyIndex(), surface, &WSI_Support);
    if(WSI_Support){
        std::cout<<"WSI not supported"<<std::endl;
        exit(-1);
    }

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(r->GetVulkanPhysicalDevice(), surface, &surfaceCapabilities);
    if(surfaceCapabilities.currentExtent.width < UINT32_MAX){
        _surface_size_x = surfaceCapabilities.currentExtent.width;
        _surface_size_y = surfaceCapabilities.currentExtent.height;
    }

    {
        uint32_t formatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, surface, &formatCount, nullptr);
        if(formatCount == 0){
            std::cerr<<"Surface format missing"<<std::endl;
            exit(-1);
        }
        std::vector<VkSurfaceFormatKHR> formatList(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, surface, &formatCount, formatList.data());
        if(formatList[0].format == VK_FORMAT_UNDEFINED){
            surfaceFormat.format = VK_FORMAT_B8G8R8A8_UNORM;
            surfaceFormat.colorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
        }
        else{
            surfaceFormat = formatList[0];
        }
    }
}

void Window::_DeInitSurface() {
    vkDestroySurfaceKHR(r->GetVulkanInstance(), surface, nullptr);
}

void Window::_InitSwapchain() {
    if(swapchain_image_number < surfaceCapabilities.minImageCount + 1) swapchain_image_number = surfaceCapabilities.minImageCount + 1;
    if(swapchain_image_number > surfaceCapabilities.maxImageCount) swapchain_image_number = surfaceCapabilities.maxImageCount;

    VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;

        uint32_t present_mode_count = 0;
        ErrorCheck(vkGetPhysicalDeviceSurfacePresentModesKHR(r->GetVulkanPhysicalDevice(), surface, &present_mode_count, nullptr));
        std::vector<VkPresentModeKHR> presentModeList(present_mode_count);
        ErrorCheck(vkGetPhysicalDeviceSurfacePresentModesKHR(r->GetVulkanPhysicalDevice(), surface, &present_mode_count, presentModeList.data()));

        for(auto m : presentModeList){
            if(m == VK_PRESENT_MODE_MAILBOX_KHR){
                std::cerr<<"[VULKAN] Present mode: MAILBOX"<<std::endl;
                break;
            }
            else if(m == VK_PRESENT_MODE_FIFO_KHR){
                std::cerr<<"[VULKAN] Present mode: FIFO"<<std::endl;
                break;
            }
            else if(m == VK_PRESENT_MODE_IMMEDIATE_KHR){
                std::cerr<<"[VULKAN] Present mode: IMMEDIATE"<<std::endl;
                break;
            }
        }


    /*VkSwapchainCreateInfoKHR swapchainInfo {};
    swapchainInfo.surface = surface;
    swapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchainInfo.clipped = VK_TRUE;
    swapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchainInfo.imageArrayLayers = 1;
    swapchainInfo.imageColorSpace = surfaceFormat.colorSpace;
    swapchainInfo.imageExtent.width = _surface_size_x;
    swapchainInfo.imageExtent.height = _surface_size_y;
    swapchainInfo.imageFormat = surfaceFormat.format;
    swapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    swapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchainInfo.minImageCount = swapchain_image_number; //create doublebuffering
    swapchainInfo.oldSwapchain = VK_NULL_HANDLE;
    swapchainInfo.pQueueFamilyIndices = nullptr;
    swapchainInfo.queueFamilyIndexCount = 0;
    swapchainInfo.presentMode = presentMode;
    swapchainInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;*/
    VkSwapchainCreateInfoKHR swapchain_create_info {};
    swapchain_create_info.sType						= VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchain_create_info.surface					= surface;
    swapchain_create_info.minImageCount				= swapchain_image_number;
    swapchain_create_info.imageFormat				= surfaceFormat.format;
    swapchain_create_info.imageColorSpace			= surfaceFormat.colorSpace;
    swapchain_create_info.imageExtent.width			= _surface_size_x;
    swapchain_create_info.imageExtent.height		= _surface_size_y;
    swapchain_create_info.imageArrayLayers			= 1;
    swapchain_create_info.imageUsage				= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchain_create_info.imageSharingMode			= VK_SHARING_MODE_EXCLUSIVE;
    swapchain_create_info.queueFamilyIndexCount		= 0;
    swapchain_create_info.pQueueFamilyIndices		= nullptr;
    swapchain_create_info.preTransform				= VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    swapchain_create_info.compositeAlpha			= VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchain_create_info.presentMode				= presentMode;
    swapchain_create_info.clipped					= VK_TRUE;
    swapchain_create_info.oldSwapchain				= VK_NULL_HANDLE;

    ErrorCheck(vkCreateSwapchainKHR(r->GetVulkanDevice(), &swapchain_create_info, nullptr, &swapchain));

    ErrorCheck(vkGetSwapchainImagesKHR(r->GetVulkanDevice(), swapchain, &swapchain_image_number, nullptr));
}

void Window::_DeInitSwapchain() {
    vkDestroySwapchainKHR(r->GetVulkanDevice(), swapchain, nullptr);
}

void Window::_InitSwapImages() {
    swapchainImage.resize(swapchain_image_number);
    swapchainImage_views.resize(swapchain_image_number);

    vkGetSwapchainImagesKHR(r->GetVulkanDevice(), swapchain, &swapchain_image_number, swapchainImage.data());

    for(uint32_t i = 0; i < swapchain_image_number; ++i){
        VkImageViewCreateInfo imageViewInfo {};
        imageViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewInfo.image = swapchainImage[i];
        imageViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewInfo.format = surfaceFormat.format;
        imageViewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        imageViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        imageViewInfo.subresourceRange.baseMipLevel = 0;
        imageViewInfo.subresourceRange.levelCount = 1;
        imageViewInfo.subresourceRange.baseArrayLayer = 0;
        imageViewInfo.subresourceRange.layerCount = 1;

        vkCreateImageView(r->GetVulkanDevice(), &imageViewInfo, nullptr, &swapchainImage_views[i]);
    }
}

void Window::_DeInitSwapImages() {
    for(auto view : swapchainImage_views){
        vkDestroyImageView(r->GetVulkanDevice(), view, nullptr);
    }
}