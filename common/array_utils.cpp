#include <cmath>
#include <cstddef>
#include "array_utils.h"

void sort_bubble(int *array_ptr, const size_t &size) {
    bool swapped;

    do {
        swapped = false;
        for (size_t i = 0; i < size - 1; ++i) {
            if (array_ptr[i] > array_ptr[i + 1]) {
                swap(&array_ptr[i], &array_ptr[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

void sort_shaker(int *array_ptr, const size_t &size) {
    bool swapped;

    do {
        swapped = false;
        for (size_t i = 0; i < size - 1; ++i) {
            if (array_ptr[i] > array_ptr[i + 1]) {
                swap(&array_ptr[i], &array_ptr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        for (size_t i = size - 1; i > 0; --i) {
            if (array_ptr[i] > array_ptr[i + 1]) {
                swap(&array_ptr[i], &array_ptr[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

void sort_comb(int *array_ptr, const size_t &size) {
    size_t gap = size;
    const float factor = 1.3;
    bool sorted = false;

    do {
        if ( (gap = floor(gap / factor) ) <= 1) {
            gap = 1;
            sorted = true;
        }
        for (size_t i = 0; i + gap < size; ++i) {
            if (array_ptr[i] > array_ptr[i + gap]) {
                swap(&array_ptr[i], &array_ptr[i + gap]);
                sorted = false;
            }
        }
    } while (!sorted);
}

void sort_insert(int *array, const size_t &size) {
    for (size_t i = 1; i < size; ++i) {
        for (size_t j = i; j > 0; --j) {
            if (array[j - 1] > array[j]) {
                swap(&array[j], &array[j - 1]);
            }
        } 
    }
}

void sort_bubble(int *matrix_ptr,
                 const size_t &width,
                 const size_t &heigth) {
    bool swapped;

    const size_t total_size = width * heigth;

    do {
        swapped = false;
        for (size_t i = 0; i < total_size - 1; ++i) {
            if (matrix_ptr[i] > matrix_ptr[i + 1]) {
                swap(&matrix_ptr[i], &matrix_ptr[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

void sort_shaker(int *matrix_ptr,
                 const size_t &width,
                 const size_t &heigth) {
    bool swapped;

    const size_t total_size = width * heigth;\

    do {
        swapped = false;
        for (size_t i = 0; i < total_size - 1; ++i) {
            if (matrix_ptr[i] > matrix_ptr[i + 1]) {
                swap(&matrix_ptr[i], &matrix_ptr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        for (size_t i = total_size - 1; i > 0; --i) {
            if (matrix_ptr[i] > matrix_ptr[i + 1]) {
                swap(&matrix_ptr[i], &matrix_ptr[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

void sort_comb(int *matrix_ptr,
               const size_t &width,
               const size_t &heigth) {
    const size_t total_size = width * heigth;

    size_t gap = total_size;
    const float factor = 1.3;
    bool sorted = false;

    do {
        if ( (gap = floor(gap / factor) ) <= 1) {
            gap = 1;
            sorted = true;
        }
        for (size_t i = 0; i + gap < total_size; ++i) {
            if (matrix_ptr[i] > matrix_ptr[i + gap]) {
                swap(&matrix_ptr[i], &matrix_ptr[i + gap]);
                sorted = false;
            }
        }
    } while (!sorted);
}

void sort_insert(int *matrix_ptr,
                 const size_t &width,
                 const size_t &heigth) {
    const size_t total_size = width * heigth;

    for (size_t i = 1; i < total_size; ++i) {
        for (size_t j = i; j > 0; --j) {
            if (matrix_ptr[j - 1] > matrix_ptr[j]) {
                swap(&matrix_ptr[j], &matrix_ptr[j - 1]);
            }
        } 
    }
}
