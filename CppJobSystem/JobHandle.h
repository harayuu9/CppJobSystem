#pragma once
#include <functional>
#include <vector>
#include <thread>

using std::function;
using std::vector;

class Job;
class JobParallelFor;

class JobHandle
{
	vector<function<void()>> funcs;

	friend Job;
	friend JobParallelFor;
public:

	void Complete()
	{
		for (auto& func : funcs)
			func();
	}
};