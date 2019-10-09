#ifndef SKYBOX_HPP
# define SKYBOX_HPP

# include <iostream>
# include <vector>
#include "stb_image.h"
# include "glad.h"
# include "Shader.hpp"
# include "Camera.hpp"
#include "Texture.hpp"
# include <memory>
class Skybox
{

public: 
/*	constructors / Destructor*/	
    Skybox(const std::vector<std::string> &texFilenames,const std::vector< const char *> &shadersFilenames, const std::vector<GLenum> &shaderType);
    //Skybox(Skybox const & src); 
    virtual ~Skybox(void); 
/*	public variables*/	
/*	public functions*/	
    virtual void            Draw() const;
	void	_LoadModel();

    std::string const	toString(void) const;


protected:
    unsigned int _vbo;
    unsigned int _vao;
    unsigned int _ebo;
    unsigned int _cubeMap;
/*	protected variables*/
    std::shared_ptr<Shader>         _shader;
/*	protected functions*/
    //void _CreateCube(void);

    static unsigned int _LoadCubeMap(const std::vector<std::string> &filenames);

};

#endif
