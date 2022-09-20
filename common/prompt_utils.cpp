#include <iostream>
#include <math.h>
#include <string>
#include "prompt_utils.h"

#define BOOL_PROMPT_ERROR_MESSAGE "Please, enter 'Y' or 'N': "
#define BOOL_PROMPT_QUERY " (Y/N): "

#define CHAR_PROMPT_ERROR_MESSAGE "Please, enter a valid character: "
#define CHAR_PROMPT_QUERY ": "

bool prompt_for_bool(std::string &prompt) {
    char response;

    std::cout << prompt << BOOL_PROMPT_QUERY;

    while (true) {
        std::cin >> response;

        switch (response) {
            case 'Y':
            case 'y':
                return true;
            case 'N':
            case 'n':
                return false;
            default:
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
                std::cout << BOOL_PROMPT_ERROR_MESSAGE;
        }
    }
}

bool prompt_for_bool(const char* prompt) {
    char response;

    std::cout << prompt << BOOL_PROMPT_QUERY;

    while (true) {
        std::cin >> response;

        switch (response) {
            case 'Y':
            case 'y':
                return true;
            case 'N':
            case 'n':
                return false;
            default:
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
                std::cout << BOOL_PROMPT_ERROR_MESSAGE;
        }
    }
}

char prompt_for_char(std::string &prompt) {
    char response;

    std::cout << prompt << CHAR_PROMPT_QUERY;

    while (true) {
        std::cin >> response;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
            std::cout << CHAR_PROMPT_ERROR_MESSAGE;
            continue;
        }

        return response;
    }
}

char prompt_for_char(const char* prompt) {
    char response;

    std::cout << prompt << CHAR_PROMPT_QUERY;

    while (true) {
        std::cin >> response;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
            std::cout << CHAR_PROMPT_ERROR_MESSAGE;
            continue;
        }

        return response;
    }
}

template unsigned int prompt_for_number<unsigned int>(std::string& prompt);
template int prompt_for_number<int>(std::string& prompt);
template float prompt_for_number<float>(std::string& prompt);
template double prompt_for_number<double>(std::string& prompt);

template unsigned int prompt_for_number<unsigned int>(const char* prompt);
template int prompt_for_number<int>(const char* prompt);
template float prompt_for_number<float>(const char* prompt);
template double prompt_for_number<double>(const char* prompt);
