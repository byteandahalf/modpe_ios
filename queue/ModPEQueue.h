#ifndef __MODPEQUEUE_H
#define __MODPEQUEUE_H

#include <vector>

enum class TaskType: int
{
	TASK_ALL,
	TASK_SETICON
};

struct ModPETask
{
	TaskType taskType;

	ModPETask(TaskType t):taskType(t){}

	virtual ~ModPETask() {};
	virtual void doTask() const = 0;
};

struct ModPEQueue
{
	static std::vector<const ModPETask*> queue;

	static void queueTask(const ModPETask*);
	static void doTasks(TaskType);
};

#endif