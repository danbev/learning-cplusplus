#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

struct Task {
    int priority;
    std::string description;
    
    Task(int p, std::string desc) : priority(p), description(std::move(desc)) {}
    
    // Move-only
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;
    Task(Task&&) = default;
    Task& operator=(Task&&) = default;
};

// Custom comparator
struct TaskComparator {
    bool operator()(const Task& lhs, const Task& rhs) const {
        return lhs.priority < rhs.priority;  // Max heap
    }
};

template<typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type>>
class MovablePriorityQueue : public std::priority_queue<T, Container, Compare> {
public:
    // Brings the constructors from the base class
    using std::priority_queue<T, Container, Compare>::priority_queue;

    T pop_move() {
        // Get a reference to the last first
        T item = std::move(this->c.front());

        // First we move the top element to the end, and move all the other elements
        // to keep the heap data structure property intact. This will not remove
        // the element but place it at the end of the container.
        std::pop_heap(this->c.begin(), this->c.end(), this->comp);

        // Now we remove the last element from the heap data structure.
        this->c.pop_back();
        return item;
    }
    void pop() = delete;
};

int main() {
    MovablePriorityQueue<Task, std::vector<Task>, TaskComparator> taskQueue;

    // Adding tasks
    taskQueue.emplace(3, "Complete project proposal");
    taskQueue.emplace(1, "Check emails");
    taskQueue.emplace(2, "Prepare for meeting");
    taskQueue.emplace(5, "Fix critical bug");
    taskQueue.emplace(4, "Review code");

    std::cout << "Processing tasks:\n";
    while (!taskQueue.empty()) {
        Task topTask = taskQueue.pop_move();  // Using our custom pop() that moves
        std::cout << "Priority: " << topTask.priority 
                  << ", Description: " << topTask.description << "\n";
    }

    return 0;
}
