#ifndef MENU_H
#define MENU_H

#include "integral.h"

#define SIZE_MENU 7
#define CODE_ERROR_INPUT 400
#define CODE_GOOD_INPUT 1
#define STR_INCORECT_INPUT "Не коректный ввод. Пожалуйста повторите попитку."
#define STR_VALUE_BEYOND \
    "Введённые данные находятся за пределами допустимых значений. Пожалуйста введите значение согласно " \
    "инструкциям."
#define STR_LINE \
    "--------------------------------------------------------------------------------"

enum keys_menu { UP = 72, DOWN = 80, ENTER = 13, ESC = 27 };
enum color {
    COLOR_GRAY = 8,
    COLOR_WHITE = 15,
    COLOR_BLACK = 0,
    COLOR_RED = 12,
    COLOR_GREEN = 10,
    COLOR_YELLOW = 14
};

extern const char* list_menu[SIZE_MENU];

// Вывод меню
void Print_Menu(const char **list_menu, int point);
// О программе
void About_Program();
// Вывод статуса интеграла
void Output_Status(struct dataIntegral data);
// Валидный ввод
void Valid_Input(double *input, struct limit bounds, char *text);
// Очистка буффера ввода
void Clear_Input_Buffer();
// Устоновить цвет консоли
void Set_Color_Consol(int text_color, int bg_color);
// Сброс цвета до стандартного
void Reset_Color();
// Вывод теста определённого цвета
void Output_Colot_Text(int text_color, char *text);
// Ввод границ
void Input_Bounds(struct dataIntegral *data, struct limit limit_bounds);
#endif // MENU_H
