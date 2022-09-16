#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <string>
#include <chrono>
#include <tuple>
#include "../common/prompt_utils.h"
#include "../common/print_utils.h"

typedef std::chrono::high_resolution_clock::time_point time_var;

#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define time_now() std::chrono::high_resolution_clock::now()

#define ARRAY_VALUE_MIN -99
#define ARRAY_VALUE_MAX 99
#define ARRAY_SIZE 100

#define PAUSE "Pause"

enum SORT_TYPE {BUBBLE = 1, SHAKER, COMB, INSERT};

void swap(int* a, int* b);

int sort(SORT_TYPE sort_type, int* array, const unsigned int size);

int* init_array(int* array, const unsigned int size);

std::tuple<int, int> find_min_and_max(int* array, const unsigned int size);

unsigned int count_elements_more(int* array, const unsigned int size, int value);

unsigned int count_elements_less(int* array, const unsigned int size, int value);

int search(int* array, const unsigned int size, int value);

int binary_search(int* array, const unsigned int size, int value);

int main() {
    std::setlocale(LC_ALL, "");
    std::srand(std::time(NULL));

    int array[100];
    std::cout << "\n1. Create array with size " << ARRAY_SIZE << std::endl;
    while (true) {
        init_array(array, ARRAY_SIZE);
        if (prompt_for_bool("Continue?")) break;
    }

    std::cout << "\n2. Sort array\n";
    while (true) {
        unsigned int choice = prompt_for_number<unsigned int>("1 = Bubble, 2 = Shaker, 3 = Comb, 4 = Insert", 1, 4);
        time_var t = time_now();
        init_array(array, ARRAY_SIZE);
        sort(static_cast<SORT_TYPE>(choice), array, ARRAY_SIZE);
        long int delta = duration(time_now() - t);
        std::cout << "Sorting took " << delta << " nanoseconds\n";
        if (prompt_for_bool("Continue?")) break;
    }

    int min, max;
    std::cout << "\n3. Find min and max\n";
    while (true) {
        time_var t = time_now();
        std::tie(min, max) = find_min_and_max(array, ARRAY_SIZE);
        long int delta = duration(time_now() - t);
        std::cout << "Min = " << min << ", Max = " << max << std::endl;
        std::cout << "Finding min and max in sorted array took " << delta << " nanoseconds\n";
        int unsorted_array[100];
        init_array(unsorted_array, ARRAY_SIZE);
        t = time_now();
        std::tie(min, max) = find_min_and_max(unsorted_array, ARRAY_SIZE);
        delta = duration(time_now() - t);
        std::cout << "Finding min and max in unsorted array took " << delta << " nanoseconds\n";
        if (prompt_for_bool("Continue?")) break;
    }

    std::cout << "\n4. Find median of min and max and find all elements equal to it\n";
    while (true) {
        int median = floor((min + max) / 2.0);
        std::cout << "Median = " << median << "\nIndexes: ";
        int count = 0;
        for (int i = 0; i < ARRAY_SIZE; ++i) {
            if (array[i] == median) {
                ++count;
                std::cout << i << ' ';
            }
        }
        std::cout << std::endl << "Count = " << count << std::endl;
        if (prompt_for_bool("Continue?")) break;
    }

    std::cout << "\n5. Find elements less than\n";
    while (true) {
        int value = prompt_for_number<int>("Enter a value between -99 and 99", -99, 99);
        std::cout << "There are " << count_elements_less(array, ARRAY_SIZE, value) << " elements less than " << value << std::endl;
        if (prompt_for_bool("Continue?")) break;
    }
    
    std::cout << "\n6. Find elements more than\n";
    while (true) {
        int value = prompt_for_number<int>("Enter a value between -99 and 99", -99, 99);
        std::cout << "There are " << count_elements_more(array, ARRAY_SIZE, value) << " elements more than " << value << std::endl;
        if (prompt_for_bool("Continue?")) break;
    }

    std::cout << "\n7. Find a number\n";
    while (true) {
        int value = prompt_for_number<int>("Enter a value between -99 and 99", -99, 99);
        time_var t = time_now();
        int pos = search(array, ARRAY_SIZE, value);
        long int delta = duration(time_now() - t);
        std::cout << "Position of '" << value << "' is " << pos << std::endl;
        std::cout << "Normal search took " << delta << " nanoseconds\n";
        t = time_now();
        pos = binary_search(array, ARRAY_SIZE, value);
        delta = duration(time_now() - t);
        std::cout << "Binary search took " << delta << " nanoseconds\n";
        if (prompt_for_bool("Continue?")) break;
    }

    std::cout << "\n8. Swap elements in an array\n";
    while (true) {
        unsigned int pos1 = prompt_for_number<unsigned int>("Enter first position", 0, 99);
        unsigned int pos2 = prompt_for_number<unsigned int>("Enter second position", 0, 99);
        std::cout << "Before:\n";
        print_array(array, ARRAY_SIZE);
        swap(&array[pos1], &array[pos2]);
        std::cout << "Swapped " << array[pos2] << " and " << array[pos1] << std::endl;
        std::cout << "After:\n";
        print_array(array, ARRAY_SIZE);
        if (prompt_for_bool("Continue?")) break;
    }

    system(PAUSE);
}

void swap(int* a, int* b) {
    auto temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int* array, const unsigned int size) {
    bool swapped;

    do {
        swapped = false;
        for (int i = 0; i < size - 1; ++i) {
            if (array[i] > array[i + 1]) {
                swap(&array[i], &array[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

void shaker_sort(int* array, const unsigned int size) {
    bool swapped;

    do {
        swapped = false;
        for (int i = 0; i < size - 1; ++i) {
            if (array[i] > array[i + 1]) {
                swap(&array[i], &array[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        for (int i = size - 1; i > 0; --i) {
            if (array[i] > array[i + 1]) {
                swap(&array[i], &array[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

void comb_sort(int* array, const unsigned int size) {
    int gap = size;
    float factor = 1.3;
    bool sorted = false;

    do {
        if ( (gap = floor(gap / factor) ) <= 1) {
            gap = 1;
            sorted = true;
        }
        for (int i = 0; i + gap < size; ++i) {
            if (array[i] > array[i + gap]) {
                swap(&array[i], &array[i + gap]);
                sorted = false;
            }
        }
    } while (!sorted);
}

void insert_sort(int* array, const unsigned int size) {
    for (int i = 1; i < size; ++i) {
        for (int j = i; j > 0; --j) {
            if (array[j - 1] > array[j]) {
                swap(&array[j], &array[j - 1]);
            }
        } 
    }
}

int* init_array(int* array, const unsigned int size) {
    for (short i = 0; i < size; ++i) {
        array[i] = std::rand() % 199 - 99;
    }

    return array;
}

int sort(SORT_TYPE sort_type, int* array, const unsigned int size) {
    switch (sort_type) {
        case BUBBLE:
            bubble_sort(array, size);
        case SHAKER:
            shaker_sort(array, size);
        case COMB:
            comb_sort(array, size);
        case INSERT:
            insert_sort(array, size);
        default:
            return -1;
    }

    return 0;
}

std::tuple<int, int> find_min_and_max(int* array, const unsigned int size) {
    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();
    for (int i = 0; i < size; ++i) {
        if (array[i] < min) min = array[i];
        if (array[i] > max) max = array[i];
    }

    return std::make_tuple(min, max);
}

unsigned int count_elements_more(int* array, const unsigned int size, int value) {
    unsigned int count = 0;
    for (int i = 0; i < size; ++i) {
        if (array[i] > value) {
            ++count;
        }
    }

    return count;
}

unsigned int count_elements_less(int* array, const unsigned int size, int value) {
    unsigned int count = 0;
    for (int i = 0; i < size; ++i) {
        if (array[i] < value) {
            ++count;
        }
    }

    return count;
}

int search(int* array, const unsigned int size, int value) {
    for (int i = 0; i < size; ++i) {
        if (array[i] == value) return i;
    }

    return -1;
}

int binary_search(int* array, const unsigned int size, int value) {
    int l = 0, r = size - 1, m;
    while (l <= r) {
        m = floor((l + r) / 2);
        if (array[m] < value) {
            l = m + 1;
        } else if (array[m] > value) {
            r = m - 1;
        } else {
            return m;
        }
    }

    return -1;
}
