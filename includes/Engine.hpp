#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <iostream>
# include <list>

# include "GameObject.hpp"
# include "SdlWindow.hpp"
# include "Time.hpp"
# include "Skybox.hpp"
# include "ARenderer.hpp"
# include "Framebuffer.hpp"
# include "PostProcess.hpp"
# include "Text.hpp"
# include "UiText.hpp"

enum eKeyState {
	KEY_PRESS, //key press during frame
	KEY_RELEASE, //key release during frame
	KEY_DOWN,
	KEY_UP

};

namespace Engine42
{
	class Engine 
	{

		public: 
			/*	constructors / destrucors	*/
			virtual ~Engine(void); 

			/*	public variables	*/
			/*	public functions	*/
			static void            AddRenderer(std::list<std::shared_ptr<ARenderer>> renderers);
			static void            AddRenderer(std::shared_ptr<ARenderer> renderer);
			static void            AddFramebuffer(std::shared_ptr<Framebuffer>  fbo);
			static void            SetWindow(const SdlWindow *win);
			static void            AddGameObject(std::shared_ptr<GameObject> object);
			static void            AddGameObject(std::list<std::shared_ptr<GameObject>> objects);
			static void            AddUIElement(std::shared_ptr<UiText> object);
			static void            ChangeFontUI(std::shared_ptr<Text> font);
			static void            SetSkybox(std::shared_ptr<Skybox> skybox);
			static void            AddPostProcessShader(std::shared_ptr<Shader> postProcessShader);
			static std::shared_ptr<Text> GetFontUI();


			static void            Loop(void);
			static const SDL_Event &GetEvent();
			static const Uint8     *GetKeyInput();
			static eKeyState		GetKeyState(Uint8 scancode);
			static bool             Destroy(ARenderer* renderer);
			static void             ReloadShaders(void);
			static void             Clear(void);
			void             ResizeWindow(int width, int height);

			static void	createFBO();
		private:
			unsigned int _fbo;
			unsigned int _colorBuffer;
			unsigned int _rbo;
			unsigned int quadVAO;
			unsigned int quadVBO;
			std::shared_ptr<PostProcess>	_shaderFbo;
			std::map<Uint8, eKeyState>	_keyboard;
			std::vector<Uint8>			_keyboardKeys;
			/*  private constructor*/
			Engine(void); 
			/*	private variables	*/
			static Engine                       _inst;
			std::list<std::shared_ptr<ARenderer>>           _renderers;
			std::list<std::shared_ptr<Framebuffer>>			_framebuffers;
			std::list<std::shared_ptr<GameObject>>   _gameObjs;
			std::list<std::shared_ptr<UiText>>   _UI;
			std::shared_ptr<Text>					_fontUI;

			bool								_clear;
			SDL_Event                           _event;
			const Uint8                         *_keys;
			const SdlWindow                     *_win;
			std::shared_ptr<Skybox>             _skybox;       
			/*	private functions	*/
			void                                _RenderAll(void);
			void                                _UpdateAll(void);
			void                                _FixedUpdateAll(void);
			void								_UpdateKeyboard(void);
			void								_InitKeyboard(void);

	};
}

#endif
