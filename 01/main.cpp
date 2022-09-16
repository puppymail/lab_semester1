#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <string>
#include "../common/prompt_utils.h"

// amount of examples to provide for binary strings
#define EXAMPLE_AMOUNT 1
#define PAUSE "Pause"

std::string get_binary_string(int value);

std::string get_binary_string(float value);

std::string get_binary_string(double value);

int main() {
    std::setlocale(LC_ALL, "");
    std::srand(std::time(NULL));

    // displaying sizes of primitive types
    std::cout << "Sizes of primitive types:\n"
            << std::setw(16) << std::left << "'int'"
                    << sizeof(int) << " bytes / " 
                    << sizeof(int) * 8 << " bits\n"
            << std::setw(16) << std::left << "'short int'"
                    << sizeof(short int) << " bytes / "
                    << sizeof(short int) * 8 << " bits\n"
            << std::setw(16) << std::left << "'long int'"
                    << sizeof(long int) << " bytes / "
                    << sizeof(long int) * 8 << " bits\n"
            << std::setw(16) << std::left << "'long long int'"
                    << sizeof(long long int) << " bytes / "
                    << sizeof(long long int) * 8 << " bits\n"
            << std::setw(16) << std::left << "'float'"
                    << sizeof(float) << " bytes / "
                    << sizeof(float) * 8 << " bits\n"
            << std::setw(16) << std::left << "'double'"
                    << sizeof(double) << " bytes / "
                    << sizeof(double) * 8 << " bits\n"
            << std::setw(16) << std::left << "'long double'"
                    << sizeof(long double) << " bytes / "
                    << sizeof(long double) * 8 << " bits\n"
            << std::setw(16) << std::left << "'char'"
                    << sizeof(char) << " bytes / "
                    << sizeof(char) * 8 << " bits\n"
            << std::setw(16) << std::left << "'bool'"
                    << sizeof(bool) << " bytes / "
                    << sizeof(bool) * 8 << " bits\n"
            << std::endl;

    unsigned int run_count;
    bool generate_random;
    std::string prompt;

    // displaying and calculating binary strings of integers

    // prompt for user input whether to generate random numbers
    generate_random = prompt_for_bool("Generate random numbers?");

//     // prompt for user input on amount of examples
//     run_count = prompt_for_number<unsigned int>("How many times to run? (enter positive integer)");

    prompt = std::string("Enter an integer");
    std::cout << "Binary string of 'signed int' (sign[1]|numeric[31]):\n";
    for (short i = 0; i < (run_count <= 0 || run_count > 99 ? EXAMPLE_AMOUNT : run_count); i++) {
        // if 'generate_random', value is randomly assigned, otherwise the user is prompted
        int value = generate_random
                ? std::rand()
                : prompt_for_number<int>(prompt);

        int positive = abs(value), negative = -abs(value);

        // printing binary string for positive value
        std::cout << std::setw(13) << std::left << positive
                << "-> " << get_binary_string(positive) << std::endl;

        // printing binary string for negative value
        std::cout << std::setw(13) << std::left << negative
                << "-> " << get_binary_string(negative) << std::endl;
    }

    // displaying and calculating binary strings of floats
    prompt = std::string("Enter a float");
    std::cout << "Binary string of 'float' (sign[1]|exponent[8]|mantissa[23]):\n";
    for (short i = 0; i < (run_count <= 0 || run_count > 99 ? EXAMPLE_AMOUNT : run_count); i++) {
        // if 'generate_random', value is randomly assigned, otherwise the user is prompted
        float value = generate_random
                ? static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)
                : prompt_for_number<float>(prompt);

        float positive = abs(value), negative = -abs(value);

        // printing binary string for positive value
        std::cout << std::setw(13) << std::left << positive
                << "-> " << get_binary_string(positive) << std::endl;

        // printing binary string for negative value
        std::cout << std::setw(13) << std::left << negative
                << "-> " << get_binary_string(negative) << std::endl;
    }

    // displaying and calculating binary strings of doubles
    prompt = std::string("Enter a double");
    std::cout << "Binary string of 'double' (sign[1]|exponent[11]|mantissa[52]):\n";
    for (short i = 0; i < (run_count <= 0 || run_count > 99 ? EXAMPLE_AMOUNT : run_count); i++) {
        double value = generate_random
                ? static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)
                : prompt_for_number<double>(prompt);

        double positive = abs(value), negative = -abs(value);

        // printing binary string for positive value
        std::cout << std::setw(13) << std::left << positive
                << "-> " << get_binary_string(positive) << std::endl;

        // printing binary string for negative value
        std::cout << std::setw(13) << std::left << negative
                << "-> " << get_binary_string(negative) << std::endl;
    }

    system(PAUSE);

    return 0;
}

std::string get_binary_string(int value) {
    char result[sizeof(value) * 8 + 2];
    unsigned int mask = 1 << (sizeof(value) * 8 - 1);

    short pos = 0;
    result[pos++] = value & unsigned(mask) ? '1' : '0';
    result[pos++] = '|';
    value <<= 1;
    for (; pos <= (sizeof(value) * 8); value <<= 1) {
        result[pos++] = value & mask ? '1' : '0';
    }
    result[pos] = '\0';

    return std::string(result);
}

union float_container {
    float float_value;
    int int_value;
};

std::string get_binary_string(float value) {
    char result[sizeof(value) * 8 + 3];
    unsigned int mask = 1u << (sizeof(value) * 8u - 1u);
    union float_container container;
    container.float_value = value;
    
    short pos = 0;
    for (; pos <= (sizeof(value) * 8) + 1; container.int_value <<= 1) {
        result[pos++] = container.int_value & mask ? '1' : '0';
        if (pos == 1 || pos == 10) {
            result[pos++] = '|';
        }
    }
    result[pos] = '\0';

    return std::string(result);
}

union double_container {
    double double_value;
    long long int int_value;
};

std::string get_binary_string(double value) {
    char result[sizeof(value) * 8 + 3];
    unsigned long long int mask = 1ull << (sizeof(value) * 8llu - 1ull);
    union double_container container;
    container.double_value = value;
    
    short pos = 0;
    for (; pos <= (sizeof(value) * 8) + 1; container.int_value <<= 1) {
        result[pos++] = container.int_value & mask ? '1' : '0';
        if (pos == 1 || pos == 13) {
            result[pos++] = '|';
        }
    }
    result[pos] = '\0';

    return std::string(result);
}
