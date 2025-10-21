#include "Task.h"

#include "GameController.h"
Task::Task() : taskId(-1), timeTaken(5), toolsNeeded(false) {}

// Add a constructor that takes an ID
Task::Task(int id, int timeTaken, bool toolsNeeded, GameController *c)
    : taskId(id),
      timeTaken(timeTaken),
      toolsNeeded(toolsNeeded),
      controller(c),
      ticksRemaining(timeTaken * 30) {}

int Task::get_timeTaken() { return timeTaken; }

bool Task::get_toolsNeeded() { return toolsNeeded; }

int Task::getTaskId() { return taskId; }

int Task::getTicksRemaining() { return ticksRemaining; }
void Task::setTicksRemaining(int i) { ticksRemaining = i; }

bool Task::getIsCompleted() { return completed; }