#pragma once
#include "BasicIncludes.h"

/// <summary>
/// Observer
/// </summary>
class QuackEye
{
public:
	virtual void Update() = 0;
};

/// <summary>
/// Subject owns the states and notifies observers when a state changes
/// </summary>
class Subject
{
public:
	void AddObserver(QuackEye* eye) { pObservers.push_back(eye); }
	void RemoveObserver(QuackEye* eye) {
		pObservers.erase(std::remove(pObservers.begin(), pObservers.end(), eye), pObservers.end());
	}
	void Notify() {
		for (QuackEye* observer : pObservers)
		{
			observer->Update();
		}
	}

private:
	std::vector<QuackEye*> pObservers;
};

class JhonnyTheDuck : public QuackEye //You can change names ade it was just a test =P
{
public:
	void Update() override { std::cout << "The duck knows what u doing dickhead" << std::endl; }
};