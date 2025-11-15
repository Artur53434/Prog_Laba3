#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>

#define SIZE_MENU 7
#define CODE_ERROR_INPUT 400
#define CODE_GOOD_INPUT 1

int Valid_Input(double* input);
void Clear_Input_Buffer();

void Print_Menu(const char** list_menu, int point);
void About_Program();
void Input_Boundar_Integral(double* lower_limit, double* upper_limit);
void Input_Step_Integral(double* step_integral);
double Calcul_Integral(double lower_limit, double upper_limit, double step_integral);
double fun(double x);
void Output_Result(double lower_limit, double upper_limit, double step_integral, double calcul, double accuracy, double absolute_calcul);
double Determine_accuracy(double calcul, double absolute_calcul);
double Calcul_Accuracy(double a, double b);
double F(double a);

int main() {
  short is_exit = 0;
  double lower_limit = 0, upper_limit = 0;
  double step_integral = 0;
  double calcul = 0;
  double accuracy = 0;
  double absolute_calcul = 0;

  short have_input_limit = 0;
  short have_input_step = 0;
  short have_calcul = 0;

  // Подключение русского языка
  SetConsoleOutputCP(65001);
  SetConsoleCP(65001);

  const char** list_menu = malloc(SIZE_MENU * sizeof(char*));
  list_menu[0] = "Ввод границ интеграла";
  list_menu[1] = "Ввод шага интегрирования";
  list_menu[2] = "Расчёт интеграла";
  list_menu[3] = "Определить точность";
  list_menu[4] = "Вывод результата";
  list_menu[5] = "О программе";
  list_menu[6] = "Выход";
  int point = 0;

  while (is_exit == 0) {
    system("cls");
    Print_Menu(list_menu, point);

    int key = _getch();
    switch(key) {
      case 72:    // стрелка вверх
        if (point == 0) point = SIZE_MENU;
        if (point > 0) point--;
        break;
      case 80:    // стрелка вниз
        if (point >= SIZE_MENU - 1) point = 0;
        else if (point < SIZE_MENU) point++;
        break;
      case 13:    // Enter - выбор пункта
        system("cls");
        switch(point) {
        case 0:
          Input_Boundar_Integral(&lower_limit, &upper_limit);
          have_input_limit = 1;
          break;
        case 1:
          Input_Step_Integral(&step_integral);
          have_input_step = 1;
          break;
        case 2:
          if (have_input_limit != 0 && have_input_step != 0) {
            calcul = Calcul_Integral(lower_limit, upper_limit, step_integral);
            have_calcul = 1;
          }
          else {
            printf("\nВведены не все данные.\n");
          }
          break;
        case 3:
          absolute_calcul = Calcul_Accuracy(lower_limit, upper_limit);
          accuracy = Determine_accuracy(calcul, absolute_calcul);
          printf("Результат вычисления точности погрешности\n");
          printf("-------------------------------------------------------------\n");
          printf("Абсолютное значение: %lf\n", absolute_calcul);
          printf("Погрешность: %10lf\n", accuracy);
          printf("-------------------------------------------------------------\n");
          break;
        case 4:
          Output_Result(lower_limit, upper_limit, step_integral, calcul, accuracy, absolute_calcul);
          break;
        case 5:
          About_Program();
          break;
        case 6:
          is_exit = 1;
          break;
        }
        if (point != 6) {
          printf("\nНажмите любую клавишу для возврата в меню...");
          _getch();
        }
        break;
      case 27:    // Escape - выход
        is_exit = 1;
        break;
    }
  }
  free(list_menu);
  return 0;
}

void Print_Menu(const char** list_menu, int point) {
  printf("Для навигации по меню используйте стрелочки вверх(↑) и вниз(↓).\n");
  printf("Нажмите enter для выбора пункта меню.\n");
  printf("Меню:\n");
  printf("----------------------------------------------------\n");
  for (int i = 0; i < SIZE_MENU; i++) {
    if (point == i) {
        printf("⟶  %d - %-38s", i + 1, list_menu[i]);
    } else {
        printf("    %d - %-38s", i + 1, list_menu[i]);
    }
    printf("\n");
  }
  printf("----------------------------------------------------\n");
}

void About_Program() {
  printf("Программа для вычисления интеграла методом Симпсона\n");
  printf("-------------------------------------------------------------\n");
  printf("Программа выполняет:\n");
  printf("1. Вычисляет площади фигуры, ограниченной кривой\n    2 * x ^ 3 + (-2) * x ^ 2 + (1) * x + (11)\n    и осью OX методом Симпсона\n");
  printf("2. Вычисляет точность метода симпсона посредством\n    сравнения с формулой Ньютона-Лейбница\n");
  printf("Версия: 0.5\n");
  printf("Разработчик: студент гр. ИВТб - 1305, Мухатаев Артур\n");
  printf("-------------------------------------------------------------\n");
}

void Input_Boundar_Integral(double* lower_limit, double* upper_limit) {
  printf("Введите границы интеграла:\n");
  printf("----------------------------------------------------\n");
  printf("Ввод нижней границы a: ");
  int code_input = Valid_Input(lower_limit);
  if (code_input != CODE_GOOD_INPUT) return;

  printf("Ввод вверхней границы b: ");
  code_input = Valid_Input(upper_limit);
  if (code_input != CODE_GOOD_INPUT) return;

  if (*lower_limit >= *upper_limit) {
    printf("\nВверхняя граница должна быть больше нижней\n");
    return;
  }
  printf("Результат ввода: %lf %lf \n", *lower_limit, *upper_limit);
  printf("----------------------------------------------------\n");
}

void Clear_Input_Buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int Valid_Input(double* input) {
  if (scanf("%lf", input) != 1) {
    Clear_Input_Buffer();
    printf("\nОшибка ввода. Пожалуйста повторите попытку.\n");
    return CODE_ERROR_INPUT;
  }

  int next_char = getchar();
  if (next_char != '\n') {
    if (next_char != EOF) Clear_Input_Buffer();
    printf("\nВы ввели непотребство. Пожалуйста повторите попитку.\n");
    return CODE_ERROR_INPUT;
  }

  return CODE_GOOD_INPUT;
}

void Input_Step_Integral(double* step_integral) {
  printf("Введите шаг интегрирования:\n");
  printf("----------------------------------------------------\n");

  printf("Ввод шага интегрирования step: ");
  int code_input = Valid_Input(step_integral);
  if (code_input != CODE_GOOD_INPUT) return;

  if ((*step_integral > (0.00000000001)) && (step_integral <= 1)) {
    printf("Не правильный шаг интегрирования.\n");
    printf("Он должен быть в интервеле [%ld; %ld].\n", 0.00000000001, 1);
    return;
  }

  printf("Результат ввода: %lf \n", *step_integral);
  printf("----------------------------------------------------\n");
}

double fun(double x) {
  double y = 2 * pow(x, 3) - 2 * pow(x, 2) + x + 11;
  if (y >= 0) return y;
  else return 0;
}

double Calcul_Integral(double lower_limit, double upper_limit, double step_integral) {
  double res;

  printf("Вычисление интеграла методом Симпсона...\n");
  printf("-------------------------------------------------------------\n");
  printf("Границы: [%.3lf, %.3lf]\n", lower_limit, upper_limit);
  printf("Шаг: %.6lf\n\n", step_integral);

  int n = (int)((upper_limit - lower_limit) / step_integral);  // количество отрезков

  // Метод Симпсона требует четное количество отрезков
  if (n % 2 != 0) n++;  // делаем четным

  double h = (upper_limit - lower_limit) / n;  // пересчитываем шаг
  double sum = fun(lower_limit) + fun(upper_limit);

  // Сумма нечетных точек (умножается на 4)
  for (int i = 1; i < n; i += 2) {
    sum += 4 * fun(lower_limit + i * h);
  }

  // Сумма четных точек (умножается на 2)
  for (int i = 2; i < n; i += 2) {
    sum += 2 * fun(lower_limit + i * h);
  }

  res = (h / 3) * (sum);

  printf("Результат вычисления: %lf\n", res);
  printf("-------------------------------------------------------------\n");
  return res;
}

void Output_Result(double lower_limit, double upper_limit, double step_integral, double calcul, double accuracy, double absolute_calcul) {
  printf("Результат выполнения программы:\n");
  printf("----------------------------------------------------\n");
  printf("Границы интеграла: с %lf по %lf\n", lower_limit, upper_limit);
  printf("Шаг интегрирования: %lf\n", step_integral);
  printf("Результат расчёта методом Симпсона: %lf\n", calcul);
  printf("Результат расчёта методом Ньютона-Лейбница: %lf\n", absolute_calcul);
  printf("Отностетельная погрешность: %lf\n", accuracy);
  printf("----------------------------------------------------\n");
}

double F(double a) {
  return 0.5 * pow(a, 4) - (2.0f / 3.0f) * pow(a, 3) + 0.5 * pow(a, 2) + 11 * a;
}

double Calcul_Accuracy(double a, double b) {
  double t1 = pow((-302.0 / 27.0 + sqrt(1126)), 1.0 / 3.0);
  double zero_fun = t1 / pow(2, 2.0 / 3.0) - 1.0 / (pow(2, 1.0 / 3.0) * 9 * t1) + 1.0 / 3.0;
  if (a <= zero_fun && b >= zero_fun) return F(b) - F(zero_fun);
  else if (a <= zero_fun && b <= zero_fun) return 0;
  else if (a >= zero_fun && b >= zero_fun) return F(b) - F(a);
  return 0;
}

double Determine_accuracy(double calcul, double absolute_calcul) {
  double res = fabs((absolute_calcul - calcul) / calcul * 100);
  return res;
}
