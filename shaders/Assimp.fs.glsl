#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 Pos;  

struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
	int hasSpecularMap;
	int hasAmbientMap;
	int hasDiffuseMap;
    float shininess;
	int type;
};
/*
enum eLightType
{
	Directionnal = 0,
	Point = 1,
	Spot = 2
};
*/
struct LightData
{
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;

	//Spot, point
	vec3	pos;
	//Directionnal, Spot
	vec3	dir;
	//Point
	float		constant;
	float 		linear;
	float		quadratic;
	//Spot
	float		cutOff;
	int 		isPoint;
	int 		isDir;
	int 		isSpot;
};

uniform Material material;
uniform LightData light;
uniform sampler2D	texture_diffuse;
uniform sampler2D	texture_ambient;
uniform sampler2D	texture_specular;
uniform	vec3		uCamPos;
uniform mat4 model;

void main()
{
	vec4 textureDiffuse = texture(texture_diffuse, TexCoords);
	vec4 textureAmbient = texture(texture_ambient, TexCoords);
	vec4 textureSpecular = texture(texture_specular, TexCoords);

	// ambient
	vec3 ambient =  material.ambient.xyz * light.ambient * mix(vec3(1.0f), textureAmbient.rgb, material.hasAmbientMap);

	// diffuse 
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.pos - Pos) * light.isPoint + normalize(light.dir) * (1 - light.isPoint);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * material.diffuse.xyz * light.diffuse * mix(vec3(1.0f), textureDiffuse.rgb, material.hasDiffuseMap);

	// specular
	vec3 viewDir = normalize(uCamPos - Pos);
	vec3 reflectDir = reflect(lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * material.specular.xyz * light.specular * mix(vec3(1.0f), textureSpecular.rgb, material.hasSpecularMap);  


	float distance = length(light.pos - Pos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
	
	ambient *= mix(1.0f, attenuation, light.isPoint);
	diffuse *= mix(1.0f, attenuation, light.isPoint);
	specular *= mix(1.0f, attenuation, light.isPoint);

	vec3 result = ambient + diffuse + specular;

	FragColor =  vec4(result, 1.0);
} 
