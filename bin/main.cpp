#include <lib/Array3d.h>
#include <iostream>

int main() {
  Array3d array(2, 2, 2);
  Array3d array2(2, 2, 2);
  uint32_t k = 34, m = 12;

  //Array3d array3 = array2 * 2;
  // k = array3[0][0][0];
  // m = array3[0][1][2];
  //std::cin >> array3[0][1][2];
  std::cout  << '\n' << array2;
  return 0;
}
