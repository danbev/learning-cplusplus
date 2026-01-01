#include <forward_list>
#include <iostream>
#include <string>
#include <vector>

void print_list(const std::string& title, const std::forward_list<std::string>& list) {
    std::cout << "--- " << title << " ---\n";
    for (const auto& item : list) {
        std::cout << "[ " << item << " ] -> ";
    }
    std::cout << "nullptr\n\n";
}

int main() {
    std::cout << "Exploring std::forward_list Iterator Mechanics\n\n";

    std::forward_list<std::string> list1;
    
    // forward_list is singly linked. To insert at the very start, 
    // we need a handle to the imaginary spot "before" the first element.
    auto it1 = list1.before_begin();

    list1.emplace_after(it1, "Apple"); 
    // it1 still points to 'before_begin'. We must manually step forward to "Apple".
    it1++; 

    list1.emplace_after(it1, "Banana");
    it1++;

    print_list("List 1 (Manual Increment)", list1);


    std::forward_list<std::string> list2;
    auto it2 = list2.before_begin();

    it2 = list2.emplace_after(it2, "Apple");
    it2 = list2.emplace_after(it2, "Banana");

    print_list("List 2 (Assignment / No Increment)", list2);

    it2 = list2.begin(); // Points to "Apple"
    
    it2 = list2.emplace_after(it2, "Cherry");
    
    print_list("List 2 (After inserting Cherry in middle)", list2);

    return 0;
}
