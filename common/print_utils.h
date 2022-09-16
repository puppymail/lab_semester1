#include <iostream>
#include <iomanip>

template <typename T>
void print_array(T* array, unsigned int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << std::setw(6) << std::left << i << array[i] << std::endl;
    }
}
