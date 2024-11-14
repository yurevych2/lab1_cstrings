// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>
#include "my_str_t.h"
#include <string>
#include <stdexcept>


my_str_t::my_str_t(size_t size, char initial) :
        data_m{nullptr}, capacity_m{0}, size_m{0} {
    reserve(SIZE_MULT * std::max(MIN_STR_LEN, size));

    size_m = size;

    for (size_t i = 0; i < capacity_m; ++i) { // fill the block with initial char
        data_m[i] = initial;
    }
}

char *my_str_t::data() const noexcept {
    return data_m;
}

size_t my_str_t::capacity() const noexcept {
    return capacity_m;
}

size_t my_str_t::size() const noexcept {
    return size_m;
}

void my_str_t::print() const {
    for (size_t i = 0; i < size_m; ++i) {
        std::cout << data()[i];
    }

    std::cout << "\n";
}

void my_str_t::reserve(size_t new_capacity) {
    if (new_capacity < capacity_m) {
        return; // do not do anything
    }

    capacity_m = new_capacity; // set the capacity_m to new_capacity

    char *new_data_m = new char[capacity_m]; // allocate memory for new_capacity chars

    for (size_t i = 0; i < size_m; ++i) { // copy size_m byte to a new block of memory
        new_data_m[i] = data_m[i];
    }

    delete[] data_m; // free previously allocated memory
    data_m = new_data_m; // set pointer to newly allocated memory

    data_m[size_m] = '\0'; // last symbol is '\0' to make the implementation of c_str trivial
}

my_str_t::my_str_t(const char *cstr) :
        data_m{nullptr}, capacity_m{0}, size_m{0} {
    if (cstr == nullptr) {
        reserve(SIZE_MULT * MIN_STR_LEN);
    } else {
        size_t cstr_len = 0;
        for (size_t i = 0; cstr[i] != '\0'; ++i) {
            ++cstr_len;
        }

        size_m = cstr_len;
        capacity_m = SIZE_MULT * size_m;

        data_m = new char[capacity_m]; // allocate memory for new_capacity chars

        for (size_t i = 0; i < size_m; ++i) { // copy size_m byte to a new block of memory
            data_m[i] = cstr[i];
        }

        data_m[size_m] = '\0'; // last symbol is '\0' to make the implementation of c_str trivial
    }
}

my_str_t::my_str_t(const std::string &str) {
    size_m = str.size();
    capacity_m = SIZE_MULT * size_m;
    data_m = new char[capacity_m];
    for (size_t i = 0; i < size_m; ++i) {
        data_m[i] = str[i];
    }

    // why do not I set last symbol to '/0'?
}

my_str_t::my_str_t(const my_str_t &mystr) : // test it!
        data_m{nullptr}, capacity_m{0}, size_m{0} {
    reserve(SIZE_MULT * std::max(MIN_STR_LEN, mystr.size_m));

    size_m = mystr.size_m;

    for (size_t i = 0; i < size_m; ++i) {
        data_m[i] = mystr.data_m[i];
    }
}

my_str_t &my_str_t::operator=(const my_str_t &mystr) {
    my_str_t copy_mystr = my_str_t(mystr);
    swap(copy_mystr);

    return *this;
}

void my_str_t::swap(my_str_t &other) noexcept {
    std::swap(data_m, other.data_m);
    std::swap(size_m, other.size_m);
    std::swap(capacity_m, other.capacity_m);
}

const char *my_str_t::c_str() const {
    return data_m;
}

my_str_t::~my_str_t() {
    delete[] data_m;
}

char &my_str_t::operator[](size_t idx) {
    return data_m[idx];
}

const char &my_str_t::operator[](size_t idx) const {
    return data_m[idx];
}

char &my_str_t::at(size_t idx) {
    if (size_m <= idx) {
        throw std::out_of_range("Index is out of range.");
    }
    return data_m[idx];
}

const char &my_str_t::at(size_t idx) const {
    if (size_m <= idx) {
        throw std::out_of_range("Index is out of range.");
    }
    return data_m[idx];
}

void my_str_t::shrink_to_fit() {
    my_str_t copy_mystr = my_str_t(*this);
    swap(copy_mystr);
}

void my_str_t::clear() {
    size_m = 0;
}

void my_str_t::resize(size_t new_size, char new_char) {
    if (new_size > capacity_m) {
        reserve(SIZE_MULT * new_size);
    }

    if (new_size < size_m) {
        size_m = new_size;
        data_m[size_m] = '\0'; // I could write it once after if-else
    } else {
        for (size_t i = size_m; i < new_size; ++i) {
            data_m[i] = new_char;
        }

        size_m = new_size;
        data_m[size_m] = '\0';
    }
}

void my_str_t::append(const my_str_t &str) {
    size_t new_size = size_m + str.size_m;
    if (new_size >= capacity_m) {
        reserve(SIZE_MULT * new_size);
    }

    for (size_t i = 0; i < str.size_m; ++i) {
        data_m[size_m + i] = str[i];
    }

    size_m = new_size;
    data_m[size_m] = '\0';
}

void my_str_t::append(char c) {
    if (size_m + 1 >= capacity_m) {
        reserve(SIZE_MULT * (size_m + 1));
    }

    data_m[size_m] = c;
    size_m++;
    data_m[size_m] = '\0';
}

void my_str_t::append(const char *cstr) {
    if (cstr == nullptr) {
        return;
    }

    my_str_t cpp_str(cstr); // it was stupid as we have insert for const char *cstr
    append(cpp_str); // just like the Oleg's joke about a kettle and an algorithm
}

void my_str_t::erase(size_t begin, size_t size) {
    if (begin > size_m) {
        throw std::out_of_range("The beginning is out of range.");
    }

    size_t chars_to_erase = (begin + size > size_m) ? size_m - begin : size;

    for (size_t i = begin; i + chars_to_erase < size_m; ++i) {
        data_m[i] = data_m[i + chars_to_erase];
    }

    size_m -= chars_to_erase;
    data_m[size_m] = '\0';
}

size_t my_str_t::find(char c, size_t idx) {
    if (idx > size_m) {
        throw std::out_of_range("Index is out of range.");
    }

    for (size_t i = idx; i < size_m; i++) {
        if (data_m[i] == c) {
            return i;
        }
    }

    return not_found;
}

size_t my_str_t::find(const std::string &str, size_t idx) {
    if (idx > size_m) {
        throw std::out_of_range("Index is out of range.");
    }

    size_t str_len = 0;
    for (size_t i = 0; str[i] != '\0'; ++i) {
        ++str_len;
    }

    if (idx + str_len >= size_m) {
        return not_found;
    }

    for (size_t i = idx; i <= size_m - str_len; ++i) {
        // check if substring matches at position i
        size_t j = 0;
        while ((j < str_len) && (data_m[i + j] == str[j])) {
            ++j;
        }

        if (j == str_len) {
            return i;
        }
    }

    return not_found;
}

size_t my_str_t::find(const char *cstr, size_t idx) {
    if (cstr == nullptr) {
        return not_found;
    }

    if (idx > size_m) {
        throw std::out_of_range("Index is out of range.");
    }

    size_t str_len = 0;
    for (size_t i = 0; cstr[i] != '\0'; ++i) {
        ++str_len;
    }

    if (idx + str_len >= size_m) {
        return not_found;
    }

    for (size_t i = idx; i <= size_m - str_len; ++i) {
        // check if substring matches at position i
        size_t j = 0;
        while ((j < str_len) && (data_m[i + j] == cstr[j])) {
            ++j;
        }

        if (j == str_len) {
            return i;
        }
    }

    return not_found;
}

my_str_t my_str_t::substr(size_t begin, size_t size) {
    if (begin > size_m) {
        throw std::out_of_range("Beginning is out of range.");
    }

    size_t substr_len = (begin + size > size_m) ? size_m - begin : size;

    my_str_t substring{substr_len, 'i'};
    for (size_t i = 0; i < substr_len; ++i) {
        substring.data_m[i] = data_m[begin + i];
    }

    return substring;
}

void my_str_t::insert(size_t idx, const my_str_t &str) {
    if (idx > size_m) {
        throw std::out_of_range("Index is out of range.");
    }

    size_t new_size = size_m + str.size_m;

    if (new_size >= capacity_m) {
        size_t new_capacity = SIZE_MULT * new_size;
        char *new_data = new char[new_capacity];

        // copy the portion before idx
        memmove(new_data, data_m, idx);

        // copy the new string content
        memmove(new_data + idx, str.data_m, str.size_m);

        // copy the rest of the original string after idx
        memmove(new_data + idx + str.size_m, data_m + idx, size_m - idx);

        new_data[new_size] = '\0'; // repeated line

        delete[] data_m;
        data_m = new_data;
        capacity_m = new_capacity;
    } else {
        // enough capacity: shift the existing content and insert new string
        memmove(data_m + idx + str.size_m, data_m + idx, size_m - idx);
        memmove(data_m + idx, str.data_m, str.size_m);
    }

    size_m = new_size;  // update the size
    data_m[size_m] = '\0';  // ensure null-termination
}

void my_str_t::insert(size_t idx, char c) {
    if (idx > size_m) {
        throw std::out_of_range("Index is out of range");
    }

    // check if we need to allocate more memory
    if (size_m + 1 >= capacity_m) {
        size_t new_capacity = SIZE_MULT * (size_m + 1);
        char *new_data = new char[new_capacity];

        // move the data before idx to the new_data array
        memmove(new_data, data_m, idx);

        // insert the character
        new_data[idx] = c;

        // copy the rest of the original string after idx
        memmove(new_data + idx + 1, data_m + idx, size_m - idx);

        new_data[size_m + 1] = '\0';

        delete[] data_m;
        data_m = new_data;
        capacity_m = new_capacity;
    } else {
        // if there's enough capacity, shift the characters and insert the new one
        memmove(data_m + idx + 1, data_m + idx, size_m - idx);
        data_m[idx] = c;
    }

    size_m += 1;
    data_m[size_m] = '\0';
}

void my_str_t::insert(size_t idx, const char *cstr) {
    if (cstr == nullptr) {
        return;
    }

    if (idx > size_m) {
        throw std::out_of_range("Index is out of range");
    }

    size_t cstr_len = 0;
    while (cstr[cstr_len] != '\0') {
        ++cstr_len;
    }

    size_t new_size = size_m + cstr_len;

    if (new_size >= capacity_m) {
        size_t new_capacity = SIZE_MULT * new_size;
        char *new_data = new char[new_capacity];

        // copy the portion before idx
        memmove(new_data, data_m, idx);

        // insert the C-string content
        memmove(new_data + idx, cstr, cstr_len);

        // copy the rest of the original string after idx
        memmove(new_data + idx + cstr_len, data_m + idx, size_m - idx);

        new_data[new_size] = '\0';

        delete[] data_m;
        data_m = new_data;
        capacity_m = new_capacity;
    } else {
        // if enough capacity, just insert the string in place
        memmove(data_m + idx + cstr_len, data_m + idx, size_m - idx);  // shift existing data
        memmove(data_m + idx, cstr, cstr_len);  // insert new content
    }

    size_m = new_size;
    data_m[size_m] = '\0';
}

bool operator==(const my_str_t &str1, const my_str_t &str2) {
    if (str1.size() != str2.size()) {
        return false;
    }
    for (size_t i = 0; i < str1.size(); ++i) {
        if (str1.data()[i] != str2.data()[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const my_str_t &str1, const my_str_t &str2) {
    return !(str1 == str2);
}

bool operator>(const my_str_t &str1, const my_str_t &str2) {
    size_t min_size = (str1.size() < str2.size()) ? str1.size() : str2.size();
    for (size_t i = 0; i < min_size; ++i) {
        if (str1.data()[i] > str2.data()[i]) {
            return true;
        } else if (str1.data()[i] < str2.data()[i]) {
            return false;
        }
    }
    return str1.size() > str2.size();
}

bool operator>=(const my_str_t &str1, const my_str_t &str2) {
    return (str1 > str2) || (str1 == str2);
}

bool operator<(const my_str_t &str1, const my_str_t &str2) {
    return !(str1 >= str2);
}

bool operator<=(const my_str_t &str1, const my_str_t &str2) {
    return !(str1 > str2);
}

bool operator==(const my_str_t &str1, const char *cstr2) {
    size_t i = 0;
    while ((i < str1.size()) && (cstr2[i] != '\0')) {
        if (str1.data()[i] != cstr2[i]) {
            return false;
        }
        ++i;
    }
    return (i == str1.size() && cstr2[i] == '\0');
}

bool operator!=(const my_str_t &str1, const char *cstr2) {
    return !(str1 == cstr2);
}

bool operator>(const my_str_t &str1, const char *cstr2) {
    size_t i = 0;
    while (i < str1.size() && cstr2[i] != '\0') {
        if (str1.data()[i] > cstr2[i]) {
            return true;
        } else if (str1.data()[i] < cstr2[i]) {
            return false;
        }
        ++i;
    }
    return str1.size() > i;
}

bool operator>=(const my_str_t &str1, const char *cstr2) {
    return (str1 > cstr2) || (str1 == cstr2);
}

bool operator<(const my_str_t &str1, const char *cstr2) {
    return !(str1 >= cstr2);
}

bool operator<=(const my_str_t &str1, const char *cstr2) {
    return !(str1 > cstr2);
}

bool operator==(const char *cstr1, const my_str_t &str2) {
    return (str2 == cstr1);
}

bool operator!=(const char *cstr1, const my_str_t &str2) {
    return !(str2 == cstr1);
}

bool operator>(const char *cstr1, const my_str_t &str2) {
    size_t i = 0;
    while (i < str2.size() && cstr1[i] != '\0') {
        if (cstr1[i] > str2.data()[i]) {
            return true;
        } else if (cstr1[i] < str2.data()[i]) {
            return false;
        }
        ++i;
    }
    return cstr1[i] != '\0';
}

bool operator>=(const char *cstr1, const my_str_t &str2) {
    return (cstr1 > str2) || (cstr1 == str2);
}

bool operator<(const char *cstr1, const my_str_t &str2) {
    return !(cstr1 >= str2);
}

bool operator<=(const char *cstr1, const my_str_t &str2) {
    return !(cstr1 > str2);
}

std::ostream &operator<<(std::ostream &stream, const my_str_t &str) {
    stream << str.c_str();
    return stream;
}

std::istream &operator>>(std::istream &stream, my_str_t &str) {
    str.clear();

    char ch;
    // skip leading whitespace
    while (stream.get(ch) && std::isspace(ch)) {
        // skip
    }

    // start reading characters until encountering a whitespace
    if (stream) {
        do {
            str.append(ch);
        } while (stream.get(ch) && !std::isspace(ch));
    }

    return stream;
}

std::istream &readline(std::istream &stream, my_str_t &str) {
    str.clear();

    char ch;
    // read characters until newline
    while (stream.get(ch)) {
        if (ch == '\n') {
            break;
        }
        str.append(ch);
    }

    return stream;
}
