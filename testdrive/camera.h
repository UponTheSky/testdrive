#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
  public:
    Camera(
      const glm::mat4& viewTrans,
      float fov,
      float viewRatio,
      float front,
      float back
    ) : _viewTrans(viewTrans), _fov(fov), _viewRatio(viewRatio), _front(front), _back(back) {
      _SetProjection();
    }

    void SetViewTrans(const glm::mat4& viewTrans) {
      _viewTrans = viewTrans;
      _SetProjection();
    }

    void SetFov(float fov) {
      _fov = fov;
      _SetProjection();
    }

    void SetViewRatio(float viewRatio) {
      _viewRatio = viewRatio;
      _SetProjection();
    }

    void SetFront(float front) {
      _front = front;
      _SetProjection();
    }

    void SetBack(float back) {
      _back = back;
      _SetProjection();
    }

    glm::mat4 GetViewTrans() const {return _viewTrans; }
    glm::mat4 GetProjection() const { return _projection; }

  private:
    glm::mat4 _viewTrans, _projection;
    float _fov, _viewRatio, _front, _back;

    void _SetProjection() { _projection = glm::perspective(glm::radians(_fov), _viewRatio, _front, _back); }
};
