#pragma once

#include <cstddef>
#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <vector>

class BaseVec {
  public:
    virtual ~BaseVec() = default;

    // member function
    const float& operator[](size_t index) const;
    float& operator[](size_t index);

  protected:
    // constructor
    explicit BaseVec(size_t capacity);

    // copy constructor
    BaseVec(const BaseVec& other);

    // move constructor
    BaseVec(BaseVec&& other);

    // copy assignment
    BaseVec& operator=(const BaseVec& other);

    // move assignment
    BaseVec& operator=(BaseVec&& other);

  private:
    std::vector<float> _array;
};

class Vec2 : public BaseVec {
  public:
    Vec2(const float u = 0, const float v = 0);
};

class Vec3 : public BaseVec {
  public:
    Vec3(const float x = 0, const float y = 0, const float z = 0);
};

class Vec4 : public BaseVec {
  public:
    Vec4(
      const float x = 0,
      const float y = 0,
      const float z = 0,
      const float w = 0
    );

    Vec4(const Vec3& vec3);
};
