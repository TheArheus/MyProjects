//
// Created by Артём on 21.01.2018.
//

#ifndef VULKAN_PLATFORM_H
#define VULKAN_PLATFORM_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <vector>

void InitPlatform();
void DeInitPlatform();
void AddRequiredPlatformInstanceExtensions(std::vector<const char *> *instance_extensions);

#endif //VULKAN_PLATFORM_H
