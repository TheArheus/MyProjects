//
// Created by Артём on 20.01.2018.
//

#ifndef VULKAN_WINDOW_H
#define VULKAN_WINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <cstdint>
#include <string>
#include "Render.h"
#include "Shared.h"

class Window {
public:
    Window(Render * render, uint32_t size_x, uint32_t size_y, std::string name);
    ~Window();

    void Close();
    bool Update();

private:
    void _InitOSWindow();
    void _DeInitOSWindow();

    void _InitSurface();
    void _InitOSSurface();
    void _DeInitSurface();

    void _UpdateOSWindow();

    void _InitSwapchain();
    void _DeInitSwapchain();

    void _InitSwapImages();
    void _DeInitSwapImages();

    void _InitDepthStencilImage();
    void _DeInitDepthStencilImage();

    void InitRenderPass();
    void DeInitRenderPass();

    GLFWwindow* window = nullptr;

    Render *r = nullptr;

    static uint64_t _win32_class_id_counter;
    uint32_t _surface_size_x = 512, _surface_size_y = 512;
    uint32_t swapchain_image_number = 2;
    std::string _window_name, _win32_class_name;

    bool windowShouldRun = true;
    bool stencilAvailable = false;

    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    VkSurfaceFormatKHR surfaceFormat;
    VkSwapchainKHR swapchain;
    VkSurfaceKHR surface;
    VkRenderPass renderpass;

    std::vector<VkImage> swapchainImage;
    std::vector<VkImageView> swapchainImage_views;

    VkImage depth_stencil_image = VK_NULL_HANDLE;
    VkImageView depth_stencil_image_view = VK_NULL_HANDLE;
    VkFormat depth_stencil_format = VK_FORMAT_UNDEFINED;
    VkDeviceMemory depth_stencil_memory = VK_NULL_HANDLE;
};


#endif //VULKAN_WINDOW_H
