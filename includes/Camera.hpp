/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:47:43 by jloro             #+#    #+#             */
/*   Updated: 2019/09/26 14:21:30 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP

# include <glm.hpp>
# include "GameObject.hpp"

# define MOVE_SPEED 5.0f
# define MOUSE_SENSITIVITY 0.1f
# define FOV 45.0f

enum eCameraDirection { Forward, Backward, Right, Left, Up, Down};

class Camera : public GameObject
{
	public:
		Camera(float width, float heigh, bool freeFlightt);
		~Camera();

		glm::mat4		GetMatView(void) const;
		glm::mat4		GetMatProj(void) const;

		void			Move(eCameraDirection dir, float deltaTime);
		void			LookAround(float posX, float posY);
		void			UpdateFrame();
		virtual void 	Update(void);
		virtual void 	FixedUpdate(void);
		void			ResizeWindow(float newWidth, float newHeight);

		glm::mat4		GetViewMatrix(void) const;
		glm::vec3		GetPos(void) const;
		glm::vec3		GetUp(void) const;
		glm::vec3		GetDir(void) const;
		float			GetMoveSpeed(void) const;
		float			GetXRotation(void) const;
		float			GetYRotation(void) const;

		bool			GetFreeFlight() const;

		static std::shared_ptr<Camera>	instance;
	private:
		void	_CalcMatrix();

		glm::vec3	_pos;
		glm::vec3	_up;
		glm::vec3	_dir;
		glm::vec3	_right;
		float		_moveSpeed;
		float		_mouseSensitivity;
		float		_pitch;
		float		_yaw;

		glm::mat4	_view;
		glm::mat4	_projection;
		bool		_sprint;



		//Size of window
		float		_width;
		float		_height;

		bool		_freeFlight;
};

#endif
