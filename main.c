#include <conio.h>
#include <stdio.h>
#include <Windows.h>

#include "integral.h"
#include "menu.h"

int main() {
  enum bool is_exit = NO;
  int point = 0;
  struct dataIntegral data;
  data.have_input_bounds = NO;
  data.have_input_step = NO;
  data.have_calculation = NO;
  data.have_accuracy = NO;

  struct limit limit_bounds;
  limit_bounds.min = -10e3;
  limit_bounds.max = 10e3;

  struct limit limit_step;
  limit_step.min = 10e-6;
  limit_step.max = 1;

  int code_input;

  // Подключение русского языка
  SetConsoleOutputCP(65001);
  SetConsoleCP(65001);

  while (is_exit == NO) {
    system("cls");
    Print_Menu(list_menu, point);

    Set_Color_Consol(COLOR_GRAY, COLOR_BLACK);
    Output_Status(data);
    Reset_Color();

    enum keys_menu key = _getch();
    switch (key) {
      case UP: // Нажатие стрелки вверх
        point = (point - 1 + SIZE_MENU) % SIZE_MENU;
        break;
      case DOWN: // Нажатие стрелки вниз
        point = (point + 1) % SIZE_MENU;
        break;
      case ENTER: // Выбор меню
        switch (point) {
          case 0:
            Input_Bounds(&data, limit_bounds);
            break;
          case 1:
            printf("Ввод шага интегрирования( от %lf до %lf)\n", limit_step.min, limit_step.max);
            printf("%s\n", STR_LINE);
            Valid_Input(&data.step, limit_step, "Введите шаг интегрирования: ");
            Output_Colot_Text(COLOR_GREEN, "Шаг интегрирования успешно введён.\n");
            data.have_input_step = YES;
            data.have_calculation = NO;
            data.have_accuracy = NO;
            break;
          case 2:
            if (data.have_input_bounds == YES && data.have_input_step == YES) {
              Calculation_Simpson(&data);
              Output_Colot_Text(COLOR_GREEN, "Интеграл упешно вычислен.\n");
              data.have_calculation = YES;
              data.have_accuracy = NO;
            }
            else Output_Colot_Text(COLOR_RED, "Не введены все данные для расчёта интеграла.\n");
            break;
          case 3:
            if (data.have_calculation == YES) {
              data.value_Newton = Calculation_Newton(data.bounds);
              data.accuracy = Determine_accuracy(data.value_Simpson, data.value_Newton);
              Output_Colot_Text(COLOR_GREEN, "Точность интеграла успешно вычислена.\n");
              data.have_accuracy = YES;
            }
            else Output_Colot_Text(COLOR_RED, "Для расчёта точности вычисленый. Необходимо сначала подчитать интеграл.\n");
            break;
          case 4:
            //Output_Status(data);
            if (data.have_accuracy == YES) {
              printf("Абстолютное значение интеграла: %lf\n", data.value_Newton);
              printf("Точность вычисления интеграла: %lf %\n", data.accuracy);
            }
            else Output_Colot_Text(COLOR_RED, "Для начала необходимо подчитать значение точности.\n");
            break;
          case 5:
            About_Program();
            break;
          case 6:
            is_exit = YES;
            break;
        }
        if (point != 6) {
          Output_Colot_Text(COLOR_GRAY, "Для продолжения нажмите любую кнопку...\n");
          _getch();
        }
        break;
      case ESC:
        is_exit = YES;
        break;
    default:
      system("cls");
      break;
    _getch();
    }
  }
  return 0;
}
