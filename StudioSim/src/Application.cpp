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

    ///* Initialize the GLFW library */
    //if (!glfwInit())
    //    return -1;

    //GLFWwindow* window;

    ///* Create a windowed mode window and its OpenGL context */
    //window = glfwCreateWindow(1280, 800, "Studio Sim", NULL, NULL); 
    //if (!window)
    //{
    //    glfwTerminate();
    //    return -1;
    //}

    ///* Make the window's context current */
    //glfwMakeContextCurrent(window);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    ///* Initialize the Glew Library*/
    //glewExperimental = GL_TRUE;
    //glewInit();

    //float positions[] = {
    //-0.5f, -0.5f, // 0
    // 0.5f, -0.5f, // 1
    // 0.5f,  0.5f, // 2
    //-0.5f,  0.5f, // 3
    //};
    //
    //unsigned int indices[] = {
    //    0, 1, 2,
    //    2, 3, 0
    //};
    //
    //GLuint vertexbuffer;
    //glGenBuffers(1, &(vertexbuffer));
    //glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    //
    //unsigned int vao;
    //glGenVertexArrays(1, &vao);
    //glBindVertexArray(vao);
    //
    //VertexArray va;
    //VertexBuffer vb(positions, 4 * 2 * sizeof(float));
    //
    //VertexBufferLayout layout;
    //layout.Push<float>(2);
    //va.AddBuffer(vb, layout);
    //
    //IndexBuffer ib(indices, 6);
    //
    //Shader shader("shaders/basic.shader");
    //shader.Bind();
    //shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    //va.Unbind();
    //vb.Unbind();
    //ib.Unbind();
    //shader.Unbind();

    //GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    //GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    ///* Loop until the user closes the window */
    //while (!glfwWindowShouldClose(window))
    //{
    //    /* Render here */
    //    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    //    QE_INFO("Testing!");

    //    ////shader.Bind();
    //    va.Bind();
    //    ib.Bind();  
    //    vb.Bind();
    //    shader.Bind();
    //    
    //    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

    //    glfwSwapBuffers(window);

    //    /* Poll for and process events */
    //    glfwPollEvents();
    //}

    
    glfwTerminate();

    delete quackEngine;
    quackEngine = nullptr;

    return 0;
}