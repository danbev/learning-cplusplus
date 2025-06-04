#include <cstdio>
#include <vector>


template<typename A, typename B>                                                    
struct custom_pair {                                                           
    A first;                                                                        
    B second;                                                                   
                                                                                
    custom_pair(const A& a, const B& b) : first(a), second(b)   {}               
    custom_pair()                       : custom_pair(A(), B()) {}                                 
};

int main() {
    printf("Size of custom_pair<int, double>: %zu\n", sizeof(custom_pair<int, double>));

    std::vector<custom_pair<double, int>> logits_id;
    using pair_type = std::remove_reference<decltype(logits_id)>::type::value_type;
    printf("Size of vector<custom_pair<double, int>>: %zu\n", sizeof(logits_id));
    printf("Size of pair_type: %zu\n", sizeof(pair_type));

    pair_type p(1.0, 2);
    printf("Size of custom_pair<double, int>: %zu\n", sizeof(p));

    return 0;
}
