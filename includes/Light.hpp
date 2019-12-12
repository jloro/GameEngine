#ifndef LIGHT_HPP
# define LIGHT_HPP

# include <glm.hpp>
# include <memory>
# include "Shader.hpp"
# include "AComponent.hpp"

enum class eLightType
{
	Directionnal = 0,
	Point,
	Spot
};

struct LightData
{
	glm::vec3	ambient;
	glm::vec3	diffuse;
	glm::vec3	specular;

	float		power;
	
	//Spot, point
	glm::vec3	pos;
	//Directionnal, Spot
	glm::vec3	dir;
	//Point
	float		constant;
	float 		linear;
	float		quadratic;
	//Spot
	float		cutOff;
};

class Light : public AComponent
{
	public:
		Light(eLightType type);
		virtual	~Light();

		void	SendLightToShader(std::shared_ptr<Shader> shader) const;

		eLightType	GetLightType() const;

		LightData	data;
	private:
		eLightType	_type;
};

#endif
