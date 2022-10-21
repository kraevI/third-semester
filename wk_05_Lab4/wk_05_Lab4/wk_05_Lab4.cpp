//Используя инструментарий шаблонов С++, напишите быструю сортировку Хоара, 
//позволяющую сортировать массив из одинаковых элементов произвольного типа, 
//допускающего копирование.﻿В качестве зависимости для сравнения используйте идею "объекта компаратора": абстрактный класс, 
//содержащий единственный метод, устанавливающий порядок элементов

#include <iostream>
#include <fstream>

struct Student {
    char name[40];
    int age;

    friend std::ostream& operator<< (std::ostream& out, const Student& student);
};

std::ostream& operator<< (std::ostream& out, const Student& student){

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

    //проверка для студентов
    Student group[5] = { {"MoominTroll", 17}, {"Snorkmaiden", 16}, {"Snufkin", 18}, {"Too-Ticky", 17}, {"Toft", 16} };
    
    qsort(group, 5);
    for (int i = 0; i < 5; i++) std::cout << group[i] << " ";
    std::cout << std::endl;

    return 0;
}
