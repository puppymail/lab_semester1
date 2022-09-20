#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <string>
#include "../common/prompt_utils.h"
#include "../common/print_utils.h"
#include "../common/array_utils.h"

#define PAUSE "Pause"

enum FILL_TYPE { SPIRAL = 1, SNAKE };

enum SWAP_TYPE { A = 1, B, C, D };

const int SPIRAL_DIR_X[4] = { 1,  0, -1,  0};
const int SPIRAL_DIR_Y[4] = { 0,  1,  0, -1};

const int SNAKE_DIR_X[4] = { 0,  1,  0,  1};
const int SNAKE_DIR_Y[4] = { 1,  0, -1,  0};

inline int fill_matrix(const FILL_TYPE &fill_type,
                       int *matrix_ptr,
                       const size_t &size);

inline int fill_matrix(const FILL_TYPE &fill_type,
                       int *matrix_ptr,
                       const size_t &width,
                       const size_t &heigth);

inline int swap_quadrants(const SWAP_TYPE &swap_type, 
                          int *input_ptr,
                          int *output_ptr,
                          const size_t &size);

int main() {
    std::setlocale(LC_ALL, "");

    std::cout << "1. Create matrix with specified size and fill it in " \
            "specified way\n";
    // prompt for matrix size
    unsigned short int choice;
    do {
        choice = prompt_for_number<unsigned short int>(
            "Enter size of square matrix (6, 8 or 10)"
        );
        if (!(choice == 6 || choice == 8 || choice == 10)) {
            std::cout << "Please enter 6, 8 or 10\n";
            continue;
        }
        break;
    } while (true);

    const size_t size = choice;
    std::cout << "Creating " << size << " by " << size << " matrix\n";

    // init matrix
    int matrix[size][size];
    int *matrix_ptr = &matrix[0][0];
    for (size_t y = 0; y < size; ++y) {
        for (size_t x = 0; x < size; ++x) {
            *((matrix_ptr + (size * y)) + x) = 0;
        }
    }

    // prompt for fill type
    FILL_TYPE fill_type = static_cast<FILL_TYPE>(
        prompt_for_number<unsigned short>(
            "Select fill mode (1 = Spiral, 2 = Snake)", 1, 2
        )
    );
    // fill matrix via fill mode provided by user
    fill_matrix(fill_type, matrix_ptr, size);

    system(PAUSE);

    std::cout << "\n2. Create new matrix with quadrants swapped in a " \
            "specified way\n";
    SWAP_TYPE swap_type;
    // prompt for swap type and swaps, loops until user interrupts
    do {
        // init swapped matrix
        int swapped[size][size];
        int *swapped_ptr = &swapped[0][0];

        // prompt for swap type
        swap_type = static_cast<SWAP_TYPE>(
            prompt_for_number<unsigned short>(
                "Select swap mode (1 = A, 2 = B, 3 = C, 4 = D)", 1, 4
            )
        );
        // swap quadrants and save result to swapped matrix
        swap_quadrants(swap_type, matrix_ptr, swapped_ptr, size);

        std::cout << "Original matrix:\n";
        print_matrix<int>(matrix_ptr, size);
        std::cout << "Swapped matrix:\n";
        print_matrix<int>(swapped_ptr, size);
    
        // if 'n', break and continue the program
        if (!prompt_for_bool("Run again?")) break;
    } while (true);

    system(PAUSE);

    std::cout << "\n3. Sort matrix\n";

    // init sorted matrix and copy values from original matrix
    int sorted[size][size];
    int *sorted_ptr = &sorted[0][0];
    for (size_t y = 0; y < size; ++y) {
        for (size_t x = 0; x < size; ++x) {
            *((sorted_ptr + (size * y)) + x) = *((matrix_ptr + (size * y)) + x);
        }
    }
    
    std::cout << "Before:\n";
    print_matrix<int>(sorted_ptr, size);
    /*
        sorting matrix via insert method. sorts matrix by treating it
        as a one-dimensional array
    */
    sort_insert(sorted_ptr, size, size);
    std::cout << "After:\n";
    print_matrix<int>(sorted_ptr, size);

    system(PAUSE);

    std::cout << "\n4. Apply arithmetic operation to all elements of matrix\n";
    // prompt for operation and value, loops until user interrupts
    do {
        // init calculated matrix
        int calculated[size][size];
        int *calculated_ptr = &calculated[0][0];

        char response;
        int value;
        std::cout << "Enter arithmetic operation ('+', '-', '*', '/'): ";
        // prompt for arithmetic operation
        while (true) {
            std::cin >> response;

            switch (response) {
                case '+':
                    value = prompt_for_number<int>("Enter a second operand");
                    for (size_t y = 0; y < size; ++y) {
                        for (size_t x = 0; x < size; ++x) {
                            *((calculated_ptr + (size * y)) + x) =
                                    *((matrix_ptr + (size * y)) + x) + value;
                        }
                    }
                    break;
                case '-':
                    value = prompt_for_number<int>("Enter a second operand");
                    for (size_t y = 0; y < size; ++y) {
                        for (size_t x = 0; x < size; ++x) {
                            *((calculated_ptr + (size * y)) + x) =
                                    *((matrix_ptr + (size * y)) + x) - value;
                        }
                    }
                    break;
                case '*':
                    value = prompt_for_number<int>("Enter a second operand");
                    for (size_t y = 0; y < size; ++y) {
                        for (size_t x = 0; x < size; ++x) {
                            *((calculated_ptr + (size * y)) + x) =
                                    *((matrix_ptr + (size * y)) + x) * value;
                        }
                    }
                    break;
                case '/':
                    std::cout << "Please note that result will be floored\n";
                    value = prompt_for_number<int>("Enter a second operand");
                    for (size_t y = 0; y < size; ++y) {
                        for (size_t x = 0; x < size; ++x) {
                            *((calculated_ptr + (size * y)) + x) =
                                    *((matrix_ptr + (size * y)) + x) / value;
                        }
                    }
                    break;
                default:
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                    std::cout << "Please, enter valid operation ('+', '-', '*', '/'): ";
                    continue;
            }

            break;
        }

        std::cout << "Original matrix:\n";
        print_matrix<int>(matrix_ptr, size);

        std::cout << "After applying arithmetic operation:\n";
        print_matrix<int>(calculated_ptr, size);
    
        // if 'n', break and continue the program
        if (!prompt_for_bool("Run again?")) break;
    } while (true);

    system(PAUSE);
    
    return 0;
}

// fills matrix in spiral pattern
void fill_matrix_spiral(int *matrix_ptr,
                        const size_t &width,
                        const size_t &heigth) {
    std::srand(std::time(NULL));

    // cursor coordinates
    int x = 0, y = 0;
    // next cursor coordinates
    int next_x, next_y;
    // direction state
    unsigned short int state = 0;
    const unsigned int total_size = width * heigth;

    // init flags to check if value has been assigned to the matrix
    bool flags[heigth][width];
    bool *flags_ptr = &flags[0][0];
    for (size_t y = 0; y < heigth; ++y) {
        for (size_t x = 0; x < width; ++x) {
            *((flags_ptr + (heigth * y)) + x) = false;
        }
    }

    std::cout << "Filling matrix as spiral\n";
    for (unsigned short int i = 1; i <= total_size; ++i) {
        std::cout << "Step " << i << std::endl;

        // setting variable at cursor to random value
        *((matrix_ptr + (heigth * y)) + x) = (std::rand() % total_size) + 1;
        // setting 'set' flag to true
        *((flags_ptr + (heigth * y)) + x) = true;

        print_matrix<int>(matrix_ptr, width, heigth);
        std::cout << std::endl;

        /*
            calculating next coordinates based on direction state
            and direction array
        */
        next_x = x + *(SPIRAL_DIR_X + state);
        next_y = y + *(SPIRAL_DIR_Y + state);
        /* 
            if next coordinates is invalid OR variable was set already,
            change direction state and change next cursor position
            accordingly
        */
        if (next_x < 0 || next_y < 0 || next_x >= width || next_y >= heigth
                || *((flags_ptr + (heigth * next_y)) + next_x)) {
            state = ++state % 4;

            next_x = x + *(SPIRAL_DIR_X + state);
            next_y = y + *(SPIRAL_DIR_Y + state);
        }

        // move cursor to next position
        x = next_x;
        y = next_y;
    }
}

// fills matrix in snake pattern
void fill_matrix_snake(int *matrix_ptr,
                       const size_t &width,
                       const size_t &heigth) {
    std::srand(std::time(NULL));

    // cursor coordinates
    int x = 0, y = 0;
    // next cursor coordinates
    int next_x, next_y;
    // direction state
    unsigned short int state = 0;
    const unsigned int total_size = width * heigth;

    // init flags to check if value has been assigned to the matrix
    bool flags[heigth][width];
    bool *flags_ptr = &flags[0][0];
    for (size_t y = 0; y < heigth; ++y) {
        for (size_t x = 0; x < width; ++x) {
            *((flags_ptr + (heigth * y)) + x) = false;
        }
    }

    std::cout << "Filling matrix as snake\n";
    for (unsigned short int i = 1; i <= total_size; ++i) {
        std::cout << "Step " << i << std::endl;

        // setting variable at cursor to random value
        *((matrix_ptr + (heigth * y)) + x) = (std::rand() % total_size) + 1;
        // setting 'set' flag to true
        *((flags_ptr + (heigth * y)) + x) = true;

        print_matrix<int>(matrix_ptr, width, heigth);
        std::cout << std::endl;

        /*
            calculating next coordinates based on direction state
            and direction array
        */
        next_x = x + *(SNAKE_DIR_X + state);
        next_y = y + *(SNAKE_DIR_Y + state);
        /* 
            if state is 0 or 2, then we are moving downwards or upwards
            and we check if next cursor position is valid, otherwise
            change direction.
            if state is 1 or 3, then we are moving right and we move
            right once and then immediatly change direction
        */
        if ((state % 2) == 0) {
            if (next_y < 0 || next_y >= heigth
                || *((flags_ptr + (heigth * next_y)) + next_x)) {
                state = ++state % 4;

                next_x = x + *(SNAKE_DIR_X + state);
                next_y = y + *(SNAKE_DIR_Y + state);
            }
        
            if (next_x >= width) break;
        } else {
            state = ++state % 4;

            next_x = x + *(SNAKE_DIR_X + state);
            next_y = y + *(SNAKE_DIR_Y + state);
        }

        // move cursor to next position
        x = next_x;
        y = next_y;
    }
}

// helper function that calls appropriate fill_matrix method
inline int fill_matrix(const FILL_TYPE &fill_type,
                       int *matrix_ptr,
                       const size_t &size) {
    switch (fill_type) {
        case FILL_TYPE::SPIRAL:
            fill_matrix_spiral(matrix_ptr, size, size);
            break;
        case FILL_TYPE::SNAKE:
            fill_matrix_snake(matrix_ptr, size, size);
            break;
        default:
            return -1;
    }

    return 0;
}

// helper function that calls appropriate fill_matrix function
inline int fill_matrix(const FILL_TYPE &fill_type,
                       int *matrix_ptr,
                       const size_t &width,
                       const size_t &heigth) {
    switch (fill_type) {
        case FILL_TYPE::SPIRAL:
            fill_matrix_spiral(matrix_ptr, width, heigth);
            break;
        case FILL_TYPE::SNAKE:
            fill_matrix_snake(matrix_ptr, width, heigth);
            break;
        default:
            return -1;
    }

    return 0;
}

/*
    swaps quadrants from input matrix according to
    schema 'a' and writes result to output matrix
*/
void swap_quadrants_a(int *input_ptr,
                      int *output_ptr,
                      const size_t &size) {
    if (size % 2 != 0) {
        std::cerr << "swap_quadrants_a(): Can't swap quadrants in matrix with size not divisible by 2\n";
        return;
    }
    copy_quadrant(input_ptr, output_ptr, size, 1, 4);
    copy_quadrant(input_ptr, output_ptr, size, 2, 1);
    copy_quadrant(input_ptr, output_ptr, size, 3, 2);
    copy_quadrant(input_ptr, output_ptr, size, 4, 3);
}

/*
    swaps quadrants from input matrix according to
    schema 'b' and writes result to output matrix
*/
void swap_quadrants_b(int *input_ptr,
                      int *output_ptr,
                      const size_t &size) {
    if (size % 2 != 0) {
        std::cerr << "swap_quadrants_b(): Can't swap quadrants in matrix with size not divisible by 2\n";
        return;
    }
    copy_quadrant(input_ptr, output_ptr, size, 1, 3);
    copy_quadrant(input_ptr, output_ptr, size, 2, 4);
    copy_quadrant(input_ptr, output_ptr, size, 3, 1);
    copy_quadrant(input_ptr, output_ptr, size, 4, 2);
}

/*
    swaps quadrants from input matrix according to
    schema 'c' and writes result to output matrix
*/
void swap_quadrants_c(int *input_ptr,
                      int *output_ptr,
                      const size_t &size) {
    if (size % 2 != 0) {
        std::cerr << "swap_quadrants_c(): Can't swap quadrants in matrix with size not divisible by 2\n";
        return;
    }
    copy_quadrant(input_ptr, output_ptr, size, 1, 4);
    copy_quadrant(input_ptr, output_ptr, size, 2, 3);
    copy_quadrant(input_ptr, output_ptr, size, 3, 2);
    copy_quadrant(input_ptr, output_ptr, size, 4, 1);
}

/*
    swaps quadrants from input matrix according to
    schema 'd' and writes result to output matrix
*/
void swap_quadrants_d(int *input_ptr,
                      int *output_ptr,
                      const size_t &size) {
    if (size % 2 != 0) {
        std::cerr << "swap_quadrants_d(): Can't swap quadrants in matrix with size not divisible by 2\n";
        return;
    }
    copy_quadrant(input_ptr, output_ptr, size, 1, 2);
    copy_quadrant(input_ptr, output_ptr, size, 2, 1);
    copy_quadrant(input_ptr, output_ptr, size, 3, 4);
    copy_quadrant(input_ptr, output_ptr, size, 4, 3);
}

// helper function that calls appropriate swap_quadrants function
inline int swap_quadrants(const SWAP_TYPE &swap_type,
                          int *input_ptr,
                          int *output_ptr,
                          const size_t &size) {
    switch (swap_type) {
        case SWAP_TYPE::A:
            swap_quadrants_a(input_ptr, output_ptr, size);
            break;
        case SWAP_TYPE::B:
            swap_quadrants_b(input_ptr, output_ptr, size);
            break;
        case SWAP_TYPE::C:
            swap_quadrants_c(input_ptr, output_ptr, size);
            break;
        case SWAP_TYPE::D:
            swap_quadrants_d(input_ptr, output_ptr, size);
            break;
        default:
            return -1;
    }

    return 0;
}
