#pragma once
#include <vector>
#include <algorithm>

using namespace std;

class Actor
{
public:

	enum State
	{
		EActive,
		EPaused,
		EDead
	};
	//Constructor
	Actor();

	virtual ~Actor();

	 void Update(float _deltaTime);

	 void Draw();

	 void UpdateComponents(float _deltaTime);

	 // Any actor-specific update code (overridable)
	 virtual void UpdateActor(float _deltaTime);

	 //getters and setters...
	 State GetState() { return m_State; }
	 void SetState(State _newState) { m_State = _newState; }

	 class Transform* GetTransform();


	 //add/remove component
	 void AddComponent(class Component* _component);
	 void RemoveComponent(class Component* _component);

protected:
	//Actor's State
	State m_State;

	class Transform* m_Transform;

	//Transform
	//this should contain things like position, scale and roataion classes and the function to those classes

	vector<class Component* > m_Components;

	 bool SortComponents(class Component* i, class Component* j);
};

