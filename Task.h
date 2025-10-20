#ifndef TASK_H
#define TASK_H

class Task{
    private:
        int timeTaken;
        bool toolsNeeded;
    public:
        Task();
        Task(int timeTaken, bool toolsNeeded);
        int get_timeTaken();
        bool get_toolsNeeded();
};

#endif