// StudioSim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <BasicIncludes.h>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Quack.h"

int main(void)
{
    QuackEngine::Log::Init();

    Quack* quackEngine = new Quack();
    quackEngine->InitEngine();
    glfwTerminate();

    delete quackEngine;
    quackEngine = nullptr;

    return 0;
}