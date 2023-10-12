#include "camera.h"

Camera* Camera::GetCamera(const std::string& name) { return _camera_map[name]; }

std::map<const std::string, Camera*> Camera::_camera_map;

Camera::Camera(
  const std::string& name,
  const glm::vec3& position,
  const glm::vec3& direction,
  const glm::vec3& up,
  float fov,
  float viewRatio,
  float front,
  float back
) : _name(name), _position(position), _direction(glm::normalize(direction)), _fov(fov), _viewRatio(viewRatio), _front(front), _back(back) {
  _right = glm::normalize(glm::cross(_direction, up));
  _up = glm::cross(_right, _direction);

  _lastX = window::INIT_WINDOW_WIDTH / 2;
  _lastY = window::INIT_WINDOW_HEIGHT / 2;

  _camera_map[name] = this;
}

void Camera::BuildView() {
  _view = glm::lookAt(_position, _position + _direction, _up);
}

void Camera::BuildProjection() {
  _projection = glm::perspective(glm::radians(_fov), _viewRatio, _front, _back);
}

void Camera::SetXaxisRotation(float angle) {
  float y = _direction[1];
  float z = _direction[2];

  _direction[1] = y * cos(angle) - z * sin(angle);
  _direction[2] = y * sin(angle) + z * cos(angle);
}

void Camera::SetYaxisRotation(float angle) {
  float z = _direction[2];
  float x = _direction[0];

  _direction[2] = z * cos(angle) - x * sin(angle);
  _direction[0] = z * sin(angle) + x * cos(angle);
}
