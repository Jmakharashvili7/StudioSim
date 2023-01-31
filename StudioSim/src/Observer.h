#pragma once
#define MAXOBSERVERS 26
#include "Actor.h"

//enum Event
//{
//	EventEntityDied
//};

//class Observer
//{
//public: 
//	Observer();// only here because of test singleton
//	virtual ~Observer();
//	virtual void onNotify(const class GameObject& go, Event event) = 0;
//};
//
//class Subject
//{
//public:
//	void
//
//private:
//	Observer* m_Observers[MAXOBSERVERS];
//	int m_NumOfObservers;
//
//};

//template<typename T>
class Event
{
public:
    using Callback = std::function<void()>;
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

    void Invoke()
    {
        if (m_callbackIdCounter == 0)
        {
            return;
        }
        for (auto& [id, callback] : m_callbacks)
        {
            callback();
        }
    }

private:
    std::map<CallbackId, Callback> m_callbacks;
    CallbackId m_callbackIdCounter;
};

class EventManager// : public Singleton<EventManager>
{
    EventManager(){}
public:
    
    Event CoinCollected;
    void OnCoinCollected() {

        CoinCollected.Invoke();
    }

};