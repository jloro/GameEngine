
#include "Skybox.hpp"
#include <iostream>

Skybox::Skybox(const std::vector<std::string> &texFilenames,  const std::vector< const char *> &shadersFilenames, 
		const std::vector<GLenum> &shaderType)
{

	Texture texture;
	_shader.reset(new Shader(shadersFilenames, shaderType));
	_cubeMap = _LoadCubeMap(texFilenames);
	texture.id = _cubeMap;
	texture.type =  eTextureType::Cubemap;
	_LoadModel();
}

void	Skybox::_LoadModel()
{
	std::vector<float> vertices = {
		-0.500000, -0.500000, 0.500000,
		0.500000, -0.500000, 0.500000,
		-0.500000, 0.500000, 0.500000,
		0.500000, 0.500000, 0.500000,
		-0.500000, 0.500000, -0.500000,
		0.500000, 0.500000, -0.500000,
		-0.500000, -0.500000, -0.500000,
		0.500000, -0.500000, -0.500000
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 1, 3,
		2, 3, 4,
		4, 3, 5,
		4, 5, 6,
		6, 5, 7,
		6, 7, 0,
		0, 7, 1,
		1, 7, 3,
		3, 7, 5,
		6, 0, 4,
		4, 0, 2
	};

	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	glBindVertexArray(0);
}

Skybox::~Skybox(void)
{
}
void    Skybox::Draw(void) const
{
	glDepthFunc(GL_LEQUAL); 
	glDepthMask(GL_FALSE);
	_shader->use();
	_shader->setMat4("view",glm::mat4(glm::mat3(Camera::instance->GetViewMatrix())));  
	_shader->setMat4("projection", Camera::instance->GetMatProj());
	glBindVertexArray(_vao);
	_shader->setInt("skybox", _cubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeMap);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
}

unsigned int Skybox::_LoadCubeMap(const std::vector<std::string> &filenames)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < filenames.size(); i++)
	{
		unsigned char *data = stbi_load(filenames[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
					0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
					);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << filenames[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
