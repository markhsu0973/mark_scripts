#include <iostream>
#include<math.h>

#define PI 3.14159265

int main ()
{
  double param, result;
  param = 1.0;
  result = atan (param) * 180 / PI;
  std::cout << "The arc tangent of" << param << " is " << result << " degrees" << std::endl;
  double x, y;
  x = -10.0;
  y = 10.0;
  result = atan2 (y,x) * 180 / PI;
  std::cout << "The arc tangent for (x=" << x << " , y= " << y << ") is " << result << " degrees" << std::endl;
  return 0;
}