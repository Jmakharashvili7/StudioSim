#pragma once

template <typename T>
class Singleton
{
public:
	static T* Instance() {
		return m_Instance = (m_Instance != nullptr) ? m_Instance : new T();
	}
	~T(){}

private:
	T(){}
	static T* m_Instance = nullptr;

};

