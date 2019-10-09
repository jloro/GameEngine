#ifndef MESHRENDERER_HPP
# define MESHRENDERER_HPP

# include <iostream>
# include "Model.hpp"
# include "Camera.hpp"
# include "Transform.hpp"
# include "Time.hpp"
# include "ARenderer.hpp"
# include <memory>

class MeshRenderer : public ARenderer
{
public: 
/*	constructors / destrucors	*/
    MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<Shader>  shader, 
    std::shared_ptr<GameObject> obj = nullptr, bool render = true);
    MeshRenderer(const MeshRenderer & src); 
    virtual ~MeshRenderer(void); 

/*	public variables	*/
/*	public functions	*/
    void                    Destroy(void);
	MeshRenderer &		    operator=(const MeshRenderer & rhs);
    virtual void        Draw() const;
	bool				IsRender() const;
	void				SetRender(bool render);
protected:
    std::shared_ptr<Model>		_model;
	bool						_render;

};
#endif

