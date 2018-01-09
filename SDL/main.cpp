#include <iostream>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
/*extern "C"{
#include <LUA/lua.h>
#include <LUA/lauxlib.h>
#include <LUA/lualib.h>
}

#include <conio.h>
#include <winnt.h>*/


int main(int argc, char* argv[]){
    Display display(640, 480, "SDL window");

    Shader shader("..\\res\\basicShader");

    Vertex vertices[] = {Vertex(glm::vec3(-0.5, -0.5, 0.0)),
                         Vertex(glm::vec3(0.5, -0.5, 0.0)),
                         Vertex(glm::vec3(0.0, 0.5, 0.0))};

    Mesh mesh(vertices, sizeof(vertices)/ sizeof(vertices[0]));

    while(!display.IsClosed()){
        display.Clear(0.69f, 0.9f, 0.05f, 0.76f);


        shader.Bind();
        mesh.Draw();

        display.Update();
    }

    return 0;
}

/*int _tmain(int argc, _TCHAR **argv) {
    lua_State *L;

    L = luaL_newstate();

    luaL_openlibs(L);

    int status = luaL_loadfile(L, "test.lua");

    if(status){
        std::cerr<<"File not found"<<std::endl;
        return 1;
    }
    int result = lua_pcall(L, 0, LUA_MULTRET, 0);
    _getch();
    return 0;
}*/
