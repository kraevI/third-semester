//Задание: написать обобщённую функцию быстрой сортировки.

//Все характеристики, по которым можно сортировать списки, числовые, т.е int, double и т.д. 
//  Массив char-ов, например, если будет сортироваться, то только после отображения символов в их порядковый номер,
//      а массив строк - в их длину. Но для сортировки чисел достаточно написать только одну функцию - для самого большого
//          типа, остальные же можно к нему привести перед сортировкой. Поэтому моя функция(qsort) будет иметь аргумент - 
//              функцию, парную для типа элементов массива, которая должна вызываться 
//                  в начале(для отображения в числовую хар-ку) и в конце(для обратной операции).


#include <iostream>
#include <time.h>
#include <Windows.h>

void qsort_forDouble(double* array, int size, bool order) {   
    //std::cout << "New qsort with size = " << size << "\n";
    int l = 0;
    int r = size - 1;
    double mid = array[size / 2];
    do {
        switch (order) {
            case 0: {
                while ((array[l] - mid > 0.1) == 1) l++;
                while ((mid - array[r] > 0.1) == 1) r--;
                break;  //why not working without this string?
            }
            case 1: {
                while ((mid - array[l] > 0.1) == 1) {
                    l++;
                    //std::cout << l << "\n";
                }
                while ((array[r] - mid > 0.1) == 1) {
                    r--;
                    //std::cout << r << "\n";
                }
            }
        }

        if (l <= r) {
            double tmp = array[l];
            array[l] = array[r];
            array[r] = tmp;
            l++;
            r--;
        }
        /*for (int i = 0; i < size; i++) {
            if (i == size / 2) {
                SetConsoleTextAttribute(hConsole, 3);
                std::cout << array[i] << " ";
                SetConsoleTextAttribute(hConsole, 7);
            }
            else std::cout << array[i] << " ";
        }*/
        //std::cout << "l = " << l << ", r = " << r << ", mid = " << size / 2 << ", size = " << size <<"\n";
        //std::cout << "\n";

    } while (l <= r);

    //std::cout << "\n";

    if (r > 0) qsort_forDouble(array, r + 1, order);
    if (l < (size - 1)) qsort_forDouble(&array[l], size - l, order);
}

void qsortMY(void* array, int size, void (*function_forThisArray)(void*, int, double*, bool), bool order) {
    double array_forSort[1000] = { 0 };

    function_forThisArray(array, size, array_forSort, 0);
    qsort_forDouble(array_forSort, size, order);
    function_forThisArray(array, size, array_forSort, 1);
}

//Пример работы qsort для структуры:
struct Student {
    char name[40];
    int age;
};

void function_forStudent(void* group, int size, double* array_forSort, bool phase) { 
    if (phase == 0) {  //Заполняю численный массив для сортировки
        std::cout << "Array before sorting: \n";
        for (int i = 0; i < size; i++) {
            array_forSort[i] = ((Student*)group)[i].age;
            std::cout << ((Student*)group)[i].name << "-" << ((Student*)group)[i].age << " ";
        }
        std::cout << "\n";
    }
    else { //Восстанавливаю по отсортированному численному массиву порядок в массиве студентов
        std::cout << "Array after sorting: \n";

        Student* duplicate = new Student[size];
        for (int i = 0; i < size; i++) duplicate[i] = ((Student*)group)[i];

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (array_forSort[i] == duplicate[j].age) {
                    ((Student*)group)[i] = duplicate[j];
                    duplicate[j].age = 0;
                    break;
                }
            }
            std::cout << ((Student*)group)[i].name << "-" << ((Student*)group)[i].age << " ";
        }
        std::cout << "\n\n";
        delete[] duplicate;
    }
}

int main() {
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //для цветного вывода в консоль
    //srand(time(NULL));

    /*const unsigned int size = 10;
    double array[size] = { 0 };*/

    Student group[5] = { {"MoominTroll", 17}, {"Snorkmaiden", 16}, {"Snufkin", 18}, {"Too-Ticky", 17}, {"Toft", 16} };
    qsortMY(group, 5, function_forStudent, 0);

    /*std::cout << "Start posithion: ";
    for (int i = 0; i < size; i++) {
        array[i] = 1 + rand() % (20 - 1 + 1) + 0.1;
        std::cout << array[i] << " ";
    }
    std::cout << "\n\n";

    qsort_forDouble(array, size, 1);

    std::cout << "Result: ";
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }*/

    return 0;
}