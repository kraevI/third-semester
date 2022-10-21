#include <iostream>
#include <string>
using namespace std;

struct Point {
	const int x, y;

	Point(const int x, const int y) : x(x), y(y) {}

	Point maxXY(const Point& rha) const {
		return Point(rha.x > x ? rha.x : x, rha.y > y ? rha.y : y);
	}

	Point minXY(const Point& rha) const {
		return Point(rha.x < x ? rha.x : x, rha.y < y ? rha.y : y);
	}

	void print() const {
		std::cout << "(" << x << "," << y << ")\n";
	}
};

struct Rectangle {
	const Point p;

	Rectangle(const Point& rha) : p(rha) {}
	Rectangle(int a) : p(0, 0) {} //не работает с пустыми скобками

	Rectangle operator + (const Rectangle &a) const {
		return Rectangle(p.maxXY(a.p));
	}

	Rectangle operator * (const Rectangle& a) const {
		return Rectangle(p.minXY(a.p));
	}

	void print() const {
		p.print();
	}
};

class Expression {
public:
    string expression;
public:
    Expression(string expression) : expression(expression) {};

    Rectangle point_to_rect(string point) {
        //Подается строка вида "x,y" возвращается объект Rectangle(x, y)
        int n = point.find(",");
        int x = stoi(point.substr(0, n));
        int y = stoi(point.substr(n + 1));
        Point p(x, y);
        return Rectangle(p);
    }

    Rectangle first_left(int i) {
        // Возвращает первый слева прямоугольник от индекса номер i
        // в предположение, что i - номер символа с операцией
        // Найденная подстрока удаляется

        int left = i;
        while (expression[left] != '(')
            left--;
        int right = left;
        while (expression[right] != ')')
            right++;
        string point = expression.substr(left + 1, right - left);
        expression = expression.substr(0, max(left, 0)) + expression.substr(right + 1);
        return point_to_rect(point);
    }

    Rectangle first_right(int i) {
        // Возвращает первый справа прямоугольник от индекса номер i
        // в предположение, что i - номер символа с операцией
        // Найденная подстрока удаляется

        int left = i;
        while (expression[left] != '(')
            left++;
        int right = left;
        while (expression[right] != ')')
            right++;
        string point = expression.substr(left + 1, right - left);
        expression = expression.substr(0, max(left, 0)) + expression.substr(right + 1);
        return point_to_rect(point);
    }

    int first_operator() {
        //Возвращает номер символа, отвечающий за операцию первого приоритета

        for (int i = 0; i < expression.size(); i++) {
            if (expression[i] == '*')
                return i;
        }

        for (int i = 0; i < expression.size(); i++)
            if (expression[i] == '+')
                return i;

        return -1;
    }

    void operat() {
        //Совершение одной операции (упрощение выражения expression)
        int i = first_operator();
        string flag = "";
        if (expression[i] == '+')
            flag = "+";
        else
            flag = "*";


        expression = expression.replace(i, 1, " ");

        Expression expression_left(expression.substr(0, i));
        Expression expression_right(expression.substr(i));

        Rectangle rec_left = expression_left.first_left(i);
        Rectangle rec_right = expression_right.first_right(0);

        string s;
        if (flag == "+") {
            Rectangle rec = Rectangle(rec_left + rec_right);
            s = "(" + to_string(rec.p.x) + "," + to_string(rec.p.y) + ")";
        }
        else {
            Rectangle rec = Rectangle(rec_left * rec_right);
            s = "(" + to_string(rec.p.x) + "," + to_string(rec.p.y) + ")";
        }
        expression = expression_left.expression + s + expression_right.expression;
    }

    void print() {
        for (int i = 0; i < expression.size(); i++)
            cout << expression[i];
        cout << "\n";
    }
};

int main() {
    string input;
    getline(cin, input);
    Expression expression = Expression(input);

    while (expression.first_operator() != -1) {
        cout << expression.expression << endl;
        expression.operat();
        expression.print();
    }

    return 0;
}