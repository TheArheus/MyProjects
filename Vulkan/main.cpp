#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "Render.h"

int main() {
    Render render;

    render.createWindow(640, 480, "Vulkan tutorial with win32 Window");

    while(render.Run()){}
    /*auto device = render.device;
    auto queue = render.queue;

    VkFence fence;
    VkFenceCreateInfo fenceInfo {};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    vkCreateFence(device, &fenceInfo, nullptr, &fence);

    VkSemaphore semaphore;
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    vkCreateSemaphore(device, &semaphoreInfo, nullptr, &semaphore);

    VkCommandPoolCreateInfo commandPoolInfo{};
    commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolInfo.flags = VK_COMMAND_POOL_RESET_FLAG_BITS_MAX_ENUM;
    commandPoolInfo.queueFamilyIndex = render.graphicsFamilyIndex;

    VkCommandPool commandPool {};
    vkCreateCommandPool(device, &commandPoolInfo, nullptr, &commandPool);

    VkCommandBuffer commandBuffer[2] {};
    VkCommandBufferAllocateInfo commandBufferAllocateInfo {};
    commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferAllocateInfo.commandPool = commandPool;
    commandBufferAllocateInfo.commandBufferCount = 2;
    commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    vkAllocateCommandBuffers(device, &commandBufferAllocateInfo, commandBuffer);

    {
        VkCommandBufferBeginInfo commandBufferBeginInfo{};
        commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        vkCmdPipelineBarrier(commandBuffer[0],
                             VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                             VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
                             0,
                             0, nullptr,
                             0, nullptr,
                             0, nullptr);

        vkBeginCommandBuffer(commandBuffer[0], &commandBufferBeginInfo);
        VkViewport viewPort {};
        viewPort.width = 800;
        viewPort.height = 640;
        viewPort.maxDepth = 1.0f;
        viewPort.minDepth = 0.0f;
        viewPort.x = 0;
        viewPort.y = 0;
        vkCmdSetViewport(commandBuffer[0], 0, 1, &viewPort);
        vkEndCommandBuffer(commandBuffer[0]);
    }
    {
        VkCommandBufferBeginInfo commandBufferBeginInfo{};
        commandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        vkBeginCommandBuffer(commandBuffer[1], &commandBufferBeginInfo);
        VkViewport viewPort {};
        viewPort.width = 800;
        viewPort.height = 640;
        viewPort.maxDepth = 1.0f;
        viewPort.minDepth = 0.0f;
        viewPort.x = 0;
        viewPort.y = 0;
        vkCmdSetViewport(commandBuffer[1], 0, 1, &viewPort);
        vkEndCommandBuffer(commandBuffer[1]);
    }

    {
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer[0];
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &semaphore;
        vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
    }
    {
        VkPipelineStageFlags flags[] = {VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT};
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer[1];
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = &semaphore;
        submitInfo.pWaitDstStageMask = flags;
        vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
    }

    vkQueueWaitIdle(queue);
    //auto res = vkWaitForFences(device, 1, &fence, VK_TRUE, UINT64_MAX);
    vkDestroyCommandPool(device, commandPool, nullptr);
    vkDestroyFence(device, fence, nullptr);*/
    return 0;
}