#include "Job.h"

JobHandle Job::Schedule()
{
	JobHandle handle;
	return Schedule(handle);
}

JobHandle& Job::Schedule(JobHandle& handle)
{
	handle.funcs.push_back([this]
		{
			Execute();
		});
}
