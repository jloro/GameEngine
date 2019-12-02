/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:50:38 by jloro             #+#    #+#             */
/*   Updated: 2019/10/15 14:07:51 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"
#include "Engine.hpp"
#include <gtc/matrix_transform.hpp>

Camera*						Camera::_instance = nullptr;

std::shared_ptr<Camera>		Camera::Instance() { return _instance->shared_from_this(); }

Camera::Camera(float width, float height, bool freeFlight) : _moveSpeed(MOVE_SPEED), _mouseSensitivity(MOUSE_SENSITIVITY), _pitch(0.0f), _yaw(-90.0f), _width(width), _height(height), _freeFlight(freeFlight)
{
	if (_instance == nullptr)
		_instance = this;
	_pos = glm::vec3(-2.0f, 60.0f, -55.0f);
	if (!freeFlight)
	{
		_dir = glm::vec3(0.0f, -0.5f, 1.0f);
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
	else
	{
		_dir = glm::vec3(0.0f, 0.0f, -1.0f);
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
	_CalcMatrix();
}

Camera::~Camera() {}

glm::mat4	Camera::GetMatView(void) const { return _view; }
glm::mat4	Camera::GetMatProj(void) const { return _projection; }
glm::vec3	Camera::GetPos(void) const { return _pos; }
glm::vec3	Camera::GetDir(void) const { return _dir; }
glm::vec3	Camera::GetUp(void) const { return _up; }
float		Camera::GetMoveSpeed(void) const { return _moveSpeed; }
float		Camera::GetXRotation(void) const { return _yaw; }
float		Camera::GetYRotation(void) const { return _pitch; }
bool		Camera::GetFreeFlight() const { return _freeFlight; }

void 	Camera::Update()
{
	if (_freeFlight)
	{
		if (Engine42::Engine::GetKeyState(SDL_SCANCODE_W) == eKeyState::KEY_DOWN)
			Move(eCameraDirection::Forward, Engine42::Time::GetDeltaTime());
		if (Engine42::Engine::GetKeyState(SDL_SCANCODE_S) == eKeyState::KEY_DOWN)
			Move(eCameraDirection::Backward, Engine42::Time::GetDeltaTime());
		if (Engine42::Engine::GetKeyState(SDL_SCANCODE_D) == eKeyState::KEY_DOWN)
			Move(eCameraDirection::Right, Engine42::Time::GetDeltaTime());
		if (Engine42::Engine::GetKeyState(SDL_SCANCODE_A) == eKeyState::KEY_DOWN)
			Move(eCameraDirection::Left, Engine42::Time::GetDeltaTime());
		if (Engine42::Engine::GetKeyState(SDL_SCANCODE_Q) == eKeyState::KEY_DOWN)
			Move(eCameraDirection::Down, Engine42::Time::GetDeltaTime());
		if (Engine42::Engine::GetKeyState(SDL_SCANCODE_E) == eKeyState::KEY_DOWN)
			Move(eCameraDirection::Up, Engine42::Time::GetDeltaTime());
		if (Engine42::Engine::GetKeyState(SDL_SCANCODE_LSHIFT) == eKeyState::KEY_DOWN)
			_sprint = true;
		else
			_sprint = false;
	}
}
void	Camera::FixedUpdate() {}

void	Camera::Move(eCameraDirection dir, float deltaTime)
{
	float moveSpeed = _sprint ? _moveSpeed * 20 : _moveSpeed;
	if (dir == eCameraDirection::Forward)
		_pos += moveSpeed * deltaTime * _dir;
	else if (dir == eCameraDirection::Backward)
		_pos -= moveSpeed * deltaTime * _dir;
	else if (dir == eCameraDirection::Right)
		_pos += moveSpeed * deltaTime * _right;
	else if (dir == eCameraDirection::Left)
		_pos -= moveSpeed * deltaTime * _right;
	else if (dir == eCameraDirection::Up)
		_pos += moveSpeed * deltaTime * _up;
	else if (dir == eCameraDirection::Down)
		_pos -= moveSpeed * deltaTime * _up;

	_CalcMatrix();
}

void	Camera::_CalcMatrix()
{
	_right = glm::normalize(glm::cross(_dir, glm::vec3(0.0f, 1.0f, 0.0f)));
	_up = glm::normalize(glm::cross(_right, _dir));
	_view = glm::lookAt(_pos, _pos + _dir, _up);
	_projection = glm::perspective(glm::radians(FOV), _width / _height, 0.1f, 10000.0f);
}

void	Camera::LookAround(float xoffset, float yoffset)
{

	xoffset *= _mouseSensitivity;
	yoffset *= _mouseSensitivity;

	_yaw   += xoffset;
	_pitch = glm::clamp(_pitch + yoffset, -89.0f, 89.0f);

	_dir.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_dir.y = sin(glm::radians(_pitch));
	_dir.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_dir = glm::normalize(_dir);
	_CalcMatrix();
}

glm::mat4	Camera::GetViewMatrix(void) const
{
	return _view;
}
