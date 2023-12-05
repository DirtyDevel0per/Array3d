#pragma once
#include <cstdint>
#include <iostream>

class Array3d;
class Array2d;
class uint17_t;
std::istream& operator>>(std::istream& stream, uint17_t rhs);
std::istream& operator>>(std::istream& stream, Array3d rhs);
std::ostream& operator<<(std::ostream& stream, Array3d& rhs);

class uint17_t {
  public:

  uint17_t(uint8_t* array, size_t index);

  operator unsigned() const;

  uint17_t& operator=(const uint32_t& rhs);

  std::ostream& operator<<(std::ostream& stream) const;

  std::istream& operator>>(std::istream& stream);

  private:

  uint8_t* array_;
  size_t index_;
};

class Array {
  public:

  Array(uint8_t* array2d, size_t offset);

  uint17_t operator[](uint32_t index) const;

  private:
  uint8_t* array_;
  size_t offset_;
};

class Array2d {
  public:

  Array2d(uint8_t* array3d, uint32_t x_offset, uint32_t y);

  Array operator[](uint32_t index) const;

  private:

  uint8_t* array2d_;
  size_t offset_;
  uint32_t y_size_;
};

class Array3d {
  friend std::istream& operator>>(std::istream& stream, Array3d rhs);
  friend std::ostream& operator<<(std::ostream& stream, Array3d& rhs);
  public:

  Array3d();

  Array3d(uint32_t x, uint32_t y, uint32_t z);

  Array3d(const Array3d& object) = default;

  ~Array3d();

  Array3d& operator=(const Array3d& object) = default;

  Array3d& operator+(const Array3d& rhs) const;

  Array3d& operator*(uint32_t rhs) const;

  Array3d& operator-(const Array3d& rhs) const;

  Array2d operator[](uint32_t index) const;

  static Array3d& MakeArray(uint32_t x, uint32_t y, uint32_t z);

  private:

  uint8_t* array3d_;
  uint32_t x_size_;
  uint32_t y_size_;
  uint32_t z_size_;
  uint8_t cnt_of_padding_bits_;
};



