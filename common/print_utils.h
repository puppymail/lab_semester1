#ifndef _H_PRINT_UTILS
#define _H_PRINT_UTILS
#include <cstddef>
#include <iostream>
#include <iomanip>
#include <cstddef>

template <typename T>
void print_array(T *array_ptr, const size_t &size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << std::setw(6) << std::left << i << array_ptr[i] << std::endl;
    }
}

template <typename T>
void print_matrix(T *matrix_ptr, const size_t &width, const size_t &heigth) {
    for (size_t y = 0; y < heigth; ++y) {
        for (size_t x = 0; x < width; ++x) {
            std::cout << *((matrix_ptr + (heigth * y)) + x) << "\t";
        }
        std::cout << std::endl;
    }
}

template <typename T>
void print_matrix(T *matrix_ptr, const size_t &size) {
    print_matrix(matrix_ptr, size, size);
}

#endif
