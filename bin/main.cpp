#include <lib/Array3d.h>
#include <iostream>

int main() {
  Array3d array(2, 2, 2);
  Array3d array2(2, 2, 2);
  uint32_t k = 34, m = 12;
  array[0][0][0] = k;
  array2[0][1][2] = m;
  array2[0][0][0] = k;
  k = 0;
  m = 0;
  Array3d array3 = array2 - array;
  k = array3[0][0][0];
  m = array3[0][1][2];
  //std::cin >> array3[0][1][2];
  std::cout << array3;
  return 0;
}
