#include "JobParallelFor.h"

JobHandle JobParallelFor::Schedule(unsigned int length)
{
	JobHandle handle;
	return Schedule(length, handle);
}

JobHandle& JobParallelFor::Schedule(unsigned int length, JobHandle& handle)
{
	handle.funcs.push_back([length,this]
	{	
		auto threadCount = std::thread::hardware_concurrency();
		vector<std::thread> threads;
		auto threadTask = length / threadCount;
		if (threadTask == 0) {
			threads.push_back(std::thread([&]
			{
				for (unsigned int index = 0; index < length; index++)
				{
					Execute(index);
				}
			}));
		}
		else
		{
			for (unsigned int i = 0; i < threadCount - 1; i++)
			{
				threads.push_back(std::thread([i,&threadTask,this]
				{
					for (auto index = threadTask*i; index < threadTask * i + threadTask; index++)
					{
						Execute(index);
					}
				}));
			}
			threads.push_back(std::thread([&threadTask,&threadCount,&length, this]
			{
				for (auto index = threadTask * (threadCount-1); index < length; index++)
				{
					Execute(index);
				}
			}));
		}
		for (auto& t : threads)
			t.join();
	});
	return handle;
}
