#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <windows.h>

#include "integral.h"
#include "menu.h"

const char* list_menu[SIZE_MENU] = {
  "Ввод границ интеграла",
  "Ввод шага интегрирования",
  "Расчёт интеграла",
  "Определить точность",
  "Вывод результата определения точности",
  "О программе",
  "Выход"
};

void Valid_Input(double* input, struct limit bounds, char* text) {
  int code_input;
  do {
    code_input = CODE_GOOD_INPUT;
    printf("%s", text);
    scanf("%lf", input);
    int next_char = getchar();

    Set_Color_Consol(COLOR_RED, COLOR_BLACK);
    if (next_char != '\n') {
      if (next_char != EOF) Clear_Input_Buffer();
      printf("%s\n", STR_INCORECT_INPUT);
      code_input = CODE_ERROR_INPUT;
    }
    else if (*input < bounds.min || *input > bounds.max) {
      printf("%s\n", STR_VALUE_BEYOND);
      code_input = CODE_ERROR_INPUT;
    }
    Reset_Color();
  } while (code_input != CODE_GOOD_INPUT);
}

void Clear_Input_Buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {}
}

void Print_Menu(const char **list_menu, int point) {
  printf("Для навигации по меню используйте стрелочки вверх(↑) и вниз(↓).\n");
  printf("Нажмите enter для выбора пункта меню.\n");
  printf("Меню:\n");
  printf("%s\n", STR_LINE);
  for (int i = 0; i < SIZE_MENU; i++) {
    if (point == i)
      printf("⟶  %d - %-38s", i + 1, list_menu[i]);
    else
      printf("    %d - %-38s", i + 1, list_menu[i]);
    printf("\n");
  }
    printf("%s\n", STR_LINE);
}

void Output_Status(struct dataIntegral data) {
  printf("Статус интеграла: \n");
  printf("%s\n", STR_LINE);

  printf("Границы интеграла: ");
  if (data.have_input_bounds == YES)
    printf("[ %lf, %lf ]\n", data.bounds.min, data.bounds.max);
  else
    printf("Не введены\n");

  printf("Шаг интегрирования: ");
  if (data.have_input_step == YES)
    printf("%lf\n", data.step);
  else
    printf("Не введён\n");

  printf("Результат интегрирования: ");
  if (data.have_calculation == YES)
    printf("%lf\n", data.value_Simpson);
  else
    printf("Не подсчитан\n");
  printf("\n");
}

void About_Program() {
  printf("Программа для вычисления интеграла методом Симпсона\n");
  printf("%s\n", STR_LINE);
  printf("Программа выполняет:\n");
  printf("1. Вычисляет площади фигуры, ограниченной кривой\n");
  printf("   2 * x ^ 3 + (-2) * x ^ 2 + (1) * x + (11)\n");
  printf("   и осью OX методом Симпсона\n");
  printf("2. Вычисляет точность метода симпсона посредством\n");
  printf("   сравнения с формулой Ньютона-Лейбница\n");
  printf("Версия: 1.0\n");
  printf("Разработчик: студент гр. ИВТб - 1305, Мухатаев Артур\n");
  printf("%s\n", STR_LINE);
}

void Set_Color_Consol(int text_color, int bg_color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, (bg_color << 4) | text_color);
}

void Reset_Color() {
  Set_Color_Consol(COLOR_WHITE, COLOR_BLACK);
}

void Output_Colot_Text(int text_color, char* text) {
  Set_Color_Consol(text_color, COLOR_BLACK);
  printf("%s", text);
  Reset_Color();
}

void Input_Bounds(struct dataIntegral *data, struct limit limit_bounds) {
  printf("Ввод границ интеграла(от %lf до %lf)\n", limit_bounds.min, limit_bounds.max);
  printf("%s\n", STR_LINE);

  Valid_Input(&data->bounds.min, limit_bounds, "Введите нижнею границу: ");

  if (data->bounds.min > 0 && data->bounds.min < 0.0000001) {
    Output_Colot_Text(COLOR_YELLOW, "Значение слишком маленькое. Автоматически округлено до 0\n");
    data->bounds.min = 0;
  }

  Valid_Input(&data->bounds.max, limit_bounds, "Введите вверхнею границу: ");

  if (data->bounds.max > 0 && data->bounds.max < 0.0000001) {
    Output_Colot_Text(COLOR_YELLOW, "Значение слишком маленькое. Автоматически округлено до 0\n");
    data->bounds.max = 0;
  }

  if (data->bounds.max < data->bounds.min) {
    Output_Colot_Text(COLOR_YELLOW, "Вверхняя границы не может быть меньше нижней границы. Значения автоматически были перестановлены местами.\n");
    int buff = data->bounds.max;
    data->bounds.max = data->bounds.min;
    data->bounds.min = buff;
  }

  if (data->bounds.max == data->bounds.min) {
    Output_Colot_Text(COLOR_YELLOW, "Границы интервала не могут совпадать.\nВерхняя границы автоматически была увелина на 1\n");
    data->bounds.max++;
  }

  Output_Colot_Text(COLOR_GREEN, "Границы интеграла успешно введены.\n");
  data->have_input_bounds = YES;
  data->have_calculation = NO;
  data->have_accuracy = NO;
}
