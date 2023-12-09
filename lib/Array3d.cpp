#include "Array3d.h"
#include <iostream>

std::istream& operator>>(std::istream& stream, Array3d rhs) {
  for (size_t i = 0; i < rhs.x_size_; ++i)
    for (size_t j = 0; j < rhs.y_size_; ++j)
      for (size_t k = 0; k < rhs.z_size_; ++k)
        std::cin >> rhs[i][j][k];
  return stream;
}

std::ostream& operator<<(std::ostream& stream, Array3d& rhs) {
  for (size_t i = 0; i < rhs.x_size_; ++i)
    for (size_t j = 0; j < rhs.y_size_; ++j)
      for (size_t k = 0; k < rhs.z_size_; ++k)
        stream << rhs[i][j][k] << " ";
  return stream;
}

std::istream& operator>>(std::istream& stream, uint17_t rhs) {
  uint32_t tmp;
  stream >> tmp;
  rhs = tmp;
  return stream;
}

uint17_t::uint17_t(uint8_t* array, const size_t index) : array_(array), index_(index) {}

uint17_t::operator unsigned() const {
  size_t byte_index = (index_ + 1) * 17 / 8;
  uint8_t offset = 7 - (index_ + 1) * 17 % 8;
  unsigned result = 0;
  for (int i = 0; i < 17; ++i) {
    result <<= 1;
    result |= array_[byte_index] >> offset & 1;
    offset == 0 ? (offset = 7, ++byte_index) : --offset;
  }

  return result;
}

uint17_t& uint17_t::operator=(const uint32_t& rhs) {
  size_t byte_index = (index_ + 1) * 17 / 8;
  uint8_t offset = 7 - (index_ + 1) * 17 % 8;
  for (int i = 0; i < 17; ++i) {
    array_[byte_index] &= ~(1 << offset);
    array_[byte_index] |= (rhs >> 16 - i & 1) << offset;
    offset == 0 ? (offset = 7, ++byte_index) : --offset;
  }

  return *this;
}

uint17_t& uint17_t::operator=(const uint17_t& rhs) {
  unsigned tmp = rhs;
  *this = tmp;

  return *this;
}

std::ostream& uint17_t::operator<<(std::ostream& stream) const {
  stream << *this;
  return stream;
}

Array::Array(uint8_t* array2d, const size_t offset) : array_(array2d), offset_(offset) {}

uint17_t Array::operator[](const uint32_t index) const {
  return {array_, offset_ + index};
}

Array2d::Array2d(uint8_t* array3d, const uint32_t x_offset, const uint32_t y)
: array2d_(array3d)
, offset_(x_offset)
, y_size_(y)
{}

Array Array2d::operator[](const uint32_t index) const {
  return {array2d_, index * y_size_ + offset_};
}

Array3d::Array3d() : array3d_(nullptr), x_size_(0), y_size_(0), z_size_(0), cnt_of_padding_bits_(0) {}

Array3d::Array3d(const uint32_t x, const uint32_t y, const uint32_t z) : x_size_(x), y_size_(y), z_size_(z) {
  array3d_ = new uint8_t[(x_size_ * y_size_ * z_size_ * 17 + 7) / 8]{};
  cnt_of_padding_bits_ = (x_size_ * y_size_ * z_size_ * 17 + 7) / 8 * 8 - x_size_ * y_size_ * z_size_ * 17;
}

Array3d::~Array3d() {
  delete[] array3d_;
}

Array3d& Array3d::operator+(const Array3d& rhs) const {
  if (rhs.x_size_ != x_size_ || rhs.y_size_ != y_size_ || rhs.z_size_ != z_size_)
    return *new Array3d();

  Array3d* result = new Array3d(x_size_, y_size_, z_size_);
  for (size_t i = 0; i < x_size_; ++i)
    for (size_t j = 0; j < y_size_; ++j)
      for (size_t k = 0; k < z_size_; ++k)
        (*result)[i][j][k] = (*this)[i][j][k] + rhs[i][j][k];

  return *result;
}

Array3d& Array3d::operator*(const uint32_t rhs) const {
  Array3d* result = new Array3d(x_size_, y_size_, z_size_);
  for (size_t i = 0; i < x_size_; ++i)
    for (size_t j = 0; j < y_size_; ++j)
      for (size_t k = 0; k < z_size_; ++k)
        (*result)[i][j][k] = (*this)[i][j][k] * rhs;
  return *result;
}

Array3d& Array3d::operator-(const Array3d& rhs) const {
  if (rhs.x_size_ != x_size_ || rhs.y_size_ != y_size_ || rhs.z_size_ != z_size_)
    return *new Array3d();

  Array3d* result = new Array3d(x_size_, y_size_, z_size_);

  for (size_t i = 0; i < x_size_; ++i)
    for (size_t j = 0; j < y_size_; ++j)
      for (size_t k = 0; k < z_size_; ++k)
        (*result)[i][j][k] = (*this)[i][j][k] - rhs[i][j][k];
  return *result;
}

Array2d Array3d::operator[](const uint32_t index) const {
  return {array3d_, index * x_size_ * y_size_, y_size_};
}

size_t Array3d::GetSize() {
  return sizeof(*array3d_) + sizeof(*this);
}

Array3d& Array3d::MakeArray(const uint32_t x, const uint32_t y, const uint32_t z) {
  return *new Array3d(x, y, z);
}





