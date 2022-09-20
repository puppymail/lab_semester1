#include <cstddef>

const int QUADRANTS[2][2] = { {2, 1},
                              {3, 4} };

template <typename T>
inline void swap(T *a, T *b) {
    auto temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T>
inline int copy_quadrant(T *input_ptr,
                         T *output_ptr,
                         const size_t &size,
                         const unsigned short int quadrant_input,
                         const unsigned short int quadrant_output) {
    if (quadrant_input < 1
        || quadrant_input > 4
        || quadrant_output < 1
        || quadrant_output > 4) {
        return -1;
    }
    
    const size_t x_i = (quadrant_input == 2 || quadrant_input == 3)
            ? 0
            : (size / 2);
    const size_t y_i = (quadrant_input == 1 || quadrant_input == 2)
            ? 0
            : (size / 2);

    const size_t x_o = (quadrant_output == 2 || quadrant_output == 3)
            ? 0
            : (size / 2);
    const size_t y_o = (quadrant_output == 1 || quadrant_output == 2)
            ? 0
            : (size / 2);

    for (size_t y = 0; y < (size / 2); ++y) {
        for (size_t x = 0; x < (size / 2); ++x) {
            *((output_ptr + (size * (y_o + y))) + (x_o + x)) =
                    *((input_ptr + (size * (y_i + y))) + (x_i + x));
        }
    }
    
    return 0;
}

void sort_bubble(int *array_ptr, const size_t &size);

void sort_shaker(int *array_ptr, const size_t &size);

void sort_comb(int *array_ptr, const size_t &size);

void sort_insert(int *array_ptr, const size_t &size);

void sort_bubble(int *matrix_ptr, 
                 const size_t &width,
                 const size_t &heigth);

void sort_shaker(int *matrix_ptr,
                 const size_t &width,
                 const size_t &heigth);

void sort_comb(int *matrix_ptr,
               const size_t &width,
               const size_t &heigth);

void sort_insert(int *matrix_ptr,
                 const size_t &width,
                 const size_t &heigth);
