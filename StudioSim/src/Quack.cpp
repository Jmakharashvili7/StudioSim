#include "Quack.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Texture.h"

Quack::Quack()
{
	m_window = nullptr;
	m_running = true;
	m_screenWidth = 1080;
	m_screenHeight = 720;
}

Quack::~Quack()
{
	delete m_window;
	m_window = nullptr;
}

int Quack::InitEngine()
{
	if (!glfwInit())
	{
		m_running = false;
		return -1;
	}

	m_window = glfwCreateWindow(m_screenWidth, m_screenHeight, "Studio Sim", NULL, NULL);
	if (!m_window)
	{
		m_running = false;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(m_window);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	/* Initialize the Glew Library*/
	glewExperimental = GL_TRUE;
	glewInit();

	////Setup stuff
	//float vertices[] = {
	//	// positions          // colors           // texture coords
	//	 0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
	//	 0.5f, -0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
	//	-0.5f, -0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
	//	-0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
	//};

	float vertices[] = {
		// positions          // colors           // texture coords
		-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
		 0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // bottom left
		 0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,  // top left 
		 -0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,  // top left 
		 -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,  // top left 
	};

	//Create vertex buffer object, vertex array objec
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//Bind vertex array object
	glBindVertexArray(VAO);
	//Copy the vertices into the buffer 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// texture coord attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	//glBindVertexArray(0);

	//Texture
	Texture texture = Texture("textures/duck.png");

	//Shader 
	Shader shader = Shader("shaders/basic.shader");

	//Camera
	OrthographicCamera camera = OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f);

	//test angle stuff
	float angleincrementamount = 1.0f;
	float tempangle = 0.0f;

	while (m_running)
	{
		//input stuff here
		//process input

		// render stuff here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// bind shader
		shader.Bind();
		// pass projection matrix to shader
		glm::mat4 projection = camera.GetProjectionMatrix();
		shader.SetUniformMatrix4fv("projection", projection);
		//camera/view transform
		glm::mat4 view = camera.GetViewMatrix();
		shader.SetUniformMatrix4fv("view", view);
		//render stuff
		glBindVertexArray(VAO);
		// bind texture
		texture.Bind();
		// render square
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//float newangle = tempangle + angleincrementamount;
		//tempangle = newangle;
		//model = glm::rotate(model, glm::radians(newangle), glm::vec3(1.0f, 0.0f, 0.0f));
		shader.SetUniformMatrix4fv("model", model);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// check and call events and swap the buffers
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}