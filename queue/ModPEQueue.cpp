#include "ModPEQueue.h"

#include <mutex>

std::vector<const ModPETask*> ModPEQueue::queue;
std::mutex queueMutex;
void ModPEQueue::queueTask(const ModPETask* task)
{
	//queue.push_back(task);
}

void ModPEQueue::doTasks(TaskType type)
{
	// This doesn't work due to what I can only assume to be a threading issue with std::vector
	typedef std::vector<const ModPETask*>::iterator task_iterator;
	for(task_iterator it = queue.begin(); it != queue.end(); it++)
	{
		const ModPETask* task = *it;
		if(task != NULL && (type == TaskType::TASK_ALL || task->taskType == type))
		{
			task->doTask();
			delete task;
			// crashes
			//queue.erase(it);
		}
	}
}
