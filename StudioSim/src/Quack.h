#pragma once
#include "BasicIncludes.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "OrthographicCamera.h"
#include "Window.h"
#include "Texture.h"
#include "GameObject.h"
#include "GameTime.h"
#include "Actor.h"
#include "QuackDataTypes.h"
#include "FrameBuffer.h"
#include "Scene.h"

class LayerStack;
class UIRenderer;
class UILayer;

#define MAX_FRAME_RATE 144
#define NUMBER_OF_SQUARES 4

class CollisionHelper;

class Quack
{
public:
	static int InitEngine();

	static void Update();
	static void RenderUpdate();

	static void ShutDown();
	static Window* GetWindow() { return m_window; }

	static OrthographicCamera* GetOrthoCamera() { return m_mainCamera; }
	static void SetOrthoCamera(OrthographicCamera* camera) { m_mainCamera = camera; }

	static inline float GetDeltaTime() { return m_gameTimer.GetDeltaTime(); }
	static FrameBuffer* GetFrameBuffer() { return m_frameBuffer; }
	static UILayer* GetUILayer() { return m_uiMain; }

	static OrthographicCamera* GetOrthoCam() { return m_mainScene.GetCamera(); }

	static void GenerateTextureList();

private:
	Quack();
	~Quack();

	static void HandleInput();
public:
	static bool m_capFrames;
	static bool s_running;
	static bool s_glfwInitialised;
private:
	static Window* m_window;
	static LayerStack* m_layerStack;
	static UILayer* m_uiMain;

	static FrameBuffer* m_frameBuffer;

	static GameTimer m_gameTimer;
	static Scene m_mainScene;

	static int m_frameCounter;
	static int m_currentFrameRate;

	static OrthographicCamera* m_mainCamera;

	static std::map<std::string, Texture*> m_textures;
};
