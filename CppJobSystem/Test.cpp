#include "JobParallelFor.h"
#include <math.h>

constexpr auto MAX = 100000000;

class AddJob : public JobParallelFor
{
public:
	AddJob(vector<int>& add) : addList{ add }
	{}

	vector<int>& addList;

	void Execute(int index)
	{
		addList[index] = (int)(cosf(sinf((float)index)) * 1000.0f);
	}
};

class SubJob : public JobParallelFor
{
public:
	SubJob(vector<int>& add) : addList{ add }
	{}

	vector<int>& addList;

	void Execute(int index)
	{
		addList[index] = (int)(sinf(cosf(sinf((float)addList[index])) * 1000.0f));
	}
};

int main()
{
	vector<int> addList;
	addList.resize(MAX);

	auto start = std::chrono::system_clock::now(); // Œv‘ªŠJŽnŽžŠÔ

	for (auto i = 0; i < 5; i++) {
		AddJob job(addList);
		SubJob job2(addList);
		auto handle = job.Schedule(MAX);
		handle = job2.Schedule(MAX, handle);
		handle.Complete();
	}
	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	printf("%lld", elapsed);
	return 0;
}