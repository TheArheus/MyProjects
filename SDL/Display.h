//
// Created by Артём on 28.12.2017.
//

#ifndef SDL_DISPLAY_H
#define SDL_DISPLAY_H

#include <string>
#include <GL/glew.h>
#include <SDL2/SDL.h>

class Display {
public:
    Display(int width, int height, const std::string title);
    ~Display();
    bool IsClosed();
    void Update();
    void Clear(float r, float g, float b, float a);

private:
    SDL_Window* m_window;
    SDL_GLContext m_GLContext;
    bool m_IsClosed;
};


#endif //SDL_DISPLAY_H
