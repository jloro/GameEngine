#ifndef TRANSFORM_HPP
# define TRANSFORM_HPP

# include <glm.hpp>
# include <iostream>
# include <memory>
//# include "glm.hpp"
# include "gtc/matrix_transform.hpp"

struct Transform
{
    public :
/*  constructors / destructors    */
    Transform(void);
    Transform(const Transform &src);
    Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, std::shared_ptr<Transform> parent = nullptr);
    Transform(glm::vec3 pos, glm::vec3 scale, std::shared_ptr<Transform> parent = nullptr);
    Transform(glm::vec3 pos, std::shared_ptr<Transform> parent = nullptr);
    virtual ~Transform(void);
/*  public variables    */
    glm::vec3	position;
    glm::vec3	rotation;
    glm::vec3	scale;
    std::shared_ptr<Transform> parent;
    virtual glm::mat4       GetLocalMatrix(void) const;
    virtual glm::mat4       GetMatrix(void) const;
    virtual void            SetLocalMatrix(glm::mat4 matrix);
    virtual void            UpdateMatrix(void);
	virtual	glm::vec3		GetWorldPos(void) const;
	virtual	glm::vec3		GetWorldScale(void) const;

/*  public functions    */
    std::string  toString(void) const;
    Transform &		operator=(const Transform & rhs);
    protected :
    glm::mat4                  _localMatrix;
    private :
        void    _Initialize(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, std::shared_ptr<Transform> parent = nullptr);
};
#endif

std::ostream &	operator<< (std::ostream & o, const Transform & rhs);
