#include <iostream>
#include <cmath>
#include <iomanip>
#include <ranges>
#define ACCURACY pow(10, -5)
#define Exact_Solution (primitive(1) - primitive(0))

double function(double x)
{
    return atan(x);
}

double primitive(double x)
{
    return x * atan(x) - (log(1 + x * x) / 2);
}

double relativeError(double answer)
{
    return abs(100 * (Exact_Solution - answer) / Exact_Solution);
}

double leftRectMethod(double a, double b)
{
    int n = 2;
    double answer = 0;
    while (true)
    {
        double h = (b - a) / n;
        double x = a;
        double prev = answer;
        answer = 0;
        for (int i = 0; i < n; i++)
        {
            answer += function(x) * h;
            x += h;
        }
        double calc_error = abs(answer - prev);
        if (calc_error < ACCURACY)
        {
            std::cout << "\nМетод левых прямоугольников:\nI: " <<
                std::fixed << std::setprecision(15) << answer
                << "\nh: " << h << "\nn: " << n <<
                "\nError " << relativeError(answer) << std::endl;
            return answer;
        }
        n *= 2;
    }
}

double rightRectMethod(double a, double b)
{
    int n = 2;
    double answer = 0;
    while (true)
    {
        double h = (b - a) / n;
        double x = a + h;
        double prev = answer;
        answer = 0;
        for (int i = 0; i < n; i++)
        {
            answer += function(x) * h;
            x += h;
        }
        double calc_error = abs(answer - prev);
        if (calc_error < ACCURACY)
        {
            std::cout << "\nМетод правых прямоугольников:\nI: " <<
                std::fixed << std::setprecision(15) << answer 
                << "\nh: "  << h << "\nn: " << n <<
                "\nError " << relativeError(answer) << std::endl;
            return answer;
        }
        n *= 2;
    }
}

double midRectMethod(double a, double b)
{
    int n = 2;
    double answer = 0;
    while (true)
    {
        double h = (b - a) / n;
        double x = a + h / 2;
        double prev = answer;
        answer = 0;
        for (int i = 0; i < n; i++)
        {
            answer += function(x) * h;
            x += h;
        }
        double calc_error = abs(answer - prev);
        if (calc_error < ACCURACY)
        {
            std::cout << "\nМетод средних прямоугольников:\nI: " <<
                std::fixed << std::setprecision(15) << answer
                << "\nh: " << h << "\nn: " << n <<
                "\nError " << relativeError(answer) << std::endl;
            return answer;
        }
        n *= 2;
    }
}

double trapezoidalMethod(double a, double b)
{
    int n = 2;
    double answer = 0;
    while (true)
    {
        double h = (b - a) / n;
        double x = a;
        double prev = answer;
        answer = (function(a)+function(b)) / 2;
        for (int i = 0; i < n; i++)
        {
            x += h;
            answer += function(x);
        }
        answer *= h;
        double calc_error = abs(answer - prev);
        if (calc_error < ACCURACY)
        {
            std::cout << "\nМетод трапеций:\nI: " <<
                std::fixed << std::setprecision(15) << answer
                << "\nh: " << h << "\nn: " << n <<
                "\nError " << relativeError(answer) << std::endl;
            return answer;
        }
        n *= 2;
    }
}

double simpsonMethod(double a, double b)
{
    int n = 2;
    double answer = 0;
    while (true)
    {
        double h = (b - a) / n;
        double x = a;
        double prev = answer;
        answer = function(a) + function(b);
        for (int i = 1; i <= n; i++)
        {
            x += h;
            if (i % 2 ==0)
                answer += 2 * function(x);
            else 
                answer += 4 * function(x);
        }
        answer *= h/3;
        double calc_error = abs(answer - prev);
        if (calc_error < ACCURACY)
        {
            std::cout << "\nМетод Симсона:\nI: " <<
                std::fixed << std::setprecision(15) << answer
                << "\nh: " << h << "\nn: " << n <<
                "\nError " << relativeError(answer) << std::endl;
            return answer;
        }
        n *= 2;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    double a = 0, b = 1;
    leftRectMethod(a, b);
    rightRectMethod(a, b);
    midRectMethod(a, b);
    trapezoidalMethod(a, b);
    simpsonMethod(a, b);
}