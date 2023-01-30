#pragma once
#define MAXOBSERVERS 26

enum Event
{
	EventEntityDied
};

class Observer
{
public: 
	Observer();// only here because of test singleton
	virtual ~Observer();
	virtual void onNotify(const class GameObject& go, Event event) = 0;
};

class Subject
{
public:
	void

private:
	Observer* m_Observers[MAXOBSERVERS];
	int m_NumOfObservers;

};

template<typename T>
class Event
{
public:
    using Callback = std::function<void(T)>;
    using CallbackId = size_t;

    Event() : m_callbackIdCounter(0) {}

    CallbackId Subscribe(Callback callback)
    {
        m_callbacks[m_callbackIdCounter] = callback;
        return m_callbackIdCounter++;
    }

    void Unsubscribe(CallbackId id)
    {
        m_callbacks.erase(id);
    }

    void Invoke(T eventArgs)
    {
        for (auto& [id, callback] : m_callbacks)
        {
            callback(eventArgs);
        }
    }

private:
    std::map<CallbackId, Callback> m_callbacks;
    CallbackId m_callbackIdCounter;
};

class EventManager
{
public:
    EventManager();
    ~EventManager();



};