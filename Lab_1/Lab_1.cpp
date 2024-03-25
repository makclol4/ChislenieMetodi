#include <iostream>
#include <functional>
#include <cmath>
#include <iomanip>
#define ACCURACY pow(10, -7)

double function(double x)
{
    return (2 * std::sin(3 * x) - 1.5 * x);
}

double derivative1(double x)
{
    return (6 * std::cos(3*x) - 1.5);
}

double derivative2(double x)
{
    return (-18 * std::sin(3 * x));
}

void createStartTable()
{
    double startX = 0.2;
    double endX = 1.0;
    double step = 0.08;

    for (double x = startX; x <= endX; x += step)
    {
        double result = function(x);
        std::cout << std::fixed << std::setprecision(2) << x << " ";
        std::cout << std::fixed << std::setprecision(7) << result << "\n";
    }
}

void metodKasateln()
{
    std::cout << "Metod Kasatelnih" << std::endl;
    double x0 = 0.8;
    for (int i = 0; true; i++)
    {
        double x1 = x0 - function(x0) / derivative1(x0);
        if (std::abs(x1 - x0) < ACCURACY)
        {
            std::cout << i << " " << std::fixed << std::setprecision(8) << x1 << "\n";
            break;
        }
        std::cout << i << " " << std::fixed << std::setprecision(8) << x1 << "\n";
        x0 = x1;
    }
}

void metodChord()
{
    std::cout << "Metod Chord" << std::endl;
    double a = 0.8;
    double b = 1;
    double x0 = a;
    for (int i = 0; true; i++)
    {
        double x1 = x0 - function(x0) * (b - x0) / (function(b) - function(x0));
        if (std::abs(x1 - x0) < ACCURACY)
        {
            std::cout << i << " " << std::fixed << std::setprecision(8) << x1 << "\n";
            break;
        }
        std::cout << i << " " << std::fixed << std::setprecision(8) << x1 << "\n";
        x0 = x1;
    }
}

void metodSecant()
{
    std::cout << "Metod Secant" << std::endl;
    double x0 = 0.8;
    double x1 = 1;
    for (int i = 0; true; i++)
    {
        double x2 = x1 - function(x1) * (x1 - x0) / (function(x1) - function(x0));
        if (std::abs(x2 - x1) < ACCURACY)
        {
            std::cout << i << " " << std::fixed << std::setprecision(8) << x2 << "\n";
            break;
        }
        std::cout << i << " " << std::fixed << std::setprecision(8) << x2 << "\n";
        x0 = x1;
        x1 = x2;
    }
}

void metodNewton()
{
    std::cout << "Metod Newtona Konechnoraznostni" << std::endl;
    double x0 = 0.8;
    double h = 0.05;
    for (int i = 0; true; i++)
    {
        double x1 = x0 - function(x0) * h / (function(x0 + h) - function(x0));
        if (std::abs(x1 - x0) < ACCURACY)
        {
            std::cout << i << " " << std::fixed << std::setprecision(8) << x1 << "\n";
            break;
        }
        std::cout << i << " " << std::fixed << std::setprecision(8) << x1 << "\n";
        x0 = x1;
    }
}

void metodSteffensena()
{
    std::cout << "Metod Steffensena" << std::endl;
    double x0 = 0.8;
    for (int i = 0; true; i++)
    {
        double x1 = x0 - std::pow(function(x0),2) / (function(x0+function(x0)) - function(x0));
        if (std::abs(x1 - x0) < ACCURACY)
        {
            std::cout << i << " " << std::fixed << std::setprecision(8) << x1 << "\n";
            break;
        }
        std::cout << i << " " << std::fixed << std::setprecision(8) << x1 << "\n";
        x0 = x1;
    }
}

void metodSimpleItteration()
{
    std::cout << "Metod SimpleItteration" << std::endl;
    double x0 = 0.8;
    double t = -0.2;
    for (int i = 0; true; i++)
    {
        double x1 = x0 - function(x0) * t;
        if (std::abs(x1 - x0) < ACCURACY)
        {
            std::cout << i << " " << std::fixed << std::setprecision(8) << x1 << "\n";
            break;
        }
        std::cout << i << " " << std::fixed << std::setprecision(8) << x1 << "\n";
        x0 = x1;
    }
}

int main()
{
    createStartTable();
    metodKasateln();
    metodChord();
    metodSecant();
    metodNewton();
    metodSteffensena();
    metodSimpleItteration();
}

