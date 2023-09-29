#include "vector.h"

/* BaseVec */
BaseVec::BaseVec(size_t capacity) : _capacity(capacity) {
  assert(capacity > 0);
  _array = new float[capacity];
}

BaseVec::~BaseVec() {
  delete[] _array;
}

BaseVec::BaseVec(const BaseVec& other) : _capacity(other._capacity) {
  std::copy(other._array, other._array + other._capacity, _array);
}

BaseVec::BaseVec(BaseVec&& other) : _capacity(other._capacity), _array(other._array) {}

BaseVec& BaseVec::operator=(const BaseVec& other) {
  if (_capacity != other._capacity) {
    throw std::runtime_error("Two objects have different capacities");
  }

  std::copy(other._array, other._array + other._capacity, _array);
  return *this;
}

BaseVec& BaseVec::operator=(BaseVec&& other) {
  if (_capacity != other._capacity) {
    throw std::runtime_error("Two objects have different capacities");
  }

  _array = other._array;
  return *this;
}

const float& BaseVec::operator[](size_t index) const {
  if (!(0 <= index && index < _capacity)) {
    throw std::runtime_error("Index out of range");
  }

  return _array[index];
}

float& BaseVec::operator[](size_t index) {
  return const_cast<float&>(
    static_cast<const BaseVec&>(*this)[index]
  );
}

Vec2::Vec2(const float u, const float v) : BaseVec(2) {
  (*this)[0] = u;
  (*this)[1] = v;
}

Vec3::Vec3(const float x, const float y, const float z) : BaseVec(3) {
  (*this)[0] = x;
  (*this)[1] = y;
  (*this)[2] = z;
}

Vec4::Vec4(const float x, const float y, const float z, const float w) : BaseVec(4) {
  (*this)[0] = x;
  (*this)[1] = y;
  (*this)[2] = z;
  (*this)[3] = w;
}

Vec4::Vec4(const Vec3& vec3) : BaseVec(4) {
  (*this)[0] = vec3[0];
  (*this)[1] = vec3[1];
  (*this)[2] = vec3[2];
  (*this)[3] = 1;
}
