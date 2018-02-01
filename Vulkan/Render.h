//
// Created by Артём on 16.01.2018.
//

#ifndef VULKAN_RENDER_H
#define VULKAN_RENDER_H

#include <vulkan/vulkan.hpp>
#include <vector>
#include <iostream>

#include "windows.h"

class Window;

class Render {
public:
    Render();
    ~Render();

    Window* createWindow(uint32_t size_x, uint32_t size_y, std::string name);

    bool Run();

    const VkInstance						GetVulkanInstance()	const;
    const VkPhysicalDevice					GetVulkanPhysicalDevice() const;
    const VkDevice							GetVulkanDevice() const;
    const VkQueue							GetVulkanQueue() const;
    const uint32_t							GetVulkanGraphicsQueueFamilyIndex() const;
    const VkPhysicalDeviceProperties	&	GetVulkanPhysicalDeviceProperties() const;
    const VkPhysicalDeviceMemoryProperties & GetVulkanPhysicalDeviceMemoryProperty() const;
private:
    void _InitInstance();
    void _DeInitInstance();

    void _InitDevice();
    void _DeInitDevice();

    void _SetupDebug();
    void _InitDebug();
    void _DeInitDebug();

    void SetupLayersAndExtensions();

    VkInstance instance = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;
    VkPhysicalDevice gpu = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties gpu_property = {};
    VkDebugReportCallbackCreateInfoEXT callbackInfoEXT {};
    VkDebugReportCallbackEXT callbackReport = VK_NULL_HANDLE;
    VkQueue queue = VK_NULL_HANDLE;
    VkPhysicalDeviceMemoryProperties gpu_memory_properties {};

    Window* _window = nullptr;

    uint32_t graphicsFamilyIndex = 0;

    std::vector<const char*> instanceLayer;
    std::vector<const char*> instanceEXT;
    std::vector<const char*> deviceLayer;
    std::vector<const char*> deviceEXT;
};


#endif //VULKAN_RENDER_H
