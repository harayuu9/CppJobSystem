/*
The MIT License (MIT)

Copyright (c) 2019 harayuu9 roudo.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

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
