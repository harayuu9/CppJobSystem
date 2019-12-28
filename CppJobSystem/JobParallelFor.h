#pragma once
#include "JobHandle.h"

class JobParallelFor
{
public:	
	JobHandle Schedule(unsigned int length);
	JobHandle& Schedule(unsigned int length,JobHandle& handle);

	virtual void Execute(int index) = 0;
};