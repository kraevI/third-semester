#include <iostream>
#include <random>
#include <fstream>

const long long int half_size = pow(2, 31);
long long int zero_element = half_size;

class MultiState {

private:
    bool* states = new bool[half_size * 2 + 1] {false};
    

public:
    MultiState(int* array, const unsigned long long int size) {
        for (unsigned long long int i = 0; i < size; i++) {
            states[zero_element + array[i]] = true;
        }
    }

    MultiState(bool* array) : states(array) {}

    bool contains(long long int s) {
        if (states[zero_element + s] == true) return true;
        else return false;
    }

    void print() {
        for (long long int i = - half_size; i <= half_size; i++)
            if (states[zero_element + i] == true) std::cout << i << " ";
        std::cout << std::endl;
    }

    MultiState operator+ (MultiState &a) {
        bool* new_states = new bool[half_size * 2 + 1] {false};
        for (long long int i = -half_size; i <= half_size; i++)
            new_states[zero_element + i] = a.states[zero_element + i] + states[zero_element + i];
        MultiState ms(new_states);
        return ms;
    }
};

class ProbabilityTest {
private:
    int E_min, E_max;

public:
    ProbabilityTest(int E_min, int E_max) :
        E_min(E_min), E_max(E_max) {}

    float test(MultiState system, unsigned test_count, unsigned seed) { 
        std::default_random_engine reng(seed);
        std::uniform_int_distribution<int> dstr(E_min, E_max);

        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (system.contains(dstr(reng))) ++good;

        return static_cast<float>(good) / static_cast<float>(test_count);
    }
};


/*
class State {
public:
    virtual bool contains(int s) {
        return 0;
    }
};

class DiscreteState: public State {
private:
    int const s0;

public:
    DiscreteState(int s0) : s0(s0) {}
    bool contains(int s) override {
        return s = s0;
    }
};

class SegmentState: public State {
private:
    int const begin_s0, end_s0;

public:
    SegmentState(int begin_s0, int end_s0) :
        begin_s0(begin_s0), end_s0(end_s0) {}

    bool contains(int s) override {
        return begin_s0 <= s and end_s0 >= s;
    }
};

class ProbabilityTest {
private:
    int E_min, E_max;

public:
    ProbabilityTest(int E_min, int E_max) :
        E_min(E_min), E_max(E_max) {}

    float test(State &system, unsigned test_count, unsigned seed) { //почему не работает без ссылки?
        std::default_random_engine reng(seed);
        std::uniform_int_distribution<int> dstr(E_min, E_max);

        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (system.contains(dstr(reng))) ++good;

                return static_cast<float>(good) / static_cast<float>(test_count);
    }
};
*/


int main() {
    /*DiscreteState d(0);
    SegmentState s(0, 100);
    ProbabilityTest pt(-1000, 1000);
    std::cout << pt.test(d, 20000, 2) << std::endl;
    std::cout << pt.test(s, 20000, 2) << std::endl;*/

    //создание сложного случайного состояния с равномерным распределением элементралных
    std::random_device myRandomDevice;
    unsigned seed = myRandomDevice();
    std::default_random_engine myRandomEngine(seed);
    std::uniform_int_distribution<long long> dstr(-pow(2, 31), pow(2, 31));

    const unsigned long int size = 1000;
    int array[size] = { 0 };
 

    //эта часть кода позволяет проверить равномерность распределения случайных чисел
    std::ofstream out;
    out.open("lab3.txt");
    if (!out) {
        std::cout << "File was not open" << std::endl;
        return 1;
    }
    for (unsigned long int i = 0; i < size; i++) {
        array[i] = dstr(myRandomEngine);
        out << array[i] << std::endl;
    }
    out.close();

    MultiState ms1(array, size);

    //проведение тестов и вывод данных
    ProbabilityTest tester(-1000, 1000);  

    out.open("lab3_output.txt");
    if (!out) {
        std::cout << "File was not open" << std::endl;
        return 1;
    }
    
    for (unsigned long long int i = 1; i <= pow(2, 20); i = i * 2) {
        out << i << " " << tester.test(ms1, i, 5) << std::endl;
        std::cout << i << std::endl;
    }
    out.close();


    return 0;
}