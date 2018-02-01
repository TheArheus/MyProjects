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
    _InitSwapImages();
    _InitDepthStencilImage();
    InitRenderPass();
}

Window::~Window() {
    DeInitRenderPass();
    _DeInitDepthStencilImage();
    _DeInitSwapImages();
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
    if(!WSI_Support){
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
        }

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

void Window::_InitDepthStencilImage() {
    std::vector<VkFormat> formats {VK_FORMAT_D32_SFLOAT_S8_UINT,
                                   VK_FORMAT_D24_UNORM_S8_UINT,
                                   VK_FORMAT_D16_UNORM_S8_UINT,
                                   VK_FORMAT_D32_SFLOAT,
                                   VK_FORMAT_D16_UNORM};

    for(auto f : formats){
        VkFormatProperties format_properties{};
        vkGetPhysicalDeviceFormatProperties(r->GetVulkanPhysicalDevice(), f, &format_properties);
        if(format_properties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT){
            depth_stencil_format = f;
            break;
        }
    }
    if((depth_stencil_format == VK_FORMAT_D32_SFLOAT_S8_UINT) ||
       (depth_stencil_format == VK_FORMAT_D24_UNORM_S8_UINT) ||
       (depth_stencil_format == VK_FORMAT_D16_UNORM_S8_UINT) ||
       (depth_stencil_format == VK_FORMAT_D32_SFLOAT) ||
       (depth_stencil_format == VK_FORMAT_D16_UNORM))
    {
        stencilAvailable = true;
    }

    VkImageCreateInfo image_info = {};
    image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_info.flags = 0;
    image_info.imageType = VK_IMAGE_TYPE_2D;
    image_info.format;
    image_info.extent.width = _surface_size_x;
    image_info.extent.height = _surface_size_y;
    image_info.extent.depth = 1;
    image_info.mipLevels = 1;
    image_info.arrayLayers = 1;
    image_info.samples = VK_SAMPLE_COUNT_1_BIT;
    image_info.tiling = VK_IMAGE_TILING_LINEAR;
    image_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    image_info.queueFamilyIndexCount = 0;
    image_info.pQueueFamilyIndices = nullptr;
    image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    vkCreateImage(r->GetVulkanDevice(), &image_info, nullptr, &depth_stencil_image);

    VkMemoryAllocateInfo memory_allocate_info = {};
    VkMemoryRequirements memory_requirements = {};
    vkGetImageMemoryRequirements(r->GetVulkanDevice(), depth_stencil_image, &memory_requirements);

    uint32_t memory_type_index;
    auto gpu_memory_requirements = r->GetVulkanPhysicalDeviceMemoryProperty();
    auto required_properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    for(int i = 0; i < gpu_memory_requirements.memoryTypeCount; i++){
        if(memory_requirements.memoryTypeBits & (1 << i)){
            if((gpu_memory_requirements.memoryTypes[i].propertyFlags & required_properties) == required_properties){
                memory_type_index = i;
                break;
            }
        }
    }

    memory_allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memory_allocate_info.memoryTypeIndex = memory_type_index;
    memory_allocate_info.allocationSize = memory_requirements.size;
    vkAllocateMemory(r->GetVulkanDevice(), &memory_allocate_info, nullptr, &depth_stencil_memory);
    vkBindImageMemory(r->GetVulkanDevice(), depth_stencil_image, depth_stencil_memory, 0);

    VkImageViewCreateInfo image_view_info = {};
    image_view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    image_view_info.subresourceRange.baseMipLevel = 0;
    image_view_info.subresourceRange.levelCount = 1;
    image_view_info.subresourceRange.baseArrayLayer = 0;
    image_view_info.subresourceRange.layerCount = 1;
    image_view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | (stencilAvailable ? VK_IMAGE_ASPECT_STENCIL_BIT : 0);
    image_view_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    image_view_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    image_view_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    image_view_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    image_view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    image_view_info.image = depth_stencil_image;
    image_view_info.format = depth_stencil_format;
    vkCreateImageView(r->GetVulkanDevice(), &image_view_info, nullptr, &depth_stencil_image_view);
}

void Window::_DeInitDepthStencilImage() {
    vkDestroyImageView(r->GetVulkanDevice(), depth_stencil_image_view, nullptr);
    vkFreeMemory(r->GetVulkanDevice(), depth_stencil_memory, nullptr);
    vkDestroyImage(r->GetVulkanDevice(), depth_stencil_image, nullptr);
}

void Window::InitRenderPass() {
    std::array<VkAttachmentDescription, 2> attachments {};
    attachments[0].format = depth_stencil_format;
    attachments[0].flags = 0;
    attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[0].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

    attachments[1].format = surfaceFormat.format;
    attachments[1].flags = 0;
    attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[1].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;

    VkAttachmentReference subpass_0_depth_stencil_attachments = {};
    subpass_0_depth_stencil_attachments.attachment = 0;
    subpass_0_depth_stencil_attachments.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    std::array<VkAttachmentReference, 1> subpass_0_color_attachments = {};
    subpass_0_color_attachments[0].attachment = 1;
    subpass_0_color_attachments[0].layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    std::array<VkSubpassDescription, 1> subpasses = {};
    subpasses[0].pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpasses[0].colorAttachmentCount = subpass_0_color_attachments.size();
    subpasses[0].pColorAttachments = subpass_0_color_attachments.data();
    subpasses[0].pDepthStencilAttachment = &subpass_0_depth_stencil_attachments;

    VkRenderPassCreateInfo renderpass_info = {};
    renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderpass_info.attachmentCount = attachments.size();
    renderpass_info.pAttachments = attachments.data();
    renderpass_info.pSubpasses = subpasses.data();
    renderpass_info.subpassCount = subpasses.size();
    vkCreateRenderPass(r->GetVulkanDevice(), &renderpass_info, nullptr, &renderpass);
}

void Window::DeInitRenderPass() {
    vkDestroyRenderPass(r->GetVulkanDevice(), renderpass, nullptr);
}