//
// Created by Артём on 26.12.2017.
//

#ifndef OPENGL1_DISPLAY_H
#define OPENGL1_DISPLAY_H
#define GLEW_STATIC

#include <SDL.h>
#include <glut.h>
#include <string>


class Display {
public:
    Display(int width, int height, const std::string& title);
    bool IsClosed();
    Display();
    void Clear(float r, float g, float b, float a);
    void Update();

    bool m_IsClosed;
    SDL_Window* m_window;
    SDL_GLContext m_GLContext;

    ~Display();
};


#endif //OPENGL1_DISPLAY_H
