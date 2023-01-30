#pragma once
#include "Singleton.h"


class ExampleSingleton : public Singleton<ExampleSingleton>
{

	ExampleSingleton();
public:
	void Test();
};

