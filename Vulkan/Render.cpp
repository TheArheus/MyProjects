//
// Created by Артём on 16.01.2018.
//

#include "Render.h"
#include "Window.h"
#include "Platform.h"
#include <sstream>

Render::Render() {
    InitPlatform();
    SetupLayersAndExtensions();
    _SetupDebug();
    _InitInstance();
    _InitDebug();
    _InitDevice();
}

Render::~Render() {
    delete _window;

    _DeInitDevice();
    _DeInitDebug();
    _DeInitInstance();
    DeInitPlatform();
}

const VkInstance Render::GetVulkanInstance() const
{
    return instance;
}

const VkPhysicalDevice Render::GetVulkanPhysicalDevice() const
{
    return gpu;
}

const VkDevice Render::GetVulkanDevice() const
{
    return device;
}

const VkQueue Render::GetVulkanQueue() const
{
    return queue;
}

const uint32_t Render::GetVulkanGraphicsQueueFamilyIndex() const
{
    return graphicsFamilyIndex;
}

const VkPhysicalDeviceProperties & Render::GetVulkanPhysicalDeviceProperties() const
{
    return gpu_property;
}

const VkPhysicalDeviceMemoryProperties& Render::GetVulkanPhysicalDeviceMemoryProperty() const {
    return gpu_memory_properties;
}

void Render::SetupLayersAndExtensions() {
    instanceEXT.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
    AddRequiredPlatformInstanceExtensions( &instanceEXT );

    deviceEXT.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
}

Window* Render::createWindow(uint32_t size_x, uint32_t size_y, std::string name) {
    _window = new Window(this, size_x, size_y, name);
    return _window;
}

bool Render::Run() {
    if(_window != nullptr){
        _window->Update();
    }
    return true;
}

void Render::_InitInstance() {
    /*VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 3);
    appInfo.pApplicationName = "Vulkan Tutorial";

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledLayerCount = instanceLayer.size();
    createInfo.enabledExtensionCount = instanceEXT.size();
    createInfo.ppEnabledLayerNames = instanceLayer.data();
    createInfo.ppEnabledExtensionNames = instanceEXT.data();
    //createInfo.pNext = &callbackInfoEXT;

    vkGetPhysicalDeviceMemoryProperties(gpu, &gpu_memory_properties);

    auto err = vkCreateInstance(&createInfo, VK_NULL_HANDLE, &instance);
    if(VK_SUCCESS != err){
        std::cerr<<"Vulkan error : Instance create failed"<<std::endl;
        std::exit(-1);
    }*/
    VkApplicationInfo application_info;
    application_info.sType                    = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    application_info.apiVersion               = VK_MAKE_VERSION(1, 0, 3);
    application_info.applicationVersion       = VK_MAKE_VERSION(1, 0, 0);
    application_info.pApplicationName         = "Vulkan Learning";

    VkInstanceCreateInfo instance_info;
    instance_info.sType                       = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_info.pApplicationInfo            = &application_info;
    //instance_info.enabledLayerCount         = instLayers.size();
    //instance_info.ppEnabledLayerNames       = instLayers.data();
    //instance_info.enabledExtensionCount     = instExt.size();
    //instance_info.ppEnabledExtensionNames   = instExt.data();

    vkCreateInstance(&instance_info, VK_NULL_HANDLE, &instance);
}

void Render::_DeInitInstance() {
    vkDestroyInstance(instance, VK_NULL_HANDLE);
    instance = VK_NULL_HANDLE;
}

void Render::_InitDevice() {
    {
        uint32_t gpu_count = 0;
        vkEnumeratePhysicalDevices(instance, &gpu_count, VK_NULL_HANDLE);
        std::vector<VkPhysicalDevice> gpu_list(gpu_count);
        vkEnumeratePhysicalDevices(instance, &gpu_count, gpu_list.data());
        gpu = gpu_list[0];

        vkGetPhysicalDeviceProperties(gpu, &gpu_property);
    }
    {
        uint32_t family_count = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(gpu, &family_count, VK_NULL_HANDLE);
        std::vector<VkQueueFamilyProperties> familyPropertyList(family_count);
        vkGetPhysicalDeviceQueueFamilyProperties(gpu, &family_count, familyPropertyList.data());

        bool found = false;
        for(int i = 0; i<family_count;i++){
            if(familyPropertyList[i].queueFlags && VK_QUEUE_GRAPHICS_BIT){
                found = true;
                graphicsFamilyIndex = i;
                break;
            }
        }
        if(!found){
            std::cerr<<"Vulkan ERROR : Queue family supporting graphics not found"<<std::endl;
            std::exit(1);
        }
    }

    {
        uint32_t layerCount1;
        vkEnumerateInstanceLayerProperties(&layerCount1, VK_NULL_HANDLE);
        std::vector<VkLayerProperties> layerPropertyList(layerCount1);
        vkEnumerateInstanceLayerProperties(&layerCount1, layerPropertyList.data());

        /*std::cout<<"Instance layers: "<<std::endl;
        for(auto &i : layerPropertyList){
            std::cout<<i.layerName<<std::endl;
        }
        std::cout<<std::endl;*/
    }

    {
        uint32_t layerCount2;
        vkEnumerateDeviceLayerProperties(gpu, &layerCount2, VK_NULL_HANDLE);
        std::vector<VkLayerProperties> layerPropertyList(layerCount2);
        vkEnumerateDeviceLayerProperties(gpu, &layerCount2, layerPropertyList.data());

        /*std::cout<<"Device layers: "<<std::endl;
        for(auto &i : layerPropertyList){
            std::cout<<i.layerName<<std::endl;
        }
        std::cout<<std::endl;*/
    }

    float queue_priority[] = {1.0f};

    VkDeviceQueueCreateInfo queueCreateInfo {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.pQueuePriorities = queue_priority;
    queueCreateInfo.queueFamilyIndex = graphicsFamilyIndex;
    queueCreateInfo.queueCount = 1;

    VkDeviceCreateInfo deviceInfo {};
    deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceInfo.queueCreateInfoCount = 1;
    deviceInfo.pQueueCreateInfos = &queueCreateInfo;
    //deviceInfo.enabledLayerCount = deviceLayer.size();
    deviceInfo.enabledExtensionCount = deviceEXT.size();
    //deviceInfo.ppEnabledLayerNames = deviceLayer.data();
    deviceInfo.ppEnabledExtensionNames = deviceEXT.data();

    auto err = vkCreateDevice(gpu, &deviceInfo, nullptr, &device);
    if(VK_SUCCESS != err){
        std::cerr<<"Vulkan error : Device creation failed"<<std::endl;
        std::exit(-1);
    }

    vkGetDeviceQueue(device, graphicsFamilyIndex, 0, &queue);
}

void Render::_DeInitDevice() {
    vkDestroyDevice(device, VK_NULL_HANDLE);
    device = VK_NULL_HANDLE;
}

VKAPI_ATTR VkBool32 VKAPI_CALL DebugReport(VkDebugReportFlagsEXT msgFlags, VkDebugReportObjectTypeEXT objectType, uint64_t sourceObject, size_t location, int32_t msgCode, const char* layerPrefix, const char* msg, void* userData){

    std::ostringstream stream;
    stream << "VKDBG: ";
    if( msgFlags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT ) {
        stream << "INFO: ";
    }
    if( msgFlags & VK_DEBUG_REPORT_WARNING_BIT_EXT ) {
        stream << "WARNING: ";
    }
    if( msgFlags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT ) {
        stream << "PERFORMANCE: ";
    }
    if( msgFlags & VK_DEBUG_REPORT_ERROR_BIT_EXT ) {
        stream << "ERROR: ";
    }
    if( msgFlags & VK_DEBUG_REPORT_DEBUG_BIT_EXT ) {
        stream << "DEBUG: ";
    }
    stream << "@[" << layerPrefix << "]: ";
    stream << msg << std::endl;
    std::cout << stream.str();

    /*if( msgFlags & VK_DEBUG_REPORT_ERROR_BIT_EXT ) {
        MessageBox( NULL, stream.str().c_str(), "Vulkan Error!", 0 );
    }*/

    return false;
}

void Render::_SetupDebug() {
    callbackInfoEXT.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    callbackInfoEXT.pfnCallback = DebugReport;
    callbackInfoEXT.flags = VK_DEBUG_REPORT_DEBUG_BIT_EXT |
                            VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
                            VK_DEBUG_REPORT_ERROR_BIT_EXT |
                            VK_DEBUG_REPORT_WARNING_BIT_EXT |
                            VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;

    instanceLayer.push_back("VK_LAYER_LUNARG_standard_validation");
    instanceEXT.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

    deviceLayer = instanceLayer;
}

PFN_vkCreateDebugReportCallbackEXT fvkCreateDebugReportCallbackEXT = VK_NULL_HANDLE;
PFN_vkDestroyDebugReportCallbackEXT fvkDestroyDebugReportCallbackEXT = VK_NULL_HANDLE;

void Render::_InitDebug() {
    fvkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");

    if(fvkDestroyDebugReportCallbackEXT == VK_NULL_HANDLE || fvkCreateDebugReportCallbackEXT == VK_NULL_HANDLE){
        std::cerr<<"Vulkan ERROR: cannon fetch functions"<<std::endl;
        return;
    }

    fvkCreateDebugReportCallbackEXT(instance, &callbackInfoEXT,VK_NULL_HANDLE, &callbackReport);
}

void Render::_DeInitDebug() {
    fvkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
    fvkDestroyDebugReportCallbackEXT(instance, callbackReport, VK_NULL_HANDLE);
}