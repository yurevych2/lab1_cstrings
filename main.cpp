#include <iostream>
#include "my_str_t.h"

int main() {
    //! CONSTRUCTOR MY_STR_T(size_t size, char initial)
    std::cout << "Let's create a string 'aaa' using my_str_t constructor." << std::endl;

    size_t my_number = 3;
    char my_charachter = 'a';
    my_str_t first_string(my_number, my_charachter);

    first_string.print();

    //! RESERVE(size_t new_capacity)
    std::cout << "Let's increase the capacity using reserve.\nCapacity: " << first_string.capacity() << std::endl;
    std::cout << "Set capacity to 7.\nCapacity:" << std::endl;
    size_t new_capacity = 7;
    first_string.reserve(new_capacity);
    std::cout << first_string.capacity() << std::endl;
    std::cout << "Set capacity to 3.\nCapacity:" << std::endl;
    new_capacity = 3;
    first_string.reserve(new_capacity);
    std::cout << first_string.capacity() << std::endl;

    //! CSTR()
    std::cout << "Use C_STR to get const pointer to cstr. The cstr I got: ";
    const char *cstr = first_string.c_str();
    for (size_t i = 0; cstr[i] != '\0'; ++i) {
        std::cout << cstr[i];
    }
    std::cout << '\n';

    //! my_str_t(const char *cstr)
    std::cout << "Let's use a constructor my_str_t(const char *cstr)." << std::endl;
    my_str_t copy_first_string(cstr);
    std::cout << "New string: ";
    copy_first_string.print();
    std::cout << "Capacity: " << copy_first_string.capacity() << ", size: "<< copy_first_string.size() << std::endl;
    std::cout << "C string: ";
    first_string.print();
    std::cout << "C string's capacity: " << first_string.capacity() << ", size: "<< first_string.size() << std::endl;

    //! my_str_t(const std::string &str)
    const std::string cppstring = "I_am_cppstring";
    std::cout << "CPP string: " << cppstring << std::endl;
    my_str_t copy_cppstring(cppstring);
    std::cout << "Copy of CPP string: ";
    copy_cppstring.print();
    std::cout << "Capacity: " << copy_cppstring.capacity() << ", size: "<< copy_cppstring.size() << std::endl;

    //! operator=
    std::cout << "Initial my_str_t #1: ";
    my_str_t str1("Hi");
    str1.print();
    std::cout << "Capacity: " << str1.capacity() << ", size: "<< str1.size() << std::endl;

    std::cout << "Initial my_str_t #2: ";
    my_str_t str2("World");
    str2.print();
    std::cout << "Capacity: " << str2.capacity() << ", size: "<< str2.size() << std::endl;

    std::cout << "Use operator=: " << std::endl;

    // Use the assignment operator
    str1 = str2;

    std::cout << "My_str_t #1: ";
    str1.print();
    std::cout << "Capacity: " << str1.capacity() << ", size: "<< str1.size() << std::endl;

    std::cout << "My_str_t #2: ";
    str2.print();
    std::cout << "Capacity: " << str2.capacity() << ", size: "<< str2.size() << std::endl;

    //! swap
    std::cout << "Initial my_str_t #1: ";
    my_str_t str1_swap("APPS");
    str1_swap.print();
    std::cout << "Capacity: " << str1_swap.capacity() << ", size: "<< str1_swap.size() << std::endl;

    std::cout << "Initial my_str_t #2: ";
    my_str_t str2_swap("TheBestFaculty");
    str2_swap.print();
    std::cout << "Capacity: " << str2_swap.capacity() << ", size: "<< str2_swap.size() << std::endl;

    std::cout << "Use swap." << std::endl;

    str1_swap.swap(str2_swap);

    std::cout << "Swaped my_str_t #1: ";
    str1_swap.print();
    std::cout << "Capacity: " << str1_swap.capacity() << ", size: "<< str1_swap.size() << std::endl;

    std::cout << "Swaped my_str_t #2: ";
    str2_swap.print();
    std::cout << "Capacity: " << str2_swap.capacity() << ", size: "<< str2_swap.size() << std::endl;

    //! my_str_t(const my_str_t &mystr)
    const my_str_t const_mystr("ConstantMyStringType");
    my_str_t copy_const_mystr(const_mystr);
    std::cout << "Check my_str_t(const my_str_t &mystr). Const my_str_t: ";
    const_mystr.print();
    std::cout << "Copy: ";
    copy_const_mystr.print();

    //! []

    try {
        char throw_error = copy_const_mystr.at(100);
        std::cout << throw_error << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }

    try {
        char throw_error = const_mystr.at(101);
        std::cout << throw_error << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }

    //! shrink_to_fit
    std::cout << "Let's increase the capacity of a string to 100.\nString: ";
    first_string.print();
    std::cout << "Capacity: " << first_string.capacity() << ", size: "<< first_string.size() << std::endl;
    size_t increased_capacity = 100;
    first_string.reserve(increased_capacity);
    std::cout << "Capacity: " << first_string.capacity() << ", size: "<< first_string.size() << std::endl;
    first_string.shrink_to_fit();
    std::cout << "Capacity: " << first_string.capacity() << ", size: "<< first_string.size() << std::endl;

    //! clear
    first_string.clear();
    std::cout << "Capacity: " << first_string.capacity() << ", size: "<< first_string.size() << std::endl;

    //! resize
    my_str_t small("the");
    my_str_t middle("best");
    my_str_t big("faculty");

    // new_size < size_m
    big.print();
    std::cout << "Capacity: " << big.capacity() << ", size: "<< big.size() << std::endl;
    big.resize(3, 'g');
    big.print();
    std::cout << "Capacity: " << big.capacity() << ", size: "<< big.size() << std::endl;

    // new_size > size_m but new_size <= capacity_m
    middle.print();
    std::cout << "Capacity: " << middle.capacity() << ", size: "<< middle.size() << std::endl;
    middle.resize(6, 'g');
    middle.print();
    std::cout << "Capacity: " << middle.capacity() << ", size: "<< middle.size() << std::endl;

    // new_size > capacity_m
    small.print();
    std::cout << "Capacity: " << small.capacity() << ", size: "<< small.size() << std::endl;
    small.resize(10, 'g');
    small.print();
    std::cout << "Capacity: " << small.capacity() << ", size: "<< small.size() << std::endl;

    //! append
    my_str_t first_part("TheBestFaculty");
    my_str_t second_part("IsAPP");
    first_part.print();
    std::cout << "Capacity: " << first_part.capacity() << ", size: " << first_part.size() << std::endl;
    first_part.append(second_part);
    first_part.print();
    std::cout << "Capacity: " << first_part.capacity() << ", size: " << first_part.size() << std::endl;
    first_part.append('S');
    first_part.print();
    std::cout << "Capacity: " << first_part.capacity() << ", size: " << first_part.size() << std::endl;
    first_part.append("(noJokes)");
    first_part.print();
    std::cout << "Capacity: " << first_part.capacity() << ", size: " << first_part.size() << std::endl;

    //! erase
    first_part.print();
    first_part.erase(3, 4);
    first_part.print();
    first_part.erase(20, 10);
    first_part.print();
    try {
        first_part.erase(100, 1);
        first_part.print();
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }

    //! find
    first_part.print();
    std::cout << first_part.find('u', 3) << std::endl;
    std::cout << first_part.find('u', 8) << std::endl;
    std::cout << first_part.find('J', 10) << std::endl;
    try {
        std::cout << first_part.find('u', 20) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }

    first_part.print();
    std::cout << first_part.find(std::string("APPS"), 10) << std::endl;
    try {
        std::cout << first_part.find(std::string("VeryVeryVeryVeryVeryLongString"), 25) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }
    try {
        std::cout << first_part.find(std::string("Lol"), 25) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }

    std::cout << first_part.find("Faculty", 0) << std::endl;

    //! substr
    my_str_t str_test("String");
    my_str_t substr_test = str_test.substr(2, 3);
    substr_test.print();
    std::cout << "Capacity: " << substr_test.capacity() << ", size: "<< substr_test.size() << std::endl;

    my_str_t substr_test_2 = str_test.substr(0, 10);
    substr_test_2.print();
    std::cout << "Capacity: " << substr_test_2.capacity() << ", size: "<< substr_test_2.size() << std::endl;

    //! insert

    my_str_t insert_test("BreadBread");
    my_str_t str_to_insert("Butter");
    insert_test.insert(5, str_to_insert);
    insert_test.print();

    insert_test.insert(0, str_to_insert);
    insert_test.print();

    insert_test.insert(22, str_to_insert);
    insert_test.print();

    insert_test.insert(28, '!');
    insert_test.print();

    my_str_t test_str("ILove");
    insert_test.insert(0, test_str.c_str());
    insert_test.print();

    //! ---
    my_str_t str_n(5, 'a');
    str_n.print();

    my_str_t str_n2("Hello, World!");
    str_n2.print();

    std::string std_str = "C++ string";
    my_str_t str3(std_str);
    str3.print();

    //! assignment operator
    my_str_t str4 = str3;
    str4.print();

    //! comparison operators
    if (str_n != str_n2) {
        std::cout << "str1 and str2 are not equal" << std::endl;
    }

    if (str3 == str4) {
        std::cout << "str3 and str4 are equal" << std::endl;
    }

    //!input/output operators
//    std::cout << "Enter a string: ";
//    my_str_t input_str(1, ' ');
//    std::cin >> input_str;
//    std::cout << "You entered: " << input_str << std::endl;

    //! readline function
//    std::cout << "Enter a full line: ";
//    std::cin.ignore();
//    readline(std::cin, input_str);
//    std::cout << "You entered the line: " << input_str << std::endl;

    //! > >= < <=
    my_str_t a("a");
    my_str_t a_dupl("a");
    my_str_t b("b");

    std::cout << (a > b) << std::endl;
    std::cout << (a < b) << std::endl;
    std::cout << (a >= a_dupl) << std::endl;
    std::cout << (a <= a_dupl) << std::endl;

    const char* c = "c";
    const char* c_dupl = "c";
    const char* d = "d";

    std::cout << (c > d) << std::endl;
    std::cout << (c < d) << std::endl;
    std::cout << (c >= c_dupl) << std::endl;
    std::cout << (c <= c_dupl) << std::endl;
    std::cout << (c == c_dupl) << std::endl;
    std::cout << (c != c_dupl) << std::endl;

    return 0;
}