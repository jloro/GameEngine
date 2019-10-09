/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Model.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:28:53 by jloro             #+#    #+#             */
/*   Updated: 2019/09/27 14:41:30 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODEL_HPP
# define MODEL_HPP

# include "Mesh.hpp"
# include <assimp/scene.h>
# include <glm.hpp>
# include <gtx/quaternion.hpp>
# include <map>
# include <assimp/Importer.hpp>
# include "SDL.h"
# include "Animation.hpp"
# include "Node.hpp"

# define ROTATION 0
# define SCALING 1
# define TRANSLATION 2

unsigned int TextureFromFile(const char *path, const std::string &directory);
class Model
{
	public:
/*  constructors / Destructor*/
		Model(void);
		Model(const char* path);
		Model(const Model & rhs);
		virtual~Model();
/*  public functions    */
		virtual void	Draw(const std::shared_ptr<Shader>  shader);
		void			PauseAnimation(void);
		void			PlayAnimation(void);
		void			AddAnimation(const char* path);
		void			ChangeAnimation(unsigned int anim);
        Model & operator=(const Model &rhs);
		glm::vec3		GetMin(void) const;
		glm::vec3		GetMax(void) const;
		float			GetChrono() const;
		unsigned int	GetCurrentAnimation() const;
		const std::shared_ptr<Animation>	GetAnimation(unsigned int i) const;
	protected:
/*  protected variables    */
		std::vector<Mesh>	_meshes;
		std::string			_dir;
		std::map<std::string, unsigned int>			_boneMap;
		std::vector<BoneInfo>	_boneInfo;
		std::vector<std::shared_ptr<Animation>>	_animations;
		unsigned int			_currentAnimation;
		float					_chrono;
		std::shared_ptr<Node>	_skeleton;
		glm::mat4				_globalTransform;
		bool					_playing;
		glm::vec3				_min;
		glm::vec3				_max;

		bool					_hasAnim;
		const aiScene*			_scene;
		Assimp::Importer		_importer;
/*  protected functions    */
		void					_LoadModel(std::string path);
		void					_ProcessNode(aiNode *node, const aiScene *scene);

		void					_LoadBones(aiMesh *mesh, std::vector<Vertex>& vertices);
		void					_AddBoneData(unsigned int id, float weight, Vertex& vertex);
		void					_BoneTransform(float timeInSecond, const std::shared_ptr<Shader>  shader);
		void					_ReadNodeHierarchy(float animationTime, std::shared_ptr<Node> node, const glm::mat4 parentTransform);
		glm::quat				_CalcInterpolatedRotation(float animationTime, std::shared_ptr<NodeAnim> nodeAnim) const;
		unsigned int			_FindKeys(float animationTime, std::shared_ptr<NodeAnim> nodeAnim, int state) const;

		Mesh					_ProcessMesh(aiMesh *mesh, const aiScene *scene);
		std::vector<Texture>	_LoadMaterialTexture(aiMaterial *mat, aiTextureType type, eTextureType typeName);
		static Texture			_LoadSimpleTexture(eTextureType typeName, const std::string filename);
		static unsigned int 	_TextureFromFile(const char *path, const std::string &directory);
		static unsigned int 	_TextureFromFile(const std::string &filename) ;
		unsigned int 	_TextureFromFile(const std::string &filename, aiTexture** textureArray) ;
		static std::string 		_GetFilename(const char *path, const std::string &directory);
};

#endif
