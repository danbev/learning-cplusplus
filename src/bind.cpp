#include <iostream>
#include <functional>
#include <string>

void process_data(int id, std::string data, bool verbose) {
    if (verbose) {
        std::cout << "Processing ID " << id << " with data: " << data << std::endl;
    } else {
        std::cout << "ID " << id << ": " << data << std::endl;
    }
}

class DataProcessor {
public:
    void process(int id, std::string data) {
        std::cout << "DataProcessor " << m_name << " handling ID " << id 
                  << " with data: " << data << std::endl;
    }

    DataProcessor(std::string name) : m_name(name) {}

private:
    std::string m_name;
};

int main() {
    std::cout << "\n--- Free Function Binding ---\n";
    auto verbose_processor = std::bind(process_data,           // function to bind
                                     std::placeholders::_1,    // id remains free
                                     std::placeholders::_2,    // data remains free
                                     true);                    // bind verbose to true
    
    verbose_processor(18, "bajja");  // Calls process_data(18, "bajja", true)

    auto id_processor = std::bind(process_data,
                                36,                           // bind id to 36
                                std::placeholders::_1,        // data remains free
                                false);                       // bind verbose to false
    
    id_processor("bajja 2");

    // Example 2: Member Function Binding
    std::cout << "\n--- Member Function Binding ---\n";
    
    DataProcessor processor1("Processor1");
    DataProcessor processor2("Processor2");

    auto bound_processor1 = std::bind(&DataProcessor::process,
                                    &processor1,
                                    std::placeholders::_1,
                                    std::placeholders::_2);

    auto bound_processor2 = std::bind(&DataProcessor::process,
                                    &processor2,
                                    42,                         // bind id to 42
                                    std::placeholders::_1);     // only data is free

    bound_processor1(1, "data1");
    bound_processor2("data2");

    std::cout << "\n--- Using with std::function ---\n";
    
    using ProcessCallback = std::function<void(int, std::string)>;
    
    ProcessCallback callback1 = bound_processor1;
    ProcessCallback callback2 = verbose_processor;
    
    callback1(3, "via callback1");
    callback2(4, "via callback2");

    return 0;
}
