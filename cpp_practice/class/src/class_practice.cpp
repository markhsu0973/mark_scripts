// example: one class, two objects
#include <iostream>
using namespace std;

class Print_value{
  public:
    void print_value(int);

};

void Print_value::print_value(int n) {
  cout << n <<"\n";
}

class Rectangle {
    int width, height;
    Print_value ouput_value;
  public:
    void set_values (int,int);
    int area () {return width*height;}
};

void Rectangle::set_values (int x, int y) {
  width = x;
  height = y;
  ouput_value.print_value(width*height);
}

int main () {
  Rectangle rect, rectb;

  
  rect.set_values (3,4);
  rectb.set_values (5,6);
  // cout << "rect area: " << rect.area() << endl;
  // cout << "rectb area: " << rectb.area() << endl;
  return 0;
}
