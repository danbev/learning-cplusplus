#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};

    std::rotate(v.begin(), v.begin() + 2, v.end());

    for (int i : v) {
        std::cout << i << " ";
    }
    // output: {3, 4, 5, 6, 1, 2}
    std::cout << '\n';

    {
        std::vector<std::string> menu = {"File", "Edit", "View", "Insert", "Format", "Tools", "Window", "Help"};
        std::cout << "Original menu:\n";
        for (const auto& item : menu) {
            std::cout << item << " ";
        }
        std::cout << '\n';

        // Let's say we want to select and group:
        // "Edit", "Insert", "Format"
        // (indices 1, 3, 4) to be contiguous starting at position 1

        // Find iterator of selected item ("Edit" at index 1)
        auto edit_pos = std::find(menu.begin(), menu.end(), "Edit");

        // Find iterator of selected item ("Insert" at index 3)
        auto insert_pos = std::find(edit_pos + 1, menu.end(), "Insert");

        // Rotate to bring "Insert" next to "Edit"
        std::rotate(edit_pos + 1, insert_pos, insert_pos + 1);
        // {"File", "Edit", "View", "Insert", "Format", "Tools", "Window", "Help"}
        //                    ↑        ↑         ↑
        //                   first   middle     last
        // {"File", "Edit", "Insert", "View", "Format", "Tools", "Window", "Help"}

        // Find "Format" and rotate it next to the group
        auto format_pos = std::find(edit_pos + 2, menu.end(), "Format");
        std::rotate(edit_pos + 2, format_pos, format_pos + 1);
        // {"File", "Edit", "Insert", "View", "Format", "Tools", "Window", "Help"}
        //                              ↑        ↑         ↑
        //                             first   middle     last
        // {"File", "Edit", "Insert", "Format", "View", "Tools", "Window", "Help"}

        for (const auto& item : menu) {
            std::cout << item << " ";
        }
        std::cout << '\n';
    }

    {
        // Generalization of the above example
        std::vector<std::string> menu = {"File", "Edit", "View", "Insert", "Format", "Tools", "Window", "Help"};
        auto edit_pos = std::find(menu.begin(), menu.end(), "Edit");
        auto gather_pos = edit_pos + 1;

        for (const auto& item_to_gather : {"Insert", "Format"}) {
            auto pos = std::find(gather_pos, menu.end(), item_to_gather);
            std::rotate(gather_pos, pos, pos + 1);
            ++gather_pos;  // Next item goes one position further
        }

        for (const auto& item : menu) {
            std::cout << item << " ";
        }
        std::cout << '\n';
    }

    return 0;
}
