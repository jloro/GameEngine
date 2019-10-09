#include "Player.hpp"
#include "Engine.hpp"
#include "gtx/compatibility.hpp"
#include "BoxCollider.hpp"
#include "GameManager.hpp"

Player::Player(std::shared_ptr<Model> character, std::shared_ptr<Shader> shader, Transform transform) : GameObject(transform), _character(character), _jump(false), _dead(false)
{
	std::shared_ptr<ARenderer> render(new MeshRenderer(character, shader));
	Engine42::Engine::AddRenderer(render);
	AddComponent(render);
	std::shared_ptr<ACollider> collider(new BoxCollider(this, _character->GetMin(), _character->GetMax(), glm::vec3(0.5f, 1.0f, 1.0f), glm::vec3(0.0f), false));
	AddComponent(collider);

}

Player::~Player() {}


void    Player::FixedUpdate(void)
{
}

bool	Player::GetDead() const { return _dead; }
void	Player::SetDead(bool dead)
{
	_dead = dead;
	_character->PlayAnimation();
	//GameManager::instance->PlayGameOver();
}
int		Player::GetRow() const
{
	if (_transform->position.x < ROW_WIDTH / 2.0f && _transform->position.x > -ROW_WIDTH / 2.0f)
		return 1;
	else if (_transform->position.x > ROW_WIDTH / 2.0f)
		return 0;
	else
		return 2;
}

void    Player::Update(void)
{
	if (!_dead)
	{
		if (Engine42::Engine::GetKeyState(SDL_SCANCODE_RIGHT) == KEY_DOWN && _transform->position.x > -ROW_WIDTH * 2.0f)
			_transform->position.x = glm::lerp(_transform->position.x, -ROW_WIDTH * 2.0f, SPEED * Engine42::Time::GetDeltaTime());
		if (Engine42::Engine::GetKeyState(SDL_SCANCODE_RIGHT) == KEY_UP)
			_transform->position.x = glm::lerp(_transform->position.x, 0.0f, SPEED * Engine42::Time::GetDeltaTime());
		if (Engine42::Engine::GetKeyState(SDL_SCANCODE_LEFT) == KEY_DOWN && _transform->position.x < ROW_WIDTH * 2.0f)
			_transform->position.x = glm::lerp(_transform->position.x, ROW_WIDTH * 2.0f, SPEED * Engine42::Time::GetDeltaTime());
		if (Engine42::Engine::GetKeyState(SDL_SCANCODE_LEFT) == KEY_UP)
			_transform->position.x = glm::lerp(_transform->position.x, 0.0f, SPEED * Engine42::Time::GetDeltaTime());
		if (Engine42::Engine::GetKeyState(SDL_SCANCODE_UP) == KEY_PRESS && _jump == false)
		{
			_velocityY = 70.0f;
			_jump = true;
			_jumpState = JUMPING;
			_character->PauseAnimation();
		}
		if (_jump && _jumpState == JUMPING)
			_transform->position.y += _velocityY * Engine42::Time::GetDeltaTime();
		if (_jump && _transform->position.y > 19.0f && _jumpState == JUMPING)
		{
			//_jumpState = FALLING;
			_velocityY = 40.0f;
		}
		if (_jump && _transform->position.y > 25.0f)
		{
			_jumpState = FALLING;
		}
		if (_jump && _transform->position.y < 19.0f && _jumpState == FALLING)
		{
			_velocityY = 75.0f;
		}
	}
	else
	{
		if (_character->GetCurrentAnimation() == 1 && _character->GetChrono() >= _character->GetAnimation(1)->duration / _character->GetAnimation(1)->ticksPerSecond)
			GameManager::instance->Reset();
	}
	if (_jump && _jumpState == FALLING)
		_transform->position.y -= _velocityY * Engine42::Time::GetDeltaTime();
	if (_jump && _transform->position.y <= 0.0f)
	{
		_character->PlayAnimation();
		_jump = false;
		_transform->position.y = 0.0f;
	}
}
