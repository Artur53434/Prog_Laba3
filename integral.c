#include "integral.h"
#include "menu.h"

void Calculation_Simpson(struct dataIntegral *data) {
  double res;

  printf("Вычисление интеграла методом Симпсона...\n");
  printf("%s\n", STR_LINE);

  int n = (int)((data->bounds.max - data->bounds.min) / data->step);
  if (n % 2 != 0) n++;

  double h = (data->bounds.max - data->bounds.min) / n;
  double sum = Fun(data->bounds.min) + Fun(data->bounds.max);

  for (int i = 1; i < n; i += 2) {
    sum += 4 * Fun(data->bounds.min + i * h);
  }

  for (int i = 2; i < n; i += 2) {
    sum += 2 * Fun(data->bounds.min + i * h);
  }

  res = (h / 3) * (sum);

  printf("Результат вычисления: %lf\n", res);
  printf("%s\n", STR_LINE);

  data->value_Simpson = res;
}

double Fun(double x) {
  double y = 2 * pow(x, 3) - 2 * pow(x, 2) + x + 11;
  if (y >= 0) return y;
  else return 0;
}

double Calculation_Newton(struct limit bounds) {
  double zero_fun = 2.076618787392332;
  double a = bounds.min;
  double b = bounds.max;

  if (a <= zero_fun) a = zero_fun;
  if (b <= zero_fun) b = zero_fun;

  return Primitive_Fun(b) - Primitive_Fun(a);
}

double Primitive_Fun(double x) {
  return 0.5 * pow(x, 4) - (2.0f / 3.0f) * pow(x, 3) + 0.5 * pow(x, 2) + 11 * x;
}

double Determine_accuracy(double value_Simpson, double value_Newton) {
  double res = fabs((value_Newton - value_Simpson) / value_Simpson * 100);
  return res;
}
