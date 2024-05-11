#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <iomanip>

#define a 0
#define b 0.5
#define eps 0.001

double f1(double x, double y) {
    return 1 + 2.2 * sin(x) + 1.5 * pow(y, 2);
}

double f2(double x, double y) {
    return cos(1.5 * x + y) + (x - y);
}

double euler_second_oeder(double y_initial, double x, double h) {
    double y_half = y_initial + 0.5 * h * f1(x, y_initial);
    double y_new = y_initial + h * f1(x + 0.5 * h, y_half);
    return y_new;
}

std::vector<std::tuple<double, double>> euler_method(double y_initial, double h) {
    std::vector<std::tuple<double, double>> points;
    double x = a;
    double y = y_initial;
    points.emplace_back(x, y);
    while (x < b - eps) {
        double y_prev = y;
        y = euler_second_oeder(y, x, h);
        x += h;
        points.emplace_back(x, y);
        if (abs(y - y_prev) < eps)
            break;
    }
    return points;
}

double runge_kutta(double y_initial, double x, double h) {
    double k1 = h * f1(x, y_initial);
    double k2 = h * f1(x + 0.5 * h, y_initial + 0.5 * k1);
    double k3 = h * f1(x + 0.5 * h, y_initial + 0.5 * k2);
    double k4 = h * f1(x + h, y_initial + k3);
    double y_new = y_initial + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    return y_new;
}

std::vector<std::tuple<double, double>> runge_kutta_method(double y_initial, double h) {
    std::vector<std::tuple<double, double>> points;
    double x = a;
    double y = y_initial;
    points.emplace_back(x, y);
    while (x < b - eps) {
        double y_prev = y;
        y = runge_kutta(y, x, h);
        x += h;
        points.emplace_back(x, y);
        if (abs(y - y_prev) < eps)
            break;
    }
    return points;
}

double adams_third_step(double y, double y_prev, double y_prev2, double h, double x) {
    return y + h * (23.0 / 12.0 * f2(x, y) - 4.0 / 3.0 * y_prev + 5.0 / 12.0 * y_prev2);
}

std::vector<std::tuple<double, double>> adams_third_order(double y_initial, double y_prime_initial, double h) {
    std::vector<std::tuple<double, double>> points;
    double x = a;
    double y = y_initial;
    double y_prev = y + h * y_prime_initial;
    points.emplace_back(x, y);
    while (x < b - eps) {
        double y_prev2 = y_prev;
        y_prev = y;
        y = adams_third_step(y, y_prev, y_prev2, h, x);
        x += h;
        points.emplace_back(x, y);
        if (abs(y - y_prev) < eps)
            break;
    }
    return points;
}

double adams_fourth_step(double y, double y_prev, double y_prev2, double y_prev3, double h, double x) {
    return y + h * (55.0 / 24.0 * f2(x, y) - 59.0 / 24.0 * f2(x - h, y_prev) +
        37.0 / 24.0 * f2(x - 2 * h, y_prev2) - 9.0 / 24.0 * f2(x - 3 * h, y_prev3));
}

std::vector<std::tuple<double, double>> adams_fourth_order(double y_initial, double y_prime_initial, double h) {
    std::vector<std::tuple<double, double>> points;
    double x = a;
    double y = y_initial;
    double y_prev = y + h * y_prime_initial;
    double y_prev2 = y_prev + h * f2(x,y);
    double y_prev3 = y_prev2 + h * f2(x+h,y_prev);
    points.emplace_back(x, y);
    while (x < b - eps) {
        y_prev3 = y_prev2;
        y_prev2 = y_prev;
        y_prev = y;
        y = adams_fourth_step(y, y_prev, y_prev2, y_prev3, h, x);
        x += h;
        points.emplace_back(x, y);
        if (abs(y - y_prev) < eps)
            break;
    }
    return points;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << std::setprecision(4);
    std::cout << std::fixed;

    double y_initial = 0;
    double h = 0.0375;
    double y_prime_initial = 1;
    //В данных векторах хранятся итоговые значения вычислений
    std::vector<std::tuple<double, double>> euler = 
        euler_method(y_initial, h);
    std::vector<std::tuple<double, double>> runge_kutta = 
        runge_kutta_method(y_initial, h);
    std::vector<std::tuple<double, double>> adams_third = 
        adams_third_order(y_initial, y_prime_initial, h);
    std::vector<std::tuple<double, double>> adams_fourth =
        adams_fourth_order(y_initial, y_prime_initial, h);

    std::cout << "Метод Эйлера" << std::endl;
    for (int i = 0; i < euler.size(); i++) 
        std::cout << "x" << i << " = " << std::get<0>(euler[i]) << " "
            << "y" << i << " = " << std::get<1>(euler[i]) << std::endl;

    std::cout << "Метод Рунге-Кутты" << std::endl;
    for (int i = 0; i < runge_kutta.size(); i++)
        std::cout << "x" << i << " = " << std::get<0>(runge_kutta[i]) << " "
            << "y" << i << " = " << std::get<1>(runge_kutta[i]) << std::endl;

    std::cout << "Метод Адамса 3-его порядка" << std::endl;
    for (int i = 0; i < adams_third.size(); i++)
        std::cout << "x" << i << " = " << std::get<0>(adams_third[i]) << " "
            << "y" << i << " = " << std::get<1>(adams_third[i]) << std::endl;

    std::cout << "Метод Адамса 4-ого порядка" << std::endl;
    for (int i = 0; i < adams_fourth.size(); i++) 
        std::cout << "x" << i << " = " << std::get<0>(adams_fourth[i]) << " "
            << "y" << i << " = " << std::get<1>(adams_fourth[i]) << std::endl;
}
