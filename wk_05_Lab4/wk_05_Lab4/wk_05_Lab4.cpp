/*
//Используя инструментарий шаблонов С++, напишите быструю сортировку Хоара, 
//позволяющую сортировать массив из одинаковых элементов произвольного типа, 
//допускающего копирование.﻿В качестве зависимости для сравнения используйте идею "объекта компаратора": абстрактный класс, 
//содержащий единственный метод, устанавливающий порядок элементов

#include <iostream>
#include <fstream>

struct Student 
{
    char name[40];
    int age;

    friend std::ostream& operator<< (std::ostream& out, const Student& student);
};

std::ostream& operator<< (std::ostream& out, const Student& student)
{
    out << "Student(" << student.name << ", " << student.age << ')';
    return out;
}

template <typename T> bool comparator(T const &lha, T const &rha) {
    return 0;
}

template<> bool comparator<int>(int const &lha, int const &rha) {
    return lha > rha;
}

template<> bool comparator<float>(float const& lha, float const& rha) {
    return lha - rha > 0.1;
}

template<> bool comparator<Student>(Student const& lha, Student const& rha) {
    return lha.age > rha.age;
}

template <typename T>
void qsort(T* array, int size) {
    int l = 0;
    int r = size - 1;
    T mid = array[size / 2];

    do {
        while (comparator(array[l], mid)) l++;
        while (comparator(mid, array[r])) r--;

        if (l <= r) {
            T tmp = array[l];
            array[l] = array[r];
            array[r] = tmp;

            l++;
            r--;
        }
        for (int i = 0; i < size; i++) std::cout << array[i] << " ";
        std::cout << "\n";

    } while (l <= r);

    if (r > 0) qsort(array, r + 1);
    if (l < size) qsort(&array[l], size - l);
}

int main() {

    int size = 20;

    //проверка для int
    int* array_i = new int[size] { 0 };
    for (int i = 0; i < size; i++) array_i[i] = i * 3 - 7;

    qsort(array_i, size);
    for (int i = 0; i < size; i++) std::cout << array_i[i] << " ";
    std::cout << std::endl;

    delete[] array_i;

    //проверка для float
    float* array_f = new float[size];
    for (int i = 0; i < size; i++) array_f[i] = (float)i * 3.2 - 0.7;

    qsort(array_f, size);
    for (int i = 0; i < size; i++) std::cout << array_f[i] << " ";
    std::cout << std::endl;

    delete[] array_f;

    //проверка для Student
    Student group[5] = { {"MoominTroll", 17}, {"Snorkmaiden", 16}, {"Snufkin", 18}, {"Too-Ticky", 17}, {"Toft", 16} };
    
    qsort(group, 5);
    for (int i = 0; i < 5; i++) std::cout << group[i] << " ";
    std::cout << std::endl;

    return 0;
}
*/

//Используя инструментарий шаблонов С++, напишите реализацию очереди с приоритетом. Очередь должна быть представлена классом PriorityQueue 
//со следующими методами:
//•конструктор по умолчанию, создающий пустую очередь с приоритетом;
//•метод push для добавления нового значения в очередь;
//•метод peek для чтения верхнего элемента очереди, но не удаления элемента;
//•метод poll для удаления верхнего элемента очереди;
//•метод is_empty, который возвращает true, если очередь пуста, иначе - false.
//Для определение приоритета используйте идею компаратора из предыдущего пункта. Компаратор должен внедряться в очередь 
//в конструкторе(сохраняется ссылка или указатель).
//Так как очередь будет выделять память под новые элементы, дополните методы методом void free(), который освобождает всю выделенную ранее память.

#include <iostream>
#include <vector>

template <typename T> bool less(T a, T b);

template <> bool less<int>(int a, int b) {
    return a < b;
}

template <typename T, typename C = std::vector<T>>
class priority_queue 
{
public:
    C vector;
    int size;
    priority_queue() : vector() {}

    bool is_empty() {
        return (size == 0);
    }

    void push(T a) {
        if (is_empty()) {
            vector.push_back(a);
            size += 1;
        }
        else 
            for (int i = 0; i < size; i++) {
                if (less(a, vector[i])) {
                    vector.emplace(vector.begin() + i, a);
                    size += 1;
                    break;
                }
                else {
                    vector.push_back(a);
                    size += 1;
                    break;
                }
            }
    }

    T peek() {
        if (is_empty()) {
            std::cout << "the queue is empty, you shouldn't use this fuction" << std::endl;
            return 0;
        }  
        else return vector[size - 1];
    }

    void poll() {
        if (is_empty()) std::cout << "the queue is empty, you shouldn't use this fuction" << std::endl;
        else {
            vector.pop_back();
            size -= 1;
        }
    }

    void free() {
        size = 0;
        vector.clear();
    }
};

int main() 
{
    priority_queue<int> p;
    std::cout << p.is_empty() << std::endl;
    p.push(2);
    std::cout << p.vector[0] << std::endl;
    std::cout << p.is_empty() << std::endl;
    p.push(7);
    std::cout << p.peek() << std::endl;
    p.push(1);
    std::cout << p.vector[0] << std::endl;
    p.poll();
    //std::cout << p.vector[2] << std::endl; //error

    return 0;
}