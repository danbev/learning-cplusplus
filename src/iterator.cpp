#include <iterator>
#include <cstddef>
#include <iostream>

class Integers {
public:
    struct Iterator {
        // Used by standard library algorithms and range-based for loops
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = int;
        using pointer           = int *;
        using reference         = int &;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const {
            return *m_ptr;
        }

        pointer operator->() {
            return m_ptr;
        }

        Iterator& operator++() {
            m_ptr++;
            return *this;
        }

        Iterator operator++(int) {
            // Post increment returns a copy of the current state so we need
            // to create a temporary to return
            Iterator tmp = *this;
            printf("Post-incrementing iterator pointing to %d\n", *m_ptr);
            ++(*this);
            return tmp;
        }

        friend bool operator== (const Iterator& a, const Iterator& b) {
            return a.m_ptr == b.m_ptr;
        };

        friend bool operator!= (const Iterator& a, const Iterator& b) {
            return a.m_ptr != b.m_ptr;
        };


        private:
            pointer m_ptr;
    };

    Integers() {
        for (size_t i = 0; i < SIZE; ++i) {
            m_data[i] = i;
        }
    }

    Iterator begin() {
        return Iterator(&m_data[0]);
    }

    Iterator end()   {
        return Iterator(&m_data[SIZE]);
    }

private:
    constexpr static std::size_t SIZE = 10;
    int m_data[SIZE];
};

int main() {
    Integers integers;
    for (auto i : integers) {
        std::cout << i << "\n";
    }
    for (auto it = integers.begin(); it != integers.end(); ++it) {
        std::cout << *it << "\n";
    }

    return 0;
}
