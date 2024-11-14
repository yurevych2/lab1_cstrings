// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef LAB1_CSTRINGS_YUREVYCH_MY_STR_T_H
#define LAB1_CSTRINGS_YUREVYCH_MY_STR_T_H


class my_str_t {
    static constexpr size_t MIN_STR_LEN = 2; // reccomendations, compilation time constant
    static constexpr size_t SIZE_MULT = 2; // reccomendations, compilation time constant

private:
    char *data_m; // Вказівник на блок пам'яті
    size_t capacity_m; // Розмір блока
    size_t size_m; // Фактичний розмір стрічки
// Рекомендовано, щоб блок пам'яті містив на 1 байт більше,
// ніж capacity_m чи максимальний size_m -- це робить
// реалізацію c_str() тривіальною.
public:
    //! Створює стрічку із size копій літери initial
    //! capacity_m встановлює рівним або більшим за size
    //! Обробка помилок конструкторами:
    //! Не повинні заважати пропагуванню виключення
    //! std::bad_alloc.
    my_str_t(size_t size, char initial);

    //! Getter. Returns data_m.
    [[nodiscard]] char *data() const noexcept; // [[nodiscard]] - error if the output is not saved

    //! Getter. Returns capacity_m.
    [[nodiscard]] size_t capacity() const noexcept;

    //! Getter. Returns size_m.
    [[nodiscard]] size_t size() const noexcept;

    //! Prints the string in a single line
    void print() const;

    //! Копіює вміст С-стрічки, вимоги до capacity_m -- ті ж, що вище
    explicit my_str_t(const char *cstr); // does not change class of an argument if it is another

    //! Копіює стрічку С++, вимоги до capacity_m -- ті ж, що вище
    explicit my_str_t(const std::string &str);

    //! Конструктор копіювання
    my_str_t(const my_str_t &mystr);

    //! Оператор присвоєння
    //! Має повертати посилання на самого себе --
    //! на об'єкт, якому присвоювали
    my_str_t &operator=(const my_str_t &mystr);

//! Advanced!
//! Реалізація не є складною, але вимагає розуміння суті
// my_str_t(my_str_t&& mystr);
//my_str_t& operator=(my_str_t&& mystr);

    //! Обмінює вміст цієї стрічки із other, за допомогою
    //! обміну вказівників
    //! noexcept вказує, що функція ніколи не кидає виключень
    void swap(my_str_t &other) noexcept;

    //! Два варіанти оператора індексації -- для константних та
    //! неконстантних об'єктів
    //! Обробка помилок:
    //! Не перевіряє виходу за межі.
    char &operator[](size_t idx);

    const char &operator[](size_t idx) const;

    //! Те ж, що й оператори []
    //! Обробка помилок:
    //! Якщо idx >= size_m -- кидає виключення std::out_of_range.
    [[nodiscard]] char &at(size_t idx);

    [[nodiscard]] const char &at(size_t idx) const;

    //! Збільшує capacity до new_capacity.
    //! Якщо new_capacity менша за capacity_m -- не робить нічого
    //! Для збільшення -- виділяє новий блок пам'яті,
    //! копіює size_m байт -- фактичний вміст стрічки,
    //! у цей новий блок, звільняє старий блок, а
    //! вказівник на новий зберігає в data_m.
    //! Обробка помилок:
    //! Не повинні заважати пропагуванню виключення
    //! std::bad_alloc.
    void reserve(size_t new_capacity);

    //! Зменшує розмір до мінімального необхідного.
    //! Мінімально необхідний -- це size_m.
    //! Для оптимізації подальшого зростання стрічки,
    //! він може бути трохи більшим -- на розсуд реалізації.
    //! Обробка помилок:
    //! Не повинні заважати пропагуванню виключення
    //! std::bad_alloc.
    void shrink_to_fit();

    //! Змінює фактичний розмір стрічки.
    //! 1. Якщо новий розмір менший за старий -- лише оновлює
    //! значення в size_m (*added: set data_m[size_m] equal to '\0').
    //! 2. Якщо new_size > size_m, але <= capacity_m,
    //! то змінює size_m і нові літери (*added: set data_m[new_size] equal to '\0').
    //! 3. Якщо new_size > capacity_m, збільшує зарезервовану
    //! пам'ять за допомогою виклику reserve(), далі -- як в п. 2
    //! Обробка помилок:
    //! Не повинні заважати пропагуванню виключення
    //! std::bad_alloc.
    void resize(size_t new_size, char new_char = ' ');

    //! Очищає вміст стрічки -- для цього достатньо
    //! зробити size_m = 0.
    void clear();

    //! Вставляє передану стрічку типу my_str_t, чи літеру,
    //! чи С-стрічку, починаючи з літери idx,
    //! зсуваючи літеру з позиції idx і правіше праворуч.
    //! Обробка помилок:
    //! Якщо idx > size_m -- кидає виключення std::out_of_range
    void insert(size_t idx, const my_str_t &str);

    //! Ця функція -- служить для оптимізації, щоб не
    //! довелося спочатку створювати із літери c стрічку my_str_t, а
    //! потім вставляти. Навіть якщо компілятор зробив би це
    //! автоматично -- це повільно.
    void insert(size_t idx, char c);

    //! Аналогічна оптимізація для C-стрічок
    void insert(size_t idx, const char *cstr);

    //! Додає стрічку чи літеру в кінці стрічки.
    //! Обробка помилок:
    //! Не повинні заважати пропагуванню виключення
    //! std::bad_alloc.
    void append(const my_str_t &str);

    void append(char c);

    void append(const char *cstr);

    //! Видаляє size літер, починаючи з індексу begin.
    //! Літери праворуч від видаленого шматка зсуваються
    //! на size ліворуч.
    //! Обробка помилок:
    //! Якщо begin > size_m -- кидає виключення std::out_of_range.
    //! Але якщо стрічка містить менше символів для стирання,
    //! ніж потрібно -- це не помилка, видаляє всі до кінця.
    void erase(size_t begin, size_t size);

    //! Повертає вказівник на С-стрічку, яка відповідає
    //! цьому об'єкту. Якщо виділяти один зайвий байт,
    //! як описано в документації на конструтор, то їй
    //! достатньо зберегти нульовий байт у позиції
    //! data_m[size_m] і повернути data_m.
    [[nodiscard]] const char *c_str() const;

    //! Функції find шукають вказану літеру чи стрічку,
    //! починаючи із idx. Якщо не знайдено, повертає
    //! константу my_str_t::not_found
    //! Обробка помилок:
    //! Якщо idx > size_m -- кидає виключення std::out_of_range.
    static constexpr size_t not_found = -1;

    size_t find(char c, size_t idx = 0);

    size_t find(const std::string &str, size_t idx = 0);

    size_t find(const char *cstr, size_t idx = 0);

    //! Скопіювати підстрічку, із begin включно,
    //! по begin+size не включно ([begin, begin+size)).
    //! Якщо end за межами початкової стрічки -- це не помилка,
    //! копіювати всі символи до кінця.
    //! beg має бути в її межах -- якщо begin>size, це помилка.
    //! Обробка помилок:
    //! Якщо begin > size_m -- кидає виключення std::out_of_range.
    my_str_t substr(size_t begin, size_t size);

    //! Деструктор.
    ~my_str_t();

};

//! Оператори вводу-виводу.
//! Увага, в загальному випадку, operator<< і operator>> мають
//! бути симетричними: оператор вводу повинен вміти прочитати те,
//! що вивів оператор виводу.
//! Для стрічок ця умова дещо спрощена -- operator<< має вивести
//! всю стрічку, а operator>> -- пропустити всі whitespace,
//! та прочитати одне слово -- до наступного whitespace.
//! Детальніше -- див. поведінку operator>> для std::string та
//! маніпулятор типу std::skipws.
std::ostream &operator<<(std::ostream &stream, const my_str_t &str);

//! Повинен пропустити всі whitespace, та прочитати одне слово --
//! до наступного whitespace.
//! Тут, для простоти, варто читати посимвольно.
//! УВАГА! В загальному випадку, читати по одному символу --
//! надміру повільно! Але тут це єдиний простий спосіб.
std::istream &operator>>(std::istream &stream, my_str_t &str);

//! Оператори порівняння.
//! Or operator <=> for advanced users!
bool operator==(const my_str_t &str1, const my_str_t &str2);

bool operator!=(const my_str_t &str1, const my_str_t &str2);

bool operator>(const my_str_t &str1, const my_str_t &str2);

bool operator>=(const my_str_t &str1, const my_str_t &str2);

bool operator<(const my_str_t &str1, const my_str_t &str2);

bool operator<=(const my_str_t &str1, const my_str_t &str2);

//! Same for the const char*
bool operator==(const my_str_t &str1, const char *cstr2);

bool operator!=(const my_str_t &str1, const char *cstr2);

bool operator>(const my_str_t &str1, const char *cstr2);

bool operator>=(const my_str_t &str1, const char *cstr2);

bool operator<(const my_str_t &str1, const char *cstr2);

bool operator<=(const my_str_t &str1, const char *cstr2);

bool operator==(const char *cstr1, const my_str_t &str2);

bool operator!=(const char *cstr1, const my_str_t &str2);

bool operator>(const char *cstr1, const my_str_t &str2);

bool operator>=(const char *cstr1, const my_str_t &str2);

bool operator<(const char *cstr1, const my_str_t &str2);

bool operator<=(const char *cstr1, const my_str_t &str2);

//! Функція, яка читає потік до символу \n і зберігає її в str,
//! очистивши стрічку перед тим.
std::istream &readline(std::istream &stream, my_str_t &str);

#endif //LAB1_CSTRINGS_YUREVYCH_MY_STR_T_H
