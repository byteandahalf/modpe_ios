#include "ModPEQueue.h"

#include <mutex>

std::vector<const ModPETask*> ModPEQueue::queue;
std::mutex queueMutex;
void ModPEQueue::queueTask(const ModPETask* task)
{
	if(queueMutex.try_lock())
	{
		// still crashing lol
		//queue.push_back(task);
		queueMutex.unlock();
	}
}

void ModPEQueue::doTasks(TaskType type)
{
	typedef std::vector<const ModPETask*>::iterator task_iterator;
	for(task_iterator it = queue.begin(); it != queue.end(); it++)
	{
		const ModPETask* task = *it;
		if(task != NULL && (type == TaskType::TASK_ALL || task->taskType == type))
		{
			task->doTask();
			delete task;
			queue.erase(it);
		}
	}
}
