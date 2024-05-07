#include <iostream>
#include <vector>

#define h 0.0001

//Первое задание
double function(double x) {
    return sin(x);
}
double derivitive_6(double x) {
    return -sin(x);
}

//Второе задание
double function_2(double x) {
    return log(x/2);
}
double derivitive_2_1(double x) {
    return 1/x;
}
double derivitive_2_2(double x) {
    return -1 / pow(x,2);
}

double lagrange(std::vector<double> x_k, std::vector<double> y_k, double x) {
    double L = 0;
    for (int i = 0; i < x_k.size(); i++) {
        double s = 1;
        for (int j = 0; j < x_k.size(); j++) {
            if (i != j) {
                s *= (x - x_k[j]) / (x_k[i] - x_k[j]);
            }
        }
        s *= y_k[i];
        L += s;
    }
    return L;
}
double lagrange_2(std::vector<double> x_k, double x) {
    double L = 0;
    for (int i = 0; i < x_k.size(); i++) {
        double s = 1;
        for (int j = 0; j < x_k.size(); j++) {
            if (i != j) {
                s *= (x - x_k[j]) / (x_k[i] - x_k[j]);
            }
        }
        s *= function_2(x_k[i]);
        L += s;
    }
    return L;
}

double factorial(double x) {
    double result = 1;
    for (int i = 1; i < x; i++)
        result *= 1;
    return result;
}

double error_lagrange(std::vector<double> x_k, double x) {
    int n = 4; 
    double result = 1;
    for (int i = 0; i < n; i++) {
        result *= x - x_k[i];
        result *= derivitive_6(2.5) / factorial(n+1);
    }
    return abs(result);
}

double left_derivative(double x, double (*func)(double)) {
    return (func(x) - func(x - h)) / h;
}

double mid_derivative(double x, double (*func)(double)) {
    return (func(x + h) - func(x - h)) / (2 * h);
}
double right_derivative(double x, double (*func)(double)) {
    return (func(x + h) - func(x)) / h;
}

//Численная вторая производная
double second_derivative(double x, double (*func)(double)) {
    return (func(x - h) - 2 * func(x) + func(x + h)) / pow(h, 2);
}

double eitken(std::vector<double> x_k, double x, std::vector<double> L, int k1, int k2) {
    if (k2 - k1 != 1)
        return (eitken(x_k, x, L, k1, k2 - 1) * (x_k[k2] - x) - (eitken(x_k, x, L, k1 + 1, k2)
            * (x_k[k1] - x))) / (x_k[k2] - x_k[k1]);
    else
        return L[k1];
}

int main()
{
    setlocale(LC_ALL, "Russian");
    double x = 1.6;
    std::vector<double> x_k = { 1.5, 2.0, 2.5, 3.5 };
    std::vector<double> y_k = { 0.99745, 0.9093, 0.59847, 0.14112 };
    std::cout << "Значение в Х по Лагранжу " << lagrange(x_k, y_k, x) << std::endl;
    std::cout << "Аналитическое значение " << function(x) << std::endl;
    std::cout << "Ошибка метода Лагранжа " << error_lagrange(x_k, x) << std::endl;
    std::cout << "Левая производная " << left_derivative(x, function) << std::endl;
    std::cout << "Правая производная " << right_derivative(x, function) << std::endl;
    std::cout << "Средняя производная " << mid_derivative(x, function) << std::endl;

    x = 1.026;
    x_k = { 1.00, 1.08, 1.20, 1.27, 1.31, 1.38 };
    y_k = { 1.17520, 1.30254, 1.50946, 1.21730, 1.22361, 1.23470 };
    int n = 6;

    std::vector<double> L(n - 1);

    for (int i = 0; i < n - 1; i++)
        L[i] = (y_k[i] * (x_k[i + 1] - x) - (y_k[i + 1] * (x_k[i] - x))) / (x_k[i + 1] - x_k[i]);

    std::cout << "Значение в Х по Эйткену " << eitken(x_k, x, L, 0, n-1) << std::endl;

    double a = 4.5;
    double b = 10;
    double m = 5.03;
    x_k = { 4.5, 5.6, 6.7, 7.8, 8.9, 10 };

    for (double i : x_k) {
        std::cout << "\nx = " << i << std::endl;
        std::cout << "Левая производная " << left_derivative(i, function_2) << std::endl;
        std::cout << "Правая производная " << right_derivative(i, function_2) << std::endl;
        std::cout << "Средняя производная " << mid_derivative(i, function_2) << std::endl;
        std::cout << "Вторая производная (численно) " << second_derivative(i, function_2) << std::endl;
        std::cout << "Первая производная (аналитически) " << derivitive_2_1(i) << std::endl;
        std::cout << "Вторая производная (аналитически) " << derivitive_2_2(i) << std::endl;
    }

    std::cout << "\nm = " << m << std::endl;
    std::cout << "Левая производная " << left_derivative(m, function_2) << std::endl;
    std::cout << "Правая производная " << right_derivative(m, function_2) << std::endl;
    std::cout << "Средняя производная " << mid_derivative(m, function_2) << std::endl;
    std::cout << "Вторая производная (численно) " << second_derivative(m, function_2) << std::endl;
    std::cout << "Первая производная (аналитически) " << derivitive_2_1(m) << std::endl;
    std::cout << "Вторая производная (аналитически) " << derivitive_2_2(m) << std::endl;
    std::cout << "Интерполированное значение m " << lagrange_2(x_k, m) << std::endl;
    std::cout << "Аналитическое значение m " << function_2(m) << std::endl;


}
