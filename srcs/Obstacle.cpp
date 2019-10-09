#include "Obstacle.hpp"
#include "Engine.hpp"
#include "BoxCollider.hpp"
#include "GameManager.hpp"

Obstacle::Obstacle()
{
	std::vector<const char *>	shadersPath{ "shaders/Vertex.vs.glsl", "shaders/Assimp.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	std::shared_ptr<Shader> 	myShader(new Shader(shadersPath, type));
	std::shared_ptr<Model>		modelServer(new Model("ressources/obj/server/server.obj"));
	std::shared_ptr<Model>		modelCroissant(new Model("ressources/obj/croissant/croissant.obj"));
	std::shared_ptr<Model>		modelCoin(new Model("ressources/obj/coin/coin.obj"));
	srand(time(0));
	Transform serverTransform(glm::vec3(0.0f, 0.0f, 30.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(0.2f));
	Transform croissantTransform(glm::vec3(0.0f, 0.125f, 30.0f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(0.125f));
	Transform coinTransform(glm::vec3(0.0f, 0.525f, 30.0f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(0.025f));
	for (int i = 0; i < 20; i++)
	{
		std::shared_ptr<GameObject> go(new GameObject(serverTransform));
		std::shared_ptr<ARenderer> renderer(new MeshRenderer(modelServer, myShader, nullptr, false));
		Engine42::Engine::AddRenderer(renderer);
		std::shared_ptr<ACollider> collider(new BoxCollider(go.get(), modelServer->GetMin(), modelServer->GetMax(), glm::vec3(1.0f), glm::vec3(0.0f), false));
		go->AddComponent(collider);
		go->AddComponent(renderer);
		_pillar.push_back(go);
	}
	for (int i = 0; i < 40; i++)
	{
		std::shared_ptr<GameObject> go(new GameObject(croissantTransform));
		std::shared_ptr<ARenderer> renderer(new MeshRenderer(modelCroissant, myShader, nullptr, false));
		Engine42::Engine::AddRenderer(renderer);
		std::shared_ptr<ACollider> collider(new BoxCollider(go.get(), modelCroissant->GetMin(), modelCroissant->GetMax(), glm::vec3(1.0f), glm::vec3(0.0f), false));
		go->AddComponent(collider);
		go->AddComponent(renderer);
		_jumpOver.push_back(go);
	}
	for (int i = 0; i < 40; i++)
	{
		std::shared_ptr<GameObject> go(new GameObject(coinTransform));
		go->SetTag(eTags::Coin);
		std::shared_ptr<ARenderer> renderer(new MeshRenderer(modelCoin, myShader, nullptr, false));
		Engine42::Engine::AddRenderer(renderer);
		std::shared_ptr<ACollider> collider(new BoxCollider(go.get(), modelCoin->GetMin(), modelCoin->GetMax(), glm::vec3(1.0f), glm::vec3(0.0f), false));
		go->AddComponent(collider);
		go->AddComponent(renderer);
		_coins.push_back(go);
	}
}

Obstacle::~Obstacle() {}

void	Obstacle::Reset()
{
	obstacles.clear();
	for (auto it = _pillar.begin(); it != _pillar.end(); it++)
		(*it)->GetComponent<MeshRenderer>()->SetRender(false);
	for (auto it = _jumpOver.begin(); it != _jumpOver.end(); it++)
		(*it)->GetComponent<MeshRenderer>()->SetRender(false);
	for (auto it = _coins.begin(); it != _coins.end(); it++)
		(*it)->GetComponent<MeshRenderer>()->SetRender(false);
}

void	Obstacle::Update()
{
	for (auto it = obstacles.begin(); it != obstacles.end(); it++)
	{
		if ((*it)->GetTransform()->GetWorldPos().z < -40.0f)
		{
			(*it)->GetTransform()->parent = nullptr;
			(*it)->GetComponent<MeshRenderer>()->SetRender(false);
			(*it)->GetComponent<MeshRenderer>()->Destroy();
			obstacles.erase(it);
		}
		if ((*it)->GetTag() == eTags::Coin)
			(*it)->GetTransform()->rotation.y += 2.0f;
	}
}

void	Obstacle::FixedUpdate()
{

}

void	Obstacle::AddObstacle(bool pillar, std::shared_ptr<Transform> parent)
{
	std::list<std::shared_ptr<GameObject>>::iterator it, end;
	int max = 0;
	int i = 0;
	bool addCoin = false;
	if (rand() % 100 < 75)
		addCoin = true;
	if (pillar)
	{
		it = _pillar.begin();
		end = _pillar.end();
	}
	else
	{
		it = _jumpOver.begin();
		end = _jumpOver.end();
		max = 1;
	}


	bool left = true, right = true, middle = true;
	for (;it != end; it++)
	{
		if (!(*it)->GetComponent<MeshRenderer>()->IsRender())
		{
			(*it)->GetTransform()->parent = parent;
			(*it)->GetTransform()->position.z = 0.0f;
			if (pillar)
				(*it)->GetTransform()->position.x = (ROW_WIDTH / 40.0f)* _GetRandomRow(left, middle, right);
			else
				(*it)->GetTransform()->position.x = (ROW_WIDTH / 40.0f)* _GetRandomRow(left, middle, right);
			if ((*it)->GetTransform()->position.x == 0)
				middle = false;
			else if ((*it)->GetTransform()->position.x == ROW_WIDTH / -40.0f)
				left = false;
			else
				right = false;
			(*it)->GetComponent<MeshRenderer>()->SetRender(true);
			Engine42::Engine::AddRenderer((*it)->GetComponent<MeshRenderer>());
			obstacles.push_back(*it);
			if (pillar || i == max)
				break;
			i++;
		}
	}

	if (addCoin)
	{

	for (auto it = _coins.begin(); it != _coins.end(); it++)
	{
		if (!(*it)->GetComponent<MeshRenderer>()->IsRender())
		{
			(*it)->GetTransform()->parent = parent;
			(*it)->GetTransform()->position.z = 0.0f;
			(*it)->GetTransform()->position.x = (ROW_WIDTH / 40.0f)* _GetRandomRow(left, middle, right);
			(*it)->GetComponent<MeshRenderer>()->SetRender(true);
			Engine42::Engine::AddRenderer((*it)->GetComponent<MeshRenderer>());
			obstacles.push_back(*it);
			break;
		}
	}
	}
}

int		Obstacle::_GetRandomRow(bool left, bool middle, bool right)
{
	if (left && middle && right)
		return (rand() % 3 - 1);
	else if (!middle && left && right)
		return (rand() % 2 == 0 ? -1 : 1);
	else if (!left && middle && right)
		return (rand() % 2 == 0 ? 0 : 1);
	else if (!right && left && middle)
		return (rand() % 2 == 0 ? -1 : 0);
	else if (left)
		return -1;
	else if (middle)
		return 0;
	else
		return 1;

}
