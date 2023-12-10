#include <iostream>
#include <vector>
#include <string>

class Employee {
    std::string name;
    bool hasTask;

public:
    Employee(const std::string& employeeName) : name(employeeName), hasTask(false) {}

    std::string getName() const {
        return name;
    }

    bool hasReceivedTask() const {
        return hasTask;
    }

    void setTaskReceived(bool value) {
        hasTask = value;
    }

    void doTask(const std::string& task) const {
        std::cout << "Employee " << getName() << " is working on task: " << task << std::endl;
    }
};

class Manager : public Employee {
    std::vector<Employee*> team;

public:
    Manager(const std::string& managerName, const std::vector<Employee*>& employees) : Employee(managerName), team(employees) {}

    int getTeamSize() const {
        return team.size();
    }

    std::vector<Employee*>& getTeam() {
        return team;
    }

    void assignTask(int taskID) {
        std::srand(taskID + std::stoi(getName().substr(getName().find('_') + 1)));

        int totalTasks = 1 + rand() % (getTeamSize());

        std::vector<std::string> taskTypes = { "Task A", "Task B", "Task C" };

        int tasksAssigned = 0;
        int taskIndex = 0;

        if (totalTasks == 0) {
            totalTasks = 1;
        }

        for (int i = 0; i < totalTasks; ++i) {
            int employeeIndex = (i + taskID) % getTeamSize();

            if (!team[employeeIndex]->hasReceivedTask()) {
                std::string taskType = taskTypes[taskIndex % taskTypes.size()];
                team[employeeIndex]->doTask(taskType);
                team[employeeIndex]->setTaskReceived(true);
                ++tasksAssigned;
                ++taskIndex;
            }
        }
        std::cout << "Manager " << getName() << " assigned " << tasksAssigned << " tasks." << std::endl;
    }
};

int main() {
    int numTeams, numEmployees;
    std::cout << "Enter number of teams: ";
    std::cin >> numTeams;

    std::vector<Manager*> managers;

    for (int i = 0; i < numTeams; ++i) {
        std::cout << "Enter number of employees for team " << i + 1 << ": ";
        std::cin >> numEmployees;

        std::vector<Employee*> employees;
        for (int j = 0; j < numEmployees; ++j) {
            std::string employeeName = "Employee_" + std::to_string(i + 1) + "_" + std::to_string(j + 1);
            employees.push_back(new Employee(employeeName));
        }

        std::string managerName = "Manager_" + std::to_string(i + 1);
        Manager* manager = new Manager(managerName, employees);
        managers.push_back(manager);
    }

    int instruction;
    bool allEmployeesAssigned = false;
    while (!allEmployeesAssigned) {
        allEmployeesAssigned = true;
        std::cout << "Enter an instruction for the company (-1 to exit): ";
        std::cin >> instruction;

        if (instruction == -1) {
            break;
        }

        for (int i = 0; i < managers.size(); ++i) {
            managers[i]->assignTask(instruction);
            bool allTasksAssigned = true;
            std::vector<Employee *> &team = managers[i]->getTeam();
            for (int j = 0; j < managers[i]->getTeamSize(); ++j) {
                if (!team[j]->hasReceivedTask()) {
                    allTasksAssigned = false;
                    break;
                }
            }
            if (!allTasksAssigned) {
                allEmployeesAssigned = false;
                break;
            }
        }
    }

    for (int i = 0; i < managers.size(); ++i) {
        delete managers[i];
    }
}
