#include "RoomManager.hpp"
#include "ARenderer.hpp"
#include "Engine.hpp"
#include <gtx/rotate_vector.hpp>
#include "gtx/compatibility.hpp"
#include "GameManager.hpp"
const unsigned int	RoomManager::maxRooms = 15;

RoomManager::RoomManager() : _nbRooms(0), _rotationMax(-90), _rotateWay(2.0f), _cornerSpawned(true), _stop(false)
{
	obstacles.reset(new Obstacle);
	Engine42::Engine::AddGameObject(obstacles);
	_rotate = 0;
	_nextRot = glm::vec3(0.0f, 0.0f, 0.0f);
	_nextPos = glm::vec3(0.0f, 0.0f, 0.0f);
	_way = glm::vec3(0.0f, 0.0f, 1.0f);
	_wayPlacement = glm::vec3(0.0f, 0.0f, 1.0f);

	std::vector<const char *>	shadersPath{ "shaders/Vertex.vs.glsl", "shaders/Assimp.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	std::shared_ptr<Shader> 	myShader(new Shader(shadersPath, type));
	_corridor.reset(new Model("ressources/obj/corridor/couloir.obj"));
	_corner.reset(new Model("ressources/obj/corridor/corner.obj"));
	Transform trans(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(40.0f, 40.0f, 40.0f), _transform);
	srand(time(0));
	for (unsigned int i = 0; i < 20; i++)
	{
		std::shared_ptr<GameObject> go(new GameObject(trans, eTags::Corridor));
		std::shared_ptr<ARenderer> renderer(new MeshRenderer(_corridor, myShader, nullptr, false));
		go->AddComponent(renderer);
		corridors.push_back(go);
	}
	for (unsigned int i = 0; i < 10; i++)
	{
		std::shared_ptr<GameObject> go(new GameObject(trans, eTags::Corner));
		std::shared_ptr<ARenderer> renderer(new MeshRenderer(_corner, myShader, nullptr, false));
		go->AddComponent(renderer);
		corners.push_back(go);
	}

	_Init();
}

void	RoomManager::Reset()
{
	obstacles->Reset();
	Engine42::Engine::AddGameObject(obstacles);
	_stop = false;
	_nbRooms = 0;
	_rooms.clear();
	_rotate = 0;
	_nextRot = glm::vec3(0.0f, 0.0f, 0.0f);
	_nextPos = glm::vec3(0.0f, 0.0f, 0.0f);
	_way = glm::vec3(0.0f, 0.0f, 1.0f);
	_wayPlacement = glm::vec3(0.0f, 0.0f, 1.0f);
	_rotationMax = -90;
	_rotateWay = 2.0f;
	_cornerSpawned = true;
	_transform->rotation.y = 0.0f;
	_transform->UpdateMatrix();
	for (auto it = corridors.begin(); it != corridors.end(); it++)
	{
		(*it)->GetTransform()->position = glm::vec3(0.0f);
		(*it)->GetTransform()->rotation = glm::vec3(0.0f);
		(*it)->GetComponent<MeshRenderer>()->SetRender(false);
		(*it)->GetTransform()->UpdateMatrix();
	}
	for (auto it = corners.begin(); it != corners.end(); it++)
	{
		(*it)->GetTransform()->position = glm::vec3(0.0f);
		(*it)->GetTransform()->rotation = glm::vec3(0.0f);
		(*it)->GetComponent<MeshRenderer>()->SetRender(false);
		(*it)->GetTransform()->UpdateMatrix();
	}
	_Init();
}

void	RoomManager::_Init()
{

	for (auto it = corridors.begin(); it != corridors.end() && _nbRooms < 3; it++)
	{
		if (!(*it)->GetComponent<MeshRenderer>()->IsRender())
		{
			_rooms.push_back((*it));
			(*it)->GetTransform()->position = _nextPos;
			_nextPos += _wayPlacement * 80.0f;
			_nbRooms++;
			Engine42::Engine::AddRenderer((*it)->GetComponent<MeshRenderer>());
			(*it)->GetComponent<MeshRenderer>()->SetRender(true);
		}
	}
	for (auto it = corners.begin(); it != corners.end(); it++)
	{
		if (!(*it)->GetComponent<MeshRenderer>()->IsRender())
		{
			(*it)->SetTag(static_cast<eTags>(static_cast<int>(eTags::Corner) | static_cast<int>(eTags::CornerLeft)));
			_rooms.push_back((*it));
			(*it)->GetTransform()->position = _nextPos + _wayPlacement * 80.0f;
			_nextPos += _wayPlacement * 80.0f;
			_nextRot += glm::vec3(0.0f, 90.0f, 0.0f);
			_wayPlacement = glm::rotate(_wayPlacement, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			_nextPos += _wayPlacement * 80.0f;
			_nbRooms++;
			Engine42::Engine::AddRenderer((*it)->GetComponent<MeshRenderer>());
			(*it)->GetComponent<MeshRenderer>()->SetRender(true);
			if (glm::distance(_wayPlacement, glm::vec3(1.0f, 0.0f, 0.0f)) < 0.1f || glm::distance(_wayPlacement, glm::vec3(-1.0f, 0.0f, 0.0f)) < 0.1f)
				_nextPos.x += _wayPlacement.x < 0.0f ? -80.0f : 80.0f;
			else
				_nextPos.z += _wayPlacement.z < 0.0f ? -80.0f : 80.0f;
			break;
		}
	}
}
RoomManager::~RoomManager() {}

void	RoomManager::Stop()
{
	_stop = true;
}
void	RoomManager::Update()
{
	if (!_stop)
	{
		if (_nbRooms < maxRooms)
		{
			if (rand() % 100 > 90 && !_cornerSpawned)
				_AddCorner(static_cast<bool>(rand() % 2));
			else
				_AddCorridor();
		}
		if (_rotate == 1)
		{
			_transform->rotation.y -= _rotateWay;
			_transform->UpdateMatrix();
		}
		for (auto it = _rooms.begin(); it != _rooms.end(); it++)
		{
			glm::vec3 tmp = (*it)->GetTransform()->position * _way;
			if (tmp.x + tmp.y + tmp.z < 40 && (static_cast<int>((*it)->GetTag()) & static_cast<int>(eTags::Corner)) != 0)
			{
				if (((GameManager::instance->player->GetRow() != 0 && (static_cast<int>((*it)->GetTag()) & static_cast<int>(eTags::CornerLeft)) != 0) || (GameManager::instance->player->GetRow() != 2 && (static_cast<int>((*it)->GetTag()) & static_cast<int>(eTags::CornerRight)) != 0)) && _rotate == 0)
					GameManager::instance->Die();
				if ((_transform->rotation.y < _rotationMax || _transform->rotation.y > _rotationMax) && !GameManager::instance->player->GetDead())
				{
					_rotate = 1;
					_way = glm::rotate(_way, glm::radians(_rotateWay), glm::vec3(0.0f, 1.0f, 0.0f));
				}
				else
					_rotate = 2;
			}
			if (tmp.x + tmp.y + tmp.z < -240)
			{
				if ((static_cast<int>((*it)->GetTag()) & static_cast<int>(eTags::Corner)) != 0)
				{
					_cornerSpawned = false;
					_rotate = 0;
				}
				(*it)->GetComponent<MeshRenderer>()->SetRender(false);
				(*it)->GetComponent<MeshRenderer>()->Destroy();
				_rooms.erase(it);
				_nbRooms--;
				continue;
			}
			(*it)->GetTransform()->position -= _way * static_cast<float>(GameManager::speedWorld) * Engine42::Time::GetDeltaTime();
		}
		_nextPos -= _way * static_cast<float>(GameManager::speedWorld) * Engine42::Time::GetDeltaTime();
	}
}

void	RoomManager::FixedUpdate()
{

}

void	RoomManager::_AddCorner(bool left)
{
	for (auto it = corners.begin(); it != corners.end(); it++)
	{
		if (!(*it)->GetComponent<MeshRenderer>()->IsRender())
		{
			if (left)
			{
				(*it)->SetTag(static_cast<eTags>(static_cast<int>(eTags::Corner) | static_cast<int>(eTags::CornerLeft)));
				_rotateWay = 2.0f;
				_cornerSpawned = true;
				_rotationMax -= 90;
				_rooms.push_back((*it));
				(*it)->GetTransform()->position = _nextPos + _wayPlacement * 80.0f;
				(*it)->GetTransform()->rotation = _nextRot;
				_nextPos += _wayPlacement * 80.0f;
				_nextRot += glm::vec3(0.0f, 90.0f, 0.0f);
				_wayPlacement = glm::rotate(_wayPlacement, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				_nextPos += _wayPlacement * 80.0f;
				_nbRooms++;
				Engine42::Engine::AddRenderer((*it)->GetComponent<MeshRenderer>());
				(*it)->GetComponent<MeshRenderer>()->SetRender(true);
				if (glm::distance(_wayPlacement, glm::vec3(1.0f, 0.0f, 0.0f)) < 0.1f || glm::distance(_wayPlacement, glm::vec3(-1.0f, 0.0f, 0.0f)) < 0.1f)
					_nextPos.x += _wayPlacement.x < 0.0f ? -80.0f : 80.0f;
				else
					_nextPos.z += _wayPlacement.z < 0.0f ? -80.0f : 80.0f;
				break;
			}
			else
			{
				(*it)->SetTag(static_cast<eTags>(static_cast<int>(eTags::Corner) | static_cast<int>(eTags::CornerRight)));
				_rotateWay = -2.0f;
				_cornerSpawned = true;
				_rotationMax += 90;
				_rooms.push_back((*it));
				(*it)->GetTransform()->position = _nextPos + _wayPlacement * 80.0f;
				(*it)->GetTransform()->rotation = _nextRot;
				(*it)->GetTransform()->rotation.y += 90.0f;
				_nextPos += _wayPlacement * 80.0f;
				_nextRot -= glm::vec3(0.0f, 90.0f, 0.0f);
				_wayPlacement = glm::rotate(_wayPlacement, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				_nextPos += _wayPlacement * 80.0f;
				_nbRooms++;
				Engine42::Engine::AddRenderer((*it)->GetComponent<MeshRenderer>());
				(*it)->GetComponent<MeshRenderer>()->SetRender(true);
				if (glm::distance(_wayPlacement, glm::vec3(1.0f, 0.0f, 0.0f)) < 0.1f || glm::distance(_wayPlacement, glm::vec3(-1.0f, 0.0f, 0.0f)) < 0.1f)
					_nextPos.x += _wayPlacement.x < 0.0f ? -80.0f : 80.0f;
				else
					_nextPos.z += _wayPlacement.z < 0.0f ? -80.0f : 80.0f;
				break;
			}
		}
	}
}

void	RoomManager::_AddCorridor()
{
	for (auto it = corridors.begin(); it != corridors.end(); it++)
	{
		if (!(*it)->GetComponent<MeshRenderer>()->IsRender())
		{
			_rooms.push_back((*it));
			(*it)->GetTransform()->position = _nextPos;
			_nextPos += _wayPlacement * 80.0f;
			(*it)->GetTransform()->rotation = _nextRot;
			_nbRooms++;
			Engine42::Engine::AddRenderer((*it)->GetComponent<MeshRenderer>());
			(*it)->GetComponent<MeshRenderer>()->SetRender(true);
			(*it)->GetTransform()->UpdateMatrix();
			obstacles->AddObstacle(static_cast<bool>(rand() % 2), (*it)->GetTransform());
			break;
		}
	}
}

bool	RoomManager::GetCornerSpawned() const { return _cornerSpawned; }
