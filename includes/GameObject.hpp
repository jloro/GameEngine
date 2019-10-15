#ifndef GAMEOBJECT_HPP
# define GAMEOBJECT_HPP
# include "SDL.h"
# include "Transform.hpp"
# include <memory>
# include <list>

class AComponent;

class GameObject
{
	public:
		GameObject(void);
		GameObject(Transform trans);
		GameObject(Transform trans, std::string tag);
		GameObject(std::string tag);
		virtual ~GameObject(void);
		virtual std::shared_ptr<Transform> GetTransform(void) const;
		void AddComponent(std::shared_ptr<AComponent> component);
		template<class T>
		std::shared_ptr<T> GetComponent()
		{
			std::shared_ptr<T>  dst;
			for (auto it : _components)
			{
				try 
				{ 
					dst = std::dynamic_pointer_cast<T>(it);
					if (dst == nullptr)
						continue;
				}
				catch (std::exception &e) { continue; }
				return dst;
			}
			return dst;
		}
		
		template<class T>
		std::list<std::shared_ptr<T>> GetComponents()
		{
			std::list<std::shared_ptr<T>>  lst;
			for (auto it : _components)
			{
				try 
				{ 
					std::shared_ptr<T> dst = std::dynamic_pointer_cast<T>(it);
					lst.push_back(dst);
				}
				catch (std::exception &e) { continue; }
			}
			return lst;
		}

		virtual void	Update(void);
		virtual void	FixedUpdate(void);
		std::string		GetTag() const;
		void			SetTag(std::string tag);
		bool			CompareTags(std::string otherTag);
		bool 			destroyOnReset;
	protected:
		std::string					_tag;
		std::shared_ptr<Transform>	_transform;
		std::list<std::shared_ptr<AComponent>> _components;
};
#endif
