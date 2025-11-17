#ifndef INTEGRAL_H
#define INTEGRAL_H

#define CODE_ERROR_INPUT 400
#define CODE_GOOD_INPUT 1

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
    bool have_input_bounds;
    bool have_input_step;
    bool have_calculation;
};

// Объявления функций
int Valid_Input();
void Clear_Input_Buffer();
double Calcul_Integral();
double fun();
double Determine_accuracy();
double Calcul_Accuracy();
double F();

#endif // INTEGRAL_H
