#include <iostream>
#include <cstring>
#include <Windows.h>
using namespace std;

class String {
private:
    char* data;
    size_t length;

public:
    // Конструктор по умолчанию
    String() {
        length = 0;
        data = new char[1];
        data[0] = '\0';
    }

    // Конструктор с параметром
    String(const char* str) {
        if (str) {
            length = 0;
            while (str[length] != '\0') length++;  // вычисляем длину вручную

            data = new char[length + 1];
            for (size_t i = 0; i <= length; i++) {  // копируем включая '\0'
                data[i] = str[i];
            }
        }
        else {
            length = 0;
            data = new char[1];
            data[0] = '\0';
        }
    }

    // Конструктор копирования
    String(const String& other) {
        length = other.length;
        data = new char[length + 1];
        for (size_t i = 0; i <= length; i++) {
            data[i] = other.data[i];
        }
    }

    // Конструктор перемещения
    String(String&& other) {
        data = other.data;
        length = other.length;
        other.data = new char[1];
        other.data[0] = '\0';
        other.length = 0;
    }

    // Деструктор
    ~String() {
        delete[] data;
    }

    // Оператор присваивания с копированием
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            for (size_t i = 0; i <= length; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Оператор присваивания с перемещением
    String& operator=(String&& other) {
        if (this != &other) {
            delete[] data;
            data = other.data;
            length = other.length;
            other.data = new char[1];
            other.data[0] = '\0';
            other.length = 0;
        }
        return *this;
    }

    // Перегрузка оператора [] для доступа к элементам
    char& operator[](size_t index) {
        return data[index];
    }

    // Перегрузка оператора [] для const объектов
    const char& operator[](size_t index) const {
        return data[index];
    }

    // Перегрузка оператора + для конкатенации
    String operator+(const String& other) const {
        String result;
        delete[] result.data;

        result.length = length + other.length;
        result.data = new char[result.length + 1];

        // Копируем первую строку
        for (size_t i = 0; i < length; i++) {
            result.data[i] = data[i];
        }

        // Копируем вторую строку
        for (size_t i = 0; i < other.length; i++) {
            result.data[length + i] = other.data[i];
        }

        result.data[result.length] = '\0';
        return result;
    }

    // Получить длину строки
    size_t getLength() const {
        return length;
    }

    // Получить строку как char*
    char* getString() {
        return data;
    }

    // Получить строку в формате const char*
    const char* getString() const {
        return data;
    }

    // ============ НОВЫЕ МЕТОДЫ ============

    // replace - замінює вказану кількість символів починаючи зі вказаного індексу на переданий рядок
    void replace(size_t index, size_t count, const String& str) {
        if (index > length) return; // Если индекс больше длины строки, не делаем ничего
        
        // Ограничиваем количество заменяемых символов
        if (index + count > length) {
            count = length - index;
        }
        
        // Вычисляем новую длину строки
        size_t new_length = length - count + str.length;
        
        // Создаем новый массив
        char* new_data = new char[new_length + 1];
        
        // Копируем часть до замены
        for (size_t i = 0; i < index; i++) {
            new_data[i] = data[i];
        }
        
        // Вставляем новую строку
        for (size_t i = 0; i < str.length; i++) {
            new_data[index + i] = str.data[i];
        }
        
        // Копируем оставшуюся часть
        for (size_t i = index + count; i < length; i++) {
            new_data[index + str.length + (i - index - count)] = data[i];
        }
        
        // Добавляем нуль-терминатор
        new_data[new_length] = '\0';
        
        // Заменяем старые данные
        delete[] data;
        data = new_data;
        length = new_length;
    }

    // substr - повертає копію підрядка між двома індексами
    String substr(size_t start, size_t end) const {
        if (start > length) start = length;
        if (end > length) end = length;
        if (start > end) {
            size_t temp = start;
            start = end;
            end = temp;
        }
        
        size_t substr_length = end - start;
        char* substr_data = new char[substr_length + 1];
        
        for (size_t i = 0; i < substr_length; i++) {
            substr_data[i] = data[start + i];
        }
        substr_data[substr_length] = '\0';
        
        String result(substr_data);
        delete[] substr_data;
        return result;
    }

    // empty - повертає true якщо в рядку нема символів, false - якщо є
    bool empty() const {
        return length == 0;
    }

    // insert - вставляє зазначений рядок на зазначений індекс
    void insert(size_t index, const String& str) {
        if (index > length) index = length; // Если индекс больше длины, вставляем в конец
        
        size_t new_length = length + str.length;
        char* new_data = new char[new_length + 1];
        
        // Копируем часть до места вставки
        for (size_t i = 0; i < index; i++) {
            new_data[i] = data[i];
        }
        
        // Вставляем новую строку
        for (size_t i = 0; i < str.length; i++) {
            new_data[index + i] = str.data[i];
        }
        
        // Копируем оставшуюся часть
        for (size_t i = index; i < length; i++) {
            new_data[str.length + i] = data[i];
        }
        
        // Добавляем нуль-терминатор
        new_data[new_length] = '\0';
        
        // Заменяем старые данные
        delete[] data;
        data = new_data;
        length = new_length;
    }

    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const String& str) {
        os << str.data;
        return os;
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    
    String str1("Hello World");
    String str2("C++");
    String str3;

    cout << "=== Исходные строки ===" << endl;
    cout << "str1: \"" << str1 << "\" (length: " << str1.getLength() << ")" << endl;
    cout << "str2: \"" << str2 << "\" (length: " << str2.getLength() << ")" << endl;
    cout << "str3: \"" << str3 << "\" (length: " << str3.getLength() << ")" << endl;

    cout << endl << "=== Тестирование empty() ===" << endl;
    cout << "str1.empty(): " << (str1.empty() ? "true" : "false") << endl;
    cout << "str3.empty(): " << (str3.empty() ? "true" : "false") << endl;

    cout << endl << "=== Тестирование substr() ===" << endl;
    String sub = str1.substr(6, 11); // "World"
    cout << "str1.substr(6, 11): \"" << sub << "\"" << endl;
    
    String sub2 = str1.substr(0, 5); // "Hello"
    cout << "str1.substr(0, 5): \"" << sub2 << "\"" << endl;

    cout << endl << "=== Тестирование insert() ===" << endl;
    String str4("Hello World");
    str4.insert(5, String(" beautiful"));
    cout << "После insert(5, \" beautiful\"): \"" << str4 << "\"" << endl;
    
    String str5("Programming");
    str5.insert(0, String("C++ "));
    cout << "После insert(0, \"C++ \"): \"" << str5 << "\"" << endl;

    cout << endl << "=== Тестирование replace() ===" << endl;
    String str6("Hello World");
    str6.replace(6, 5, String("C++"));
    cout << "После replace(6, 5, \"C++\"): \"" << str6 << "\"" << endl;
    
    String str7("Programming is fun");
    str7.replace(0, 11, String("C++"));
    cout << "После replace(0, 11, \"C++\"): \"" << str7 << "\"" << endl;

    cout << endl << "=== Комбинированное тестирование ===" << endl;
    String str8("Test");
    cout << "Исходная строка: \"" << str8 << "\"" << endl;
    
    str8.insert(4, String(" string"));
    cout << "После insert: \"" << str8 << "\"" << endl;
    
    String sub3 = str8.substr(5, 11);
    cout << "substr(5, 11): \"" << sub3 << "\"" << endl;
    
    str8.replace(0, 4, String("Demo"));
    cout << "После replace: \"" << str8 << "\"" << endl;
    
    cout << "empty(): " << (str8.empty() ? "true" : "false") << endl;

    return 0;
}
