#pragma once
#include "BasicIncludes.h"
#include <list>

class mObserver
{
public:
	virtual ~mObserver(){};
	virtual void Update(const std::string& message) = 0;
};

class mSubject
{
public:
	virtual ~mSubject() {};
	virtual void Attach(mObserver* eye) = 0;
	virtual void Detach(mObserver* eye) = 0;
	virtual void Notify() = 0;
};

//Subject notifies observers when the state is changed

class Subject : public mSubject
{
public:
	virtual ~Subject(){}
	//#rule 1 boss up

};

// 
class Observer : mObserver
{

};