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

    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const String& str) {
        os << str.data;
        return os;
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    String str1("Hello");
    String str2(" World");
    String str3;

    cout << endl << "=== Тестирование функций ===" << endl;
    cout << "str1: " << str1 << " (length: " << str1.getLength() << ")" << endl;
    cout << "str2: " << str2 << " (length: " << str2.getLength() << ")" << endl;
    cout << "str3: " << str3 << " (length: " << str3.getLength() << ")" << endl;

    cout << endl << "=== Конкатенация ===" << endl;
    String str4 = str1 + str2;
    cout << "str1 + str2 = " << str4 << endl;

    cout << endl << "=== Тестирование оператора [] ===" << endl;
    cout << "str1[1] = " << str1[1] << endl;
    str1[1] = 'a';
    cout << "После изменения str1[1] = 'a': " << str1 << endl;

    cout << endl << "=== Конструктор копирования ===" << endl;
    String str5 = str4;
    cout << "str5 (копия str4): " << str5 << endl;

    cout << endl << "=== Оператор присваивания ===" << endl;
    str3 = str1;
    cout << "str3 = str1: " << str3 << endl;

    cout << endl << "=== Конструктор перемещения ===" << endl;
    String str6 = String("Temporary");
    cout << "str6 (перемещение): " << str6 << endl;

    cout << endl << "=== Оператор присваивания с перемещением ===" << endl;
    String str7;
    str7 = String("Another temp");
    cout << "str7 (перемещение): " << str7 << endl;

    cout << endl << "=== Получение const char* ===" << endl;
    const char* cstr = str1.getString();
    cout << "const char* from str1: " << cstr << endl;
    return 0;
}