#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
  vector<int> numbers { 1, 2, 3, 4, 5, 10, 15, 20, 25, 35, 45, 50 };
  // 使用 lambda expression 替代原有的 condition 函數
  auto count = count_if(numbers.begin(), numbers.end(),
    [](int x) { return (x > 5); });
  cout << "Count: " << count << endl;
}