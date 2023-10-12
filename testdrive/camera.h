#pragma once

#include <map>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "consts.h"
#include "camera.h"

class Camera {
  public:
    Camera(
      const std::string& name,
      const glm::vec3& position,
      const glm::vec3& direction,
      const glm::vec3& up,
      float fov,
      float viewRatio,
      float front,
      float back
    );

    static Camera* GetCamera(const std::string& name);

    void BuildView();
    glm::mat4 GetView() const { return _view; }

    glm::vec3 GetPosition() const { return _position; }
    glm::vec3 GetDirection() const { return _direction; }
    glm::vec3 GetRight() const { return _right; }

    void SetPosition(const glm::vec3& position) { _position = position; }
    void SetDirection(const glm::vec3& direction) { _direction = direction; }

    void SetXaxisRotation(float angle);
    void SetYaxisRotation(float angle);

    float GetLastX() const { return _lastX; }
    float GetLastY() const { return _lastY; }
    void SetLastX(float xpos) { _lastX = xpos; }
    void SetLastY(float ypos) { _lastY = ypos; }

    float GetFov() const { return _fov; }
    void SetFov(float fov) { _fov = fov; }

    void BuildProjection();
    glm::mat4 GetProjection() const { return _projection; }

  private:
    // camera features
    const std::string _name;
    static std::map<const std::string, Camera*> _camera_map;

    // view
    glm::vec3 _position, _direction, _up, _right;
    glm::mat4 _view;

    // projecton
    float _fov, _viewRatio, _front, _back;
    glm::mat4 _projection;

    // mouse position info(camera instance specific)
    float _lastX, _lastY;
};
