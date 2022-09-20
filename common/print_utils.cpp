#include <cstddef>
#include "print_utils.h"

template void print_array<int>(int *array_ptr, const size_t &size);

template void print_matrix<int>(int *matrix_ptr, const size_t &size);

template void print_matrix<int>(int *matrix_ptr,
                                const size_t &width,
                                const size_t &height);
