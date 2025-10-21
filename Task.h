#ifndef TASK_H
#define TASK_H
#include <string>
class GameController;
class ProgressBar;

class Task {
 protected:
  int taskId;  // Use taskId consistently, not id
  int timeTaken;
  bool toolsNeeded;
  GameController *controller;
  int ticksRemaining;
  ProgressBar *progress;
  bool completed = false;

 public:
  Task();
  Task(int id, int timeTaken, bool toolsNeeded, GameController *controller);

  virtual ~Task() = default;
  virtual void tick() {};
  int getTicksRemaining();
  void setTicksRemaining(int i);
  int get_timeTaken();
  bool get_toolsNeeded();
  bool getIsCompleted();
  int getTaskId();
  virtual std::string getDirection() { return "none"; };
  virtual std::string getType() { return "none"; };

  virtual void complete() {};
};

#endif