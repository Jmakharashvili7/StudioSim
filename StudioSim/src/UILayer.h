#pragma once
#include "Layer.h"
#include "UIWindow.h"
#include "ViewportUI.h"
#include "EditorUI.h"
#include "WorldOutlinerUI.h"
#include "ContentBrowserUI.h"
#include "JsonLoader.h"

struct CreatClassInfo
{

	std::string objectName;
	std::string textureName;

	TransformData transformData;
	CollisionData collisionData;
	bool boxCollision;
	bool sphereCollision;
	bool noCollision;

	bool addPhysicsComponent : 1;
	PhysicsData physicsData;

	bool addAnimator : 1;
	AnimationData animationData;

	MovementData movementData;
	EntityData entityData;


	CreatClassInfo()
	{
		objectName = " ";
		textureName = "blue.png";

		transformData = TransformData();
		collisionData = CollisionData();

		addPhysicsComponent = false;
		physicsData = PhysicsData();

		addAnimator = false;
		animationData = AnimationData();

		movementData = MovementData();
		entityData = EntityData();
	}	
};

enum class Classes
{
	GAMEOBJECT,
	ACTOR,
	CHARACTER,
	ENEMY
};

// Basic setup of new window
//1. Create a class for the window you want to implement and make it a child of UIWindow
//2. In UILayer create a pointer to an instance of the class you created
//3. Create the constructor and deconstructor for the class look at ViewportUI .h and .cpp for example
//4. Create a render function for the UI Window
//5. The render function should include ImGui::Begin at the beginning and
//	 ImGui::End at the end of the render function
//6. Create an instance of the class in UILayer.cpp in the Init Windows function
//7. Call the render function of the instance in the EnableDocking function
class UILayer : public Layer
{
public:
	UILayer();
	~UILayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
	void OnEvent() override;
	void InitWindows();

	inline glm::vec4& GetColor() { return m_color; }
	inline ViewportUI* GetViewport() { return m_viewportUI; }
	inline EditorUI* GetEditorUI() { return m_editorUI; }
	inline WorldOutlinerUI* GetWorldOutliner() { return m_worldOutliner; }

	inline std::vector<UIWindow*> GetAllWindows() { return m_windowList; }

private:
	void EnableDocking();
	void SetUpObjectCreator();
	void CreatePopupContent(Classes createClass);
	void BasePopupContent();
	void ActorContent();
	void CharacterContent();
	std::string CollisionName(CollisionType type);

	void ObjectName();
	void ObjectTransformData();
	void ObjectCollisionData(TransformData data);
	void ObjectTextureName();

private:
	float m_time;
	glm::vec4 m_color;
	ViewportUI* m_viewportUI;	
	EditorUI* m_editorUI;
	WorldOutlinerUI* m_worldOutliner;
	ContentBrowserUI* m_contentBrowser;

	std::vector<UIWindow*> m_windowList;
	
	CreatClassInfo newObjectInfo;

	VertexData* vertexData;
};

