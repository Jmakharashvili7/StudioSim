// StudioSim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <BasicIncludes.h>
#include "Quack.h"

int main(void)
{
    QuackEngine::Log::Init();
    QE_ERROR("test");

    //c

    Quack* quackEngine = new Quack();
    quackEngine->InitEngine();

    /* Initialize the library */
    /*if (!glfwInit())
        return -1;*/

    /* Create a windowed mode window and its OpenGL context */
    /*window = glfwCreateWindow(640, 480, "Studio Sim", NULL, NULL); 
    if (!window)
    {
        glfwTerminate();
        return -1;
    }*/

    /* Make the window's context current */
    //glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    //while (!glfwWindowShouldClose(window))
    //{
    //    /* Render here */
    //    glClear(GL_COLOR_BUFFER_BIT);

    //    /* Swap front and back buffers */
    //    glfwSwapBuffers(window);

    //    /* Poll for and process events */
    //    glfwPollEvents();
    //}

    
    glfwTerminate();

    delete quackEngine;
    quackEngine = nullptr;

    return 0;
}