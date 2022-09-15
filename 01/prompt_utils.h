#include <iostream>
#include <math.h>
#include <string>

#define NUMBER_PROMPT_ERROR_MESSAGE "Please, enter a valid number: "
#define NUMBER_PROMPT_QUERY ": "

bool prompt_for_bool(std::string &prompt);

bool prompt_for_bool(const char* prompt);

template <typename N>
N prompt_for_number(std::string& prompt) {
    N response;

    std::cout << prompt << NUMBER_PROMPT_QUERY;

    while (true) {
        std::cin >> response;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << NUMBER_PROMPT_ERROR_MESSAGE;
            continue;
        }

        return response;
    }
}

template <typename N>
N prompt_for_number(const char* prompt) {
    N response;

    std::cout << prompt << NUMBER_PROMPT_QUERY;

    while (true) {
        std::cin >> response;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << NUMBER_PROMPT_ERROR_MESSAGE;
            continue;
        }

        return response;
    }
}
