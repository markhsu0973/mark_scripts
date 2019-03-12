#include <iostream>
 
using namespace std;

class Box {
   public:
      // Constructor definition
      Box(double l , double b , double h ) {
         cout <<"Constructor called." << endl;
         length = l;
         breadth = b;
         height = h;
      }
      double Volume() {
         return length * breadth * height;
      }
      int compare(Box box) {
         return this->Volume() > box.Volume();
      }
      
   private:
      double length;     // Length of a box
      double breadth;    // Breadth of a box
      double height;     // Height of a box
};



int main(void) {
   Box Box1(1, 2, 3);    // Declare box1
   Box Box2(1, 3, 1);    // Declare box2
   
   cout<<"Box1 volume: "<<Box1.Volume()<<" Box2 volume: "<<Box2.Volume()<<endl;
   if(Box1.compare(Box2)) {
      cout << "Box2 is smaller than Box1" <<endl;
   } else {
      cout << "Box2 is equal to or larger than Box1" <<endl;
   }
   
   return 0;
}
