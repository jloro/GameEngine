
#include "SdlWindow.hpp"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Engine.hpp"
#include "Terrain.hpp"
#include "Skybox.hpp"
#include "Player.hpp"
#include "FpsDisplay.hpp"
#include "GameManager.hpp"
#include "SDL_mixer.h"

std::shared_ptr<Skybox> CreateSkyBox()
{
	std::vector<std::string>	texturesPath{
	"ressources/textures/craterlake_ft.tga",
	"ressources/textures/craterlake_bk.tga",
	"ressources/textures/craterlake_up.tga",
	"ressources/textures/craterlake_dn.tga",
	"ressources/textures/craterlake_rt.tga",
	"ressources/textures/craterlake_lf.tga", 
	};
	std::vector<const char *>	shadersPath{"shaders/skybox.vs.glsl", "shaders/skybox.fs.glsl"};
	std::vector<GLenum> type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
	std::shared_ptr<Skybox> skybox(new Skybox(texturesPath, shadersPath, type));
	return skybox;
}

bool InitModels(SdlWindow &win)
{
	std::vector<const char *>	shadersPath{ "shaders/Skeletical.vs.glsl", "shaders/Assimp.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	Camera* cam = new Camera(win.GetWidth(), win.GetHeight(), false);

	std::shared_ptr<Model>	test(new Model("ressources/obj/Running/42stud.fbx"));
	test->AddAnimation("ressources/animations/Dying Backwards.fbx");
	std::shared_ptr<Shader> 	skeletalShader(new Shader(shadersPath, type));
	shadersPath[0] = "shaders/Vertex.vs.glsl";
	std::shared_ptr<Shader> 	stdShader(new Shader(shadersPath, type));
	std::shared_ptr<Player> player(new Player(test, skeletalShader, Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f))));
	Engine42::Engine::AddGameObject(player);
	Engine42::Engine::SetWindow(&win);
	Engine42::Engine::AddGameObject(cam->instance);
	GameManager *gm = new GameManager(player);
	Engine42::Engine::AddGameObject(gm->instance);
	gm->destroyOnReset = false;
	cam->destroyOnReset = false;
	return true;
}
int ErrorQuit(std::string txt1, std::string txt2)
{
	if (!txt1.empty()) {std::cout << txt1 << std::endl;}
	if (!txt2.empty()) {std::cout << txt2 << std::endl;}
	SDL_Quit();
	return (EXIT_SUCCESS);
}
bool initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		ErrorQuit("Erreur lors de l'initialisation de la SDL :", SDL_GetError());
		return false;
	}
	if (Mix_Init(MIX_INIT_OGG) == -1)
	{
		ErrorQuit("SDL_Mixer  error :", Mix_GetError());
		return false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048))
	{
		ErrorQuit("SDL_Mixer error :", Mix_GetError());
		return false;
	}
	return true;
}

int				main(void)
{
	if (!initSDL())
		return EXIT_SUCCESS;
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		return ErrorQuit("Failed to init freetype library", std::string());
	}
	SdlWindow	win(800, 400, false, true, "42run");
	win.CreateGlContext(4, 1, true, 24);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, win.GetWidth(), win.GetHeight());
	try
	{
		std::shared_ptr<Text>	font(new Text("ressources/fonts/SEASRN__.ttf", ft, 24));
		Engine42::Engine::ChangeFontUI(font);
	 	InitModels(win);
	}
	catch(const std::exception& e)
	{
		return ErrorQuit(e.what(), std::string());
	}
	Engine42::Engine::Loop();
	SDL_Quit();
}
