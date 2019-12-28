#pragma once
#include "JobHandle.h"

class Job
{
public:
	JobHandle Schedule();
	JobHandle& Schedule(JobHandle& handle);

	virtual void Execute() = 0;
};