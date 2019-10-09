#ifndef ARENDERER_HPP
# define ARENDERER_HPP

# include <iostream>
# include "Transform.hpp"
# include "Shader.hpp"
# include "Mesh.hpp"
# include "AComponent.hpp"

class ARenderer : public AComponent
{

public: 
/*	constructors / destrucors	*/
    ARenderer();
    ARenderer(std::shared_ptr<GameObject> obj);
    ARenderer(std::shared_ptr<Shader> shader, GameObject *obj = nullptr);
    ARenderer(std::shared_ptr<Shader> shader, std::shared_ptr<GameObject> obj = std::shared_ptr<GameObject>(nullptr));
    virtual ~ARenderer();
/*	public variables	*/
/*	public functions	*/

    virtual std::shared_ptr<Shader> GetShader(void) const;
    //void                    Destroy(void);
    virtual void                    SetShader(std::shared_ptr<Shader>  shader);
    virtual void        Draw() const = 0;
protected:
    std::shared_ptr<Shader>    _shader;
};
#endif
