#include <stdio.h>
#include <conio.h>
#include <math.h>

#include "integral.h"
#include "menu.h"

const char* list_menu[SIZE_MENU] = {
  "Ввод границ интеграла",
  "Ввод шага интегрирования",
  "Расчёт интеграла",
  "Определить точность",
  "Вывод результата",
  "О программе",
  "Выход"
};

int Valid_Input(double* input, struct limit, char* text) {
  printf("%s", text);
  scanf("%lf", input);
  int next_char = getchar();

  if (next_char != '\n') {
    if (next_char != EOF) Clear_Input_Buffer();
    printf("\n%s\n", STR_INCORECT_INPUT);
    return CODE_ERROR_INPUT;
  }

  if (input < limit.min || input > limit.max) {
    printf("\n%s\n", STR_VALUE_BEYOND);
    return CODE_ERROR_INPUT;
  }

  return CODE_GOOD_INPUT;
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
  printf("Версия: 0.5\n");
  printf("Разработчик: студент гр. ИВТб - 1305, Мухатаев Артур\n");
  printf("%s\n", STR_LINE);
}
