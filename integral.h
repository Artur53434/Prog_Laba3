#ifndef INTEGRAL_H
#define INTEGRAL_H

// Булевый тип
enum bool { YES, NO };

// Структура для границ
struct limit
{
    double min;
    double max;
};

// Стуктура для данных интеграла
struct dataIntegral
{
    struct limit bounds;
    double step;
    double value_Simpson;
    double value_Newton;
    double accuracy;
    enum bool have_input_bounds;
    enum bool have_input_step;
    enum bool have_calculation;
    enum bool have_accuracy;
};

// Объявления функций
void Calculation_Simpson(struct dataIntegral *data);
double Fun(double x);
double Calculation_Newton(struct limit bounds);
double Determine_accuracy(double value_Simpson, double value_Newton);
double Primitive_Fun(double x);

#endif // INTEGRAL_H
