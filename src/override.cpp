#include <iostream>
#include <type_traits>
#include <unordered_map>

struct ModelConfig {
    bool use_gpu = false;
    int batch_size = 1;
    float learning_rate = 0.01;
    std::string model_path = "default.model";
};

// Our override system
struct Override {
    enum Type { BOOL, INT, FLOAT, STRING } type;
    union {
        bool bool_val;
        int int_val;
        float float_val;
        const char* string_val;
    };
};

template<typename T>
typename std::enable_if<std::is_same<T, bool>::value, bool>::type try_override(T& target, const Override* ovrd) {
    // target is a reference to a T which must be &bool in this case which
    // happens at compile time.
    
    // The following check is a runtime check though:
    if (ovrd && ovrd->type == Override::BOOL) {
        target = ovrd->bool_val;
        return true;
    }
    return false;
}

template<typename T>
typename std::enable_if<std::is_same<T, int>::value, bool>::type try_override(T& target, const Override* ovrd) {
    if (ovrd && ovrd->type == Override::INT) {
        target = ovrd->int_val;
        return true;
    }
    return false;
}

template<typename T>
typename std::enable_if<std::is_same<T, float>::value, bool>::type try_override(T& target, const Override* ovrd) {
    if (ovrd && ovrd->type == Override::FLOAT) {
        target = ovrd->float_val;
        return true;
    }
    return false;
}

int main() {
    ModelConfig config;
    std::cout << "\nInitial Configuration:\n";
    std::cout << "Use GPU: " << std::boolalpha << config.use_gpu << "\n";
    std::cout << "Batch Size: " << config.batch_size << "\n";
    std::cout << "Learning Rate: " << config.learning_rate << "\n\n";

    std::unordered_map<std::string, Override> overrides = {
        {"use_gpu",       {Override::BOOL,  {.bool_val = true}}},
        {"batch_size",    {Override::INT,   {.int_val = 32}}},
        {"learning_rate", {Override::FLOAT, {.float_val = 0.001}}}
    };

    if (auto it = overrides.find("use_gpu"); it != overrides.end()) {
        if (try_override(config.use_gpu, &it->second)) {
            std::cout << "Successfully overrode use_gpu to: " << config.use_gpu << "\n";
        }
    }

    if (auto it = overrides.find("batch_size"); it != overrides.end()) {
        if (try_override(config.batch_size, &it->second)) {
            std::cout << "Successfully overrode batch_size to: " << config.batch_size << "\n";
        }
    }

    // Show how the runtime checking works. The compiler will add a call to
    // the int version of try_override because config.batch_size is an int.
    // But at runtime we are passing in a bool value which should not work.
    Override runtime = {Override::BOOL, {.bool_val = true}};
    bool overridden = try_override(config.batch_size, &runtime);
    if (overridden) {
        std::cout << "Successfully overrode runtime Override: " << config.batch_size << "\n";
    } else {
        std::cout << "Failed to override batch_size\n";
    }

    // Print final config
    std::cout << "\nFinal Configuration:\n";
    std::cout << "Use GPU: " << std::boolalpha << config.use_gpu << "\n";
    std::cout << "Batch Size: " << config.batch_size << "\n";
    std::cout << "Learning Rate: " << config.learning_rate << "\n";
}
