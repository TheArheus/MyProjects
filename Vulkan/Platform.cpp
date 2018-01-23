//
// Created by Артём on 21.01.2018.
//

#include "Platform.h"

void InitPlatform(){
    glfwInit();
}
void DeInitPlatform(){
    glfwTerminate();
}
void AddRequiredPlatformInstanceExtensions(std::vector<const char *> *instance_extensions){
    uint32_t instance_extension_count = 0;
    const char ** instance_extensions_buffer = glfwGetRequiredInstanceExtensions( &instance_extension_count );
    for( uint32_t i=0; i < instance_extension_count; i++ ) {
        instance_extensions->push_back( instance_extensions_buffer[i] );
    }
}
