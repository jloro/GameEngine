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
# include "Font.hpp"
# include "UiText.hpp"
# include "Material.hpp"
# include "Light.hpp"

enum class eKeyState {
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
			static void	SetUp();
			static void            AddRenderer(std::list<std::shared_ptr<ARenderer>> renderers);
			static void            AddRenderer(std::shared_ptr<ARenderer> renderer);
			static void            AddFramebuffer(std::shared_ptr<Framebuffer>  fbo);
			static void            SetWindow(const SdlWindow *win);
			static void            AddGameObject(std::shared_ptr<GameObject> object);
			static void            AddGameObject(std::list<std::shared_ptr<GameObject>> objects);
			static void            AddUIElement(std::shared_ptr<AUi> object);
			static void            ChangeFontUI(std::shared_ptr<Font> font);
			static void            SetSkybox(std::shared_ptr<Skybox> skybox);
			static void            AddPostProcessShader(std::shared_ptr<Shader> postProcessShader);
			static std::shared_ptr<Font> GetFontUI();


			static void            Loop(void);
			static std::list<const SDL_Event> GetEvents();
			static const Uint8     *GetKeyInput();
			static eKeyState		GetKeyState(Uint8 scancode);
			static bool             Destroy(ARenderer* renderer);
			static bool             Destroy(GameObject *go);
			static void             ReloadShaders(void);
			static void             Clear(void);
			static void				AddTag(std::string tag);
			static int				GetTag(std::string tag);
			static void				InitKeyboard(void);

			void             		ResizeWindow(int width, int height);
			static void				AddLight(std::shared_ptr<GameObject> light);
			static std::list<std::shared_ptr<Light>> &	GetLights();
			static void	createFBO();
		private:

			unsigned int _fbo;
			unsigned int _colorBufferMS;
			unsigned int _rbo;
			unsigned int _quadVAO;
			unsigned int _quadVBO;

			unsigned int _fboIntermediate;
			unsigned int _colorBuffer;
			std::shared_ptr<Shader>	_shaderFbo;

			std::map<Uint8, eKeyState>	_keyboard;
			std::map<std::string, int>	_tags;
			/*  private constructor*/
			Engine(void); 
			/*	private variables	*/
			static Engine							_inst;
			std::list<std::shared_ptr<ARenderer>>   _renderers;
			std::list<std::shared_ptr<Framebuffer>>	_framebuffers;
			std::list<std::shared_ptr<GameObject>>	_gameObjs;
			std::list<std::shared_ptr<Light>>   	_lights;
			std::list<std::shared_ptr<AUi>>			_UI;
			std::shared_ptr<Font>					_fontUI;

			bool								_clear;
			std::list<const SDL_Event>			_events;
			const Uint8                         *_keys;
			const SdlWindow                     *_win;
			std::shared_ptr<Skybox>             _skybox;       
			/*	private functions	*/
			void                                _RenderAll(void);
			void                                _UpdateAll(void);
			void                                _FixedUpdateAll(void);
			void								_UpdateKeyboard(void);
			void								_OnClick() const;
			void								_OnRelease() const;

	};
}

#endif
