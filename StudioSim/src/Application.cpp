// StudioSim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <BasicIncludes.h>
#include "Quack.h"

int main(void)
{
    QuackEngine::Log::Init();
    Quack::InitEngine();

    while (Quack::s_running)
    {
        Quack::Update();
        //Quack::PhysicsUpdate();
        Quack::RenderUpdate();
    }
    Quack::ShutDown();
    return 0;
}