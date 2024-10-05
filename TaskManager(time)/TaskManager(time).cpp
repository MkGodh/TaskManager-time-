#include <iostream>
#include <ctime>
#include <vector>

struct TaskInfo {
    std::string name;
    double duration;
    std::tm start_time;
    std::tm end_time;
};

int main() {
    std::string command;
    std::string current_task;
    std::vector<TaskInfo> completed_tasks;
    std::time_t taskBegin;
    std::tm local_start;



    while (command != "exit") {
        std::cout << "Please input a command: " << std::endl;
        std::cin >> command;
        while (command != "begin" && command != "end" && command != "status" && command != "exit") {
            std::cout << "Please input correct command!";
            std::cin >> command;
        }
        if (command == "begin") {
            if (!current_task.empty()) {
                std::cout << "Previous task " << current_task << " ended automatically.\n";

                std::time_t endTime = std::time(nullptr);
                std::tm local_end;
                localtime_s(&local_end, &endTime);
                double taskTime = std::difftime(endTime, taskBegin);

                completed_tasks.push_back({ current_task, taskTime, local_start, local_end });
            }
            std::cout << "Please, input name of the task : ";
            std::cin >> current_task;
            std::cout << "Now you are working on " << current_task << std::endl;

            taskBegin = std::time(nullptr);
            localtime_s(&local_start, &taskBegin);

        }
        else if (command == "end") {
            if (!current_task.empty()) {
                std::time_t endTime = std::time(nullptr);
                std::tm local_end;
                localtime_s(&local_end, &endTime);

                double taskTime = std::difftime(endTime, taskBegin);
                int totalSec = static_cast<int>(taskTime);

                int hours = totalSec / 3600;
                int minutes = (totalSec % 3600) / 60;
                int seconds = totalSec % 60;

                char startBuffer[26];
                char endBuffer[26];
                asctime_s(startBuffer, sizeof(startBuffer), &local_start); 
                asctime_s(endBuffer, sizeof(endBuffer), &local_end);

                std::cout << current_task << " task is end.You begin at: " << startBuffer
                    << " Time wasted: " << hours << " hours," << minutes << " minutes, " << seconds
                    << " seconds.\nAnd you end at " << endBuffer;

                completed_tasks.push_back({ current_task, taskTime, local_start, local_end });
                current_task.clear();
            }
            else {
                std::cout << "No task to end. \n";
            }
        }
        else if (command == "status") {
            if (!current_task.empty()) {
                std::time_t currentTime = std::time(nullptr);
                double taskDif = std::difftime(currentTime, taskBegin);
                int totalSec = static_cast<int>(taskDif);

                int hours = totalSec / 3600;
                int minutes = (totalSec % 3600) / 60;
                int seconds = totalSec % 60;

                char startBuffer[26];
                asctime_s(startBuffer, sizeof(startBuffer), &local_start);

                std::cout << "Current task " << current_task << "' started at: " << startBuffer
                    << " Time wasted: " << hours << " hours, " << minutes << " minutes, " << seconds
                    << " seconds.\n";
            }
            else {
                std::cout << "No active task. \n";
            }
            std::cout << "\nCompleted tasks:\n";
            for (const auto& task : completed_tasks) {
                int totalSec = static_cast<int>(task.duration);
                int hours = totalSec / 3600;
                int minutes = (totalSec % 3600) / 60;
                int seconds = totalSec % 60;

                char startBuffer[26];
                char endBuffer[26];
                asctime_s(startBuffer, sizeof(startBuffer), &task.start_time); // Безопасная версия asctime
                asctime_s(endBuffer, sizeof(endBuffer), &task.end_time);

                std::cout << "Task: " << task.name
                    << " *Start: " << startBuffer
                    << " *End: " << endBuffer
                    << " *Duration: " << hours << " hours, " << minutes << " minutes, " << seconds << " seconds.\n";
            }
        }
    }
    std::cout << "Finishing programm!";
    return 0;
}
