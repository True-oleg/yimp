#include <stdio.h>
#include <math.h>

float func_U(float x, float y) {


float min1X = pow(sin(x), 2) + exp(3);
float min2Y = log(fabs(x + pow(y, 3)));
float min;
if (min1X < min2Y) {
  min = min1X;
} else {
  min = min2Y;
}


if (min < 1) {
  return 2 * pow(y, x);
} else {
  float znam = 1 - tan(x - pow(y, 2)); 

  if (fabs(znam) < 1e-10) {
    printf("Знаменатель дроби не должен равняться нулю!\n");
    return 0;
  }
  float podkor = (x * pow(y, 2)) / znam;

  if (podkor < 1e-10) {
    return -pow(-podkor, 1.0/3.0);
  }
  return pow(podkor, 1.0/3.0);
}

} //конец функции



int main() {
  printf("Таблица значений U(x,y)\n");
  printf("x\\y\t");

float hx = 2.0;
float hy = 2.5;

float x_nach = 1.0;
float x_kon = 4.0;
float y_nach = 2.0;
float y_kon = 5.0;



   for (float y = y_nach; y <= y_kon + 1e-6; y += hy) {
     printf("%.2f\t", y);
     }
  printf("\n");

  for (float x = x_nach; x <= x_kon + 1e-6; x += hx) {
     printf("%.2f\t", x);

    for (float y = y_nach; y <= y_kon + 1e-6; y += hy) {
      float U = func_U(x, y);
      printf("%.2f\t", U);
      }

printf("\n");
}
return 0;

} //конец программы
