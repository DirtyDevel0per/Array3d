#include <gtest/gtest.h>
#include <lib/Array3d.h>

void Rand(Array3d& mas, int x, int y, int z) {
  for (int i = 0; i < x; ++i)
    for (int j = 0; j < y; ++j)
      for (int k = 0; k < z; ++k)
        mas[i][j][k] = rand() % 1000;
}
TEST(Array3dMemoryTests, MaxSizeTest) {
  Array3d mas(100, 800, 100);

  ASSERT_TRUE(sizeof(mas.GetSize()) < 17 * 1e6 + 8);
}

TEST(Array3dMemoryTests, DestructorTest) {
  bool flag = true;
  for (int i = 0; i < 50; ++i) {
    try {
      Array3d* tmp = new Array3d(1000, 1000, 1000);
      delete tmp;
    } catch (const std::bad_alloc& e) {
      flag = false;
      break;
    }
  }
  ASSERT_TRUE(flag);
}

TEST(Array3dIndexTests, IntAndArray) {
  Array3d mas(10, 10, 10);
  unsigned k = 10;
  unsigned m;
  mas[2][3][0] = k;
  m = mas[2][3][0];
  ASSERT_EQ(k, m);
}

TEST(Array3dIndexTests, ArrayAndArray) {
  Array3d mas(10, 10, 10);
  unsigned k = 10;
  Array3d mas2(3, 4, 5);
  mas[2][3][0] = k;
  mas2[1][1][4] = mas[2][3][0];
  ASSERT_EQ(mas2[1][1][4], mas[2][3][0]);
}

TEST(Array3dIndexTests, MultTest) {
  Array3d mas(10, 10, 10);
  Rand(mas, 10, 10, 10);
  unsigned int kk = 5;
  Array3d mas2 = mas * kk;
  for (int i = 0; i < 10; ++i)
    for (int j = 0; j < 10; ++j)
      for (int k = 0; k < 10; ++k)
        ASSERT_EQ(mas2[i][j][k], mas[i][j][k] * kk);
}

TEST(Array3dIndexTests, AddTest) {
  Array3d mas(10, 10, 10);
  Array3d mas2(10, 10, 10);
  Rand(mas, 10, 10, 10);
  Rand(mas2, 10, 10, 10);
  Array3d mas3 = mas + mas2;
  for (int i = 0; i < 10; ++i)
    for (int j = 0; j < 10; ++j)
      for (int k = 0; k < 10; ++k)
        ASSERT_EQ(mas3[i][j][k], mas[i][j][k] + mas2[i][j][k]);
}

TEST(Array3dIndexTests, SubstrTest) {
  Array3d mas(10, 10, 10);
  Array3d mas2(10, 10, 10);
  Rand(mas, 10, 10, 10);
  Rand(mas2, 10, 10, 10);
  for (int i = 0; i < 10; ++i)
    for (int j = 0; j < 10; ++j)
      for (int k = 0; k < 10; ++k) {
       if (mas2[i][j][k] > mas[i][j][k])
         mas2[i][j][k] = mas[i][j][k];
      }
  Array3d mas3 = mas - mas2;
  for (int i = 0; i < 10; ++i)
    for (int j = 0; j < 10; ++j)
      for (int k = 0; k < 10; ++k)
        ASSERT_EQ(mas3[i][j][k], mas[i][j][k] - mas2[i][j][k]);
}