#include <iostream>

//Обобщённый вариант, без RAII
template <typename value_type, int N>
struct Grid final {

    value_type* data;
    unsigned int x;
    Grid<value_type, N - 1> grid; //subspace

    template<typename... Args>
    Grid(value_type const& t, int x, Args... subspace) : x(x), grid(subspace...) {
        data = new value_type[size()]{};
        std::fill(data, data + size(), t);
    }

    template<typename... Args>
    Grid(unsigned int x, Args... subspace) : x(x), grid(subspace...) {}

    unsigned int size() {
        return x * grid.size();
    }

    template<typename... Args>
    unsigned int idx(unsigned int x_idx, Args... subspace) {
        return (x_idx - 1) * grid.size() + grid.idx(subspace...);
    }

    template<typename... Args>
    value_type operator()(unsigned int x_idx, Args... subspace) {
        return data[idx(x_idx, subspace...)];
    }
};

template<typename value_type>
struct Grid<value_type, 2> final {

    value_type* data;
    unsigned int x_1, x_2;

    Grid(value_type const& t, unsigned int x_1, unsigned int x_2) : x_1(x_1), x_2(x_2) {
        data = new value_type[size()]{};
        std::fill(data, data + size(), t);
    }
    Grid(unsigned int x_2, unsigned int x_1) : x_1(x_1), x_2(x_2) {}

    unsigned int size() {
        return x_1 * x_2;
    }

    unsigned int idx(unsigned int x_1_idx, unsigned int x_2_idx) {
        return (x_1_idx - 1) * x_2 + (x_2_idx - 1);
    }

    value_type operator()(unsigned int x_1_idx, unsigned int x_2_idx) {
        return data[idx()];
    }
};

//Стандартная сетка со всеми методами
template <typename value_type>
class Grid_2D final {

public:
    value_type* data;
    unsigned int x_size, y_size;

    Grid_2D(value_type* data, unsigned int x_size, unsigned int y_size) : data(data), x_size(x_size), y_size(y_size) {}  
    Grid_2D(value_type const& t) : Grid_2D(t, 1, 1) {}
    Grid_2D(unsigned int x_size, unsigned int y_size) : x_size(x_size), y_size(y_size) {
        data = new value_type[x_size * y_size]{};
    }
    Grid_2D(value_type const& t, unsigned int x_size, unsigned int y_size) : x_size(x_size), y_size(y_size) {
        data = new value_type[x_size * y_size]{};
        std::fill(data, data + x_size * y_size, t);
    }

    //RAII
    ~Grid_2D() { delete[] data; }

    //конструктор копирования
    Grid_2D(Grid_2D<value_type> const& other) : x_size(other.x_size), y_size(other.y_size) {
        data = new value_type[x_size * y_size]{ 0 };
        for (unsigned int i = 0; i < x_size * y_size; i++)
            data[i] = other.data[i];

    }

    //конструктор перемещения
    Grid_2D(Grid_2D<value_type>&& other) : data(other.data), x_size(other.x_size), y_size(other.y_size) {       
        other.x_size = 0, other.y_size = 0;
        other.data = nullptr;
    }

    //оператор копирующего присваивания
    Grid_2D<value_type>& operator=(Grid_2D<value_type> const& other) {
        if (this == &other)
            return *this;

        value_type* tmp_data = new value_type[other.x_size * other.y_size];
        for (unsigned int i = 0; i < other.x_size * other.y_size; i++)
            tmp_data[i] = other.data[i];
        delete[] data;
        data = tmp_data;
        return *this;
    };

    //оператор присваивания перемещением
    Grid_2D<value_type>& operator=(Grid_2D<value_type>&& other) {
        if (this == &other)
            return *this;

        delete[] data;
        data = other.data;
        x_size = other.x_size, y_size = other.y_size;
        other.x_size = 0, other.y_size = 0;
        other.data = nullptr;
        return *this;
    }



    value_type operator()(unsigned int x_idx, unsigned int y_idx) {
        return data[(x_idx - 1) * y_size + (y_idx - 1)];
    }

    //заполнение значений data элементом t
    Grid_2D<value_type> operator=(value_type const& t) {
        std::fill(data, data + x_size * y_size, t);
        return *this;
    }
};

int main() {
    /*
    int* data = new int[25] { 0 };
    unsigned int const x = 5;
    unsigned int const y = 5;

    Grid_2D <int> int_grid1(data, y, x);
    std::cout << "Init. grid 5*5 with elements which equal 0.\nOutput x_size: " << int_grid1.x_size << std::endl;

    //конструктор копирования
    Grid_2D <int> int_grid2(int_grid1);
    std::cout << "Init. new grid by copy constructor.\nOutput x_size: " << int_grid2.x_size << std::endl;
    

    //конструктор перемещения
    Grid_2D <int> int_grid3(std::move(int_grid1));
    std::cout << "Init. new grid by move constructor.\nOutput x_size : " << int_grid3.x_size << std::endl;
    //std::cout << "grid1.x [0] " << int_grid1.x_size << std::endl;

    //оператор копирующего присваивания
    int_grid3 = 15;
    int_grid2 = int_grid3;
    std::cout << "Copy assignment's work.\nOutput data[5] : " << int_grid2.data[5] << std::endl;

    //оператор присваивания перемещением
    int_grid2 = 10;
    int_grid3 = std::move(int_grid2);
    std::cout << "Move assignment's work.\nOutput data[5] : " << int_grid3.data[5] << std::endl;
    std::cout << "Output adress of the data on the right side: " << int_grid2.data << std::endl;

    Grid_2D <int> T(4, 5, 9);
    std::cout << T(3, 4);*/

    Grid <float, 3> grid3(90.1f, 2, 2, 3);
    std::cout << grid3.data[9] << std::endl;
    grid3.data[9] = 5.9;
    std::cout << grid3(2, 2, 2);

    return 0;
}
