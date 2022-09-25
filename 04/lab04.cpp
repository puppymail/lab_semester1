#include <cstdlib>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <iterator>
#include <cctype>
#include "lab04.h"

#define PAUSE "Pause"

#define WORDS_AMOUNT_MIN 1
#define WORDS_AMOUNT_MAX 50

#define WORD_SIZE_MIN 1
#define WORD_SIZE_MAX 10

void edit_text(std::string &str);

std::string reverse_words(std::string &str);

void print_words(std::string &str);

int lab04() {
    std::setlocale(LC_ALL, "Russian");

    std::cout << "1. Enter between 1 and 50 words between 1 and 10 symbols " 
            "each separated by space and terminated by a dot\n";

    std::cout << "Please, enter text:\n";
    std::string str;
    std::cin.sync();
    std::getline(std::cin, str, '\n');

    std::cout << "\n2. Edit input text\n";
    std::cout << "Before: " << '\'' << str << '\'' << std::endl;
    edit_text(str);
    std::cout << "After: " << '\'' << str << '\'' << std::endl;

    std::cout << "\n3. Reverse words\n";
    std::cout << "After reverse: " << '\'' << reverse_words(str) << '\'' << std::endl;

    std::cout << "\n4. Print words in columns with right-alignment\n";
    print_words(str);

    system(PAUSE);

    return 0;
}

void edit_text(std::string &str) {
    char *chara;
    unsigned short int state = 0, word_count = 0, word_size = 0, dot_count = 0;
    bool done = false;
    size_t pos = 0, mark = 0, word_start_pos = 0;
    int step = 0;
    while (!done) {
        if (pos >= str.size()) {
            done = true;
            continue;
        }
        chara = &str.at(pos);
        switch (state) {
            case 0:
                if (*chara == ' ') {
                    state = 2;
                    mark = pos++;
                } else if (*chara == '.') {
                    state = 3;
                    ++dot_count;
                } else if (std::isalnum(*chara)) {
                    state = 1;
                    word_size = 1;
                    word_start_pos = pos++;
                } else {
                    state = 4;
                    mark = pos;
                }
                break;
            case 1:
                if (std::isalnum(*chara)) {
                    if (std::isupper(*chara)) {
                        *chara = std::tolower(*chara);
                    }
                    ++word_size;
                    ++pos;
                } else {
                    state = 0;
                    if (word_size > WORD_SIZE_MAX) {
                        str.erase(word_start_pos - 1, pos - word_start_pos + 1);
                        pos -= (pos - word_start_pos + 1);
                    }
                    word_size = 0;
                    continue;
                }
                break;
            case 2:
                if (*chara == ' ') {
                    ++pos;
                    continue;
                } else {
                    str.erase(mark, pos - mark - 1);
                    pos -= (pos - mark);
                    ++pos;
                    state = 0;
                }
                break;
            case 3:
                if ((++pos) < str.size()) {
                    if (str.at(pos) == '.') {
                        ++dot_count;
                        continue;
                    } else {
                        if (dot_count > 3) {
                            str.erase(pos - (dot_count - 3), (dot_count - 3));
                            pos -= (dot_count - 3);
                            dot_count = 3;
                        }
                        if (dot_count == 3) {
                            state = 0;
                        } else {
                            str.erase(pos - (dot_count - 1));
                            done = true;
                        }
                        dot_count = 0;
                    }
                } else {
                    if (dot_count > 3) {
                        str.erase(pos - (dot_count - 3), (dot_count - 3));
                        dot_count = 3;
                    }
                    if (dot_count != 3) {
                        str.erase(pos - (dot_count - 1));
                    }
                    done = true;
                }
                break;
            case 4:
                if ((++pos) < str.size()) {
                    if (str.at(pos) == *chara) {
                        continue;
                    } else {
                        str.erase(mark, pos - (mark + 1));
                        pos -= (pos - (mark + 1));
                        state = 0;
                    }
                } else {
                    str.erase(mark, pos - (mark + 1));
                    done = true;
                }
                break;
            default:
                std::cerr << "Illegal state: " << state << std::endl;
                throw ("Illegal state: " + state);
        }
    }
}

std::string reverse_words(std::string &str) {
    std::stringstream ss;

    char *chara;
    unsigned short int state = 0;
    bool done = false;
    size_t pos = 0, word_start_pos = 0;
    int step = 0;
    while (!done) {
        if (pos >= str.size()) {
            done = true;
            if (state == 1) {
                auto iter = str.crend() - pos;
                while (iter < (str.crend() - word_start_pos)) {
                    ss << *iter;
                    iter++;
                }
            }
            continue;
        }
        chara = &str.at(pos);
        switch (state) {
            case 0:
                if (std::isalnum(*chara)) {
                    state = 1;
                    word_start_pos = pos;
                } else {
                    ss << *chara;
                    ++pos;
                    continue;
                }
                break;
            case 1:
                if (std::isalnum(*chara)) {
                    ++pos;
                    continue;
                } else {
                    state = 0;
                    auto iter = str.crend() - pos;
                    while (iter < (str.crend() - word_start_pos)) {
                        ss << *iter;
                        iter++;
                    }
                }
                break;
            default:
                std::cerr << "Illegal state: " << state << std::endl;
                throw ("Illegal state: " + state);
        }
    }

    return ss.str();
}

void print_words(std::string &str) {
    char *chara;
    unsigned short int state = 0, word_count = 0, max_word_size = 0;
    bool done = false;
    size_t pos = 0, word_start_pos = 0;
    int step = 0;
    std::vector<std::string> words;
    while (!done) {
        if (pos >= str.size()) {
            done = true;
            if (state == 1) {
                words.push_back(str.substr(word_start_pos, pos - word_start_pos));
                if ((pos - word_start_pos) > max_word_size) 
                    max_word_size = (pos - word_start_pos);
                word_start_pos = 0;
            }
            continue;
        }
        chara = &str.at(pos);
        switch (state) {
            case 0:
                if (std::isalnum(*chara)) {
                    state = 1;
                    word_start_pos = pos;
                } else {
                    ++pos;
                    continue;
                }
                break;
            case 1:
                if (std::isalnum(*chara)) {
                    ++pos;
                    continue;
                } else {
                    state = 0;
                    words.push_back(str.substr(word_start_pos, pos - word_start_pos));
                    if ((pos - word_start_pos) > max_word_size) 
                        max_word_size = (pos - word_start_pos);
                    word_start_pos = 0;
                }
                break;
            default:
                std::cerr << "Illegal state: " << state << std::endl;
                throw ("Illegal state: " + state);
        }
    }

    unsigned short int counter = 0, columns = words.size() > 20 ? 3 : 2;

    for (std::string &word : words) {
        std::cout << std::right << std::setw(max_word_size + 3) << word;
        if (++counter >= columns) {
            std::cout << std::endl;
            counter = 0;
        }
    }
    std::cout << std::endl;
}
