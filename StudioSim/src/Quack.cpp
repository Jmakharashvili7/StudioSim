#include "Quack.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "DepthTexture.h"

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

	//Shader 
	Shader shader = Shader("shaders/basic.shader");

	DepthTexture depthTexture = DepthTexture("textures/duck.png");

	//Setup stuff
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	//Create vertex buffer object, vertex array object, element buffer object, Frame Buffer and Depth Buffer
	unsigned int VBO, VAO, EBO, FBO, depthFBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenFramebuffers(1, &FBO);
	glGenFramebuffers(1, &depthFBO);
	//Bind vertex array object
	glBindVertexArray(VAO);

	//Copy the vertices into the buffer 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Copy the indices into the buffer 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Bind FBO as active FrameBuffer
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
		cout << "FrameBuffer Completed." << endl;
	else
		cout << "FrameBuffer Not Finished." << endl;

	

	glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture.depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	//Re-bind rendering to the default buffer to have it show on screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Texture
	Texture texture = Texture("textures/duck.png");

	//Camera
	OrthographicCamera camera = OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f);

	// pass projection matrix to shader
	glm::mat4 projection = camera.GetProjectionMatrix();
	shader.SetUniformMatrix4fv("projection", projection);

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

		// bind texture
		texture.Bind();

		// bind shader
		shader.Bind();

		//camera/view transform
		glm::mat4 view = camera.GetViewMatrix();
		shader.SetUniformMatrix4fv("view", view);
		
		//render stuff
		glBindVertexArray(VAO);

		// render square
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		float newangle = tempangle + angleincrementamount;
		tempangle = newangle;
		model = glm::rotate(model, glm::radians(newangle), glm::vec3(0.5f, 0.5f, 0.5f));
		shader.SetUniformMatrix4fv("model", model);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 12);

		// check and call events and swap the buffers
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteFramebuffers(1, &FBO);
	glDeleteFramebuffers(1, &depthFBO);

	glfwTerminate();
	return 0;
}