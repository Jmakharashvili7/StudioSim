#pragma once
class Component
{
public:
	//constructor
	//the lower the update order, the earlier component updates
	Component(class Actor* _owner, int _updateOrder);

	//Destructor

	virtual ~Component();

	virtual void Update(float _deltaTime);

	inline int GetUpdateOrder() const { return m_UpdateOrder; }

protected:
	//Owning actor
	class Actor* m_Owner;

	//update order of the component
	int m_UpdateOrder;
};

