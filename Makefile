# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/13 16:05:39 by fchevrey          #+#    #+#              #
#    Updated: 2019/10/19 14:29:16 by jules            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libGameEngine.a

## Colors ##
PURPLE = [038;2;255;40;255
GREEN = [038;2;82;255;123
CYAN = [038;2;0;255;255
PINK = [038;2;255;0;137
YELLOW = [038;2;252;125;91
ORANGE = [038;2;239;138;5

## Sources ##
SRCS_DIR = srcs

SRCS =  Time.cpp SdlWindow.cpp Mesh.cpp Model.cpp Shader.cpp Camera.cpp \
		Engine.cpp  Transform.cpp Skybox.cpp Framebuffer.cpp PostProcess.cpp\
		AComponent.cpp GameObject.cpp ARenderer.cpp ACollider.cpp\
		PrintGlm.cpp Font.cpp MeshRenderer.cpp Terrain.cpp AUi.cpp\
		BoxColliderRenderer.cpp BoxCollider.cpp NodeAnim.cpp UiButton.cpp \
		Animation.cpp Node.cpp MusicListener.cpp SoundListener.cpp UiText.cpp \

HEADER = SdlWindow.hpp Texture.hpp Vertex.hpp Shader.hpp Mesh.hpp Time.hpp \
		GameObject.hpp Engine.hpp Transform.hpp Skybox.hpp PostProcess.hpp \
		AComponent.hpp ACollider.hpp PrintGlm.hpp  MeshRenderer.hpp Terrain.hpp  \
		Font.hpp ARenderer.hpp BoxCollider.hpp UiText.hpp UiButton.hpp\
		BoxColliderRenderer.hpp BoxCollider.hpp Model.hpp AUi.hpp\
		Camera.hpp NodeAnim.hpp Animation.hpp Node.hpp MusicListener.hpp SoundListener.hpp \

## Objects ##
OBJS = $(SRCS:.cpp=.o)
OBJS_DIR = ./objs
OBJS_PRE = $(addprefix $(OBJS_DIR)/, $(OBJS))

## Lib dirs ##
LIB_DIR = ./lib

## Macros for extern library installation ##
SDL_VER = 2.0.9
SDL_MIXER_VER = 2.0.2
ASSIMP_VER = 4.1.0

MAIN_DIR_PATH = $(shell pwd)
SDL_PATH = $(addprefix $(MAIN_DIR_PATH), /lib/sdl2)
SDL_MIXER_PATH = $(addprefix $(MAIN_DIR_PATH), /lib/sdl2_mixer)
GLAD_PATH = $(addprefix $(MAIN_DIR_PATH), /lib/glad)
GLM_PATH = $(addprefix $(MAIN_DIR_PATH), /lib/glm)
ASSIMP_PATH = $(addprefix $(MAIN_DIR_PATH), /lib/assimp-$(ASSIMP_VER))
JSON_PATH = $(addprefix $(MAIN_DIR_PATH), /lib/json)

#IRRXML_PATH = $(addprefix $(ASSIMP_PATH), /build/contrib/irrXML)

HEADER_DIR = includes/

## Includes ##
INC = -I ./$(HEADER_DIR)

SDL2_INC = $(shell sh ./lib/sdl2/bin/sdl2-config --cflags)

LIB_INCS =	-I $(GLM_PATH)/glm \
			$(SDL2_INC) \
			-I $(SDL_MIXER_PATH)/include/SDL2 \
			-I $(ASSIMP_PATH)/include/ \
			-I $(GLAD_PATH)/includes/ \
			-I $(JSON_PATH)/include


HEADERS = $(addprefix $(HEADER_DIR), $(HEADER))

INCS = $(INC) $(LIB_INCS)

## FLAGS ##
CC = clang++

CFLAGS = -Wall -Wextra -Werror -std=c++11 -Wno-unknown-pragmas

MESSAGE = "make[1]: Nothing to be done for 'all'"
DONE_MESSAGE = "\033$(GREEN)2m✓\t\033$(GREEN)mDONE !\033[0m\
				\n ========================================\n"

## RULES ##

all: CHECK_LIB_DIR ASSIMP SDL_MIXER GLAD GLM print_name $(NAME) print_end

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp $(HEADERS)
	@echo "\033$(PURPLE)m⧖	Creating	$@\033[0m"
	@export PKG_CONFIG_PATH=$(PKG_CONFIG_PATH):$(addprefix $(SDL_PATH), /lib/pkgconfig) &&\
	$(CC) -c -o $@ $< $(CFLAGS) $(INCS)

$(OBJS_DIR):
	@echo "\033$(CYAN)m➼	\033$(CYAN)mCreating $(NAME)'s objects \
	with flag : \033$(GREEN)m $(CFLAGS)\033[0m"
	@mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS_DIR) $(OBJS_PRE) $(HEADERS) 
	@echo "\033$(GREEN)m➼\t\033$(GREEN)32m Creating $(NAME)'s lib\033[0m"
	@ar rc $(NAME) $(OBJS_PRE)
	@$(eval MESSAGE = $(DONE_MESSAGE))

set_linux :
	$(eval FRAMEWORK = -lGL -ldl)

linux : set_linux all

linux_re: set_linux re

rm_obj:
	@rm -rf $(OBJS_DIR)
	@echo "\033$(PINK)36m✗	\033[0m\033$(PINK)31m$(NAME)'s object removed\033[0m"

clean: rm_obj
	@make -C $(GLAD_PATH) clean

fclean: rm_obj clean
	@rm -rf $(NAME)
	@echo "\033$(PINK)36m✗	\033[0m\033$(PINK)31m$(NAME) removed\033[0m"
	@make -C $(GLAD_PATH) fclean

re: fclean all

exe: rm_obj all

rm_SDL2:
	@rm -rf $(SDL2_PATH)
	@echo "\033$(PINK)36m✗	SDL2-$(SDL_VER) removed\033[0m"

re_SDL2: fclean rm_SDL2 all

MODE_DEBUG: change_cflag all

re_sanitize: rm_obj MODE_DEBUG

sanitize:
	@$(eval CFLAGS = -fsanitize=address)

GLM:
	@if [ ! -d "./lib/glm" ]; then \
		echo "\033$(PINK)m⚠\tGlm is not installed ! ...\033[0m"; \
		echo "\033$(CYAN)m➼\tDownloading Glm ...\033[0m"; \
		printf "\r\033$(YELLOW)m\tIn 3 ...\033[0m"; sleep 1; \
		printf "\r\033$(YELLOW)m\tIn 2 ...\033[0m"; sleep 1; \
		printf "\r\033$(YELLOW)3m\tIn 1 ...\033[0m"; sleep 1; printf "\n"; \
		cd lib &&\
		git clone https://github.com/g-truc/glm glm;\
	else \
		echo "\033$(GREEN)m✓\tGlm already installed\033[0m"; \
	fi
GLAD:
	@if [ ! -d "./lib/glad" ]; then \
		echo "\033$(PINK)m⚠\tGlad is not installed ! ...\033[0m"; \
		echo "\033$(CYAN)m➼\tDownloading Glad ...\033[0m"; \
		printf "\r\033$(YELLOW)m\tIn 3 ...\033[0m"; sleep 1; \
		printf "\r\033$(YELLOW)m\tIn 2 ...\033[0m"; sleep 1; \
		printf "\r\033$(YELLOW)3m\tIn 1 ...\033[0m"; sleep 1; printf "\n"; \
		cd lib &&\
		git clone https://github.com/jloro/Glad glad;\
		cd glad;\
		make;\
	else \
		echo "\033$(GREEN)m✓\tGlad already installed\033[0m"; \
		make -C $(GLAD_PATH);\
	fi


ASSIMP:	
	@if [ ! -d "./lib/assimp-$(ASSIMP_VER)" ]; then \
		echo "\033$(PINK)m⚠\tAssimp is not installed ! ...\033[0m"; \
		echo "\033$(CYAN)m➼\tCompiling assimp-$(ASSIMP_VER) ...\033[0m"; \
		printf "\r\033$(YELLOW)m\tIn 3 ...\033[0m"; sleep 1; \
		printf "\r\033$(YELLOW)m\tIn 2 ...\033[0m"; sleep 1; \
		printf "\r\033$(YELLOW)3m\tIn 1 ...\033[0m"; sleep 1; printf "\n"; \
		cd lib &&\
		curl -OL https://github.com/assimp/assimp/archive/v4.1.0.tar.gz && \
		tar -zxvf v$(ASSIMP_VER).tar.gz && \
		rm v$(ASSIMP_VER).tar.gz && \
		mkdir -p $(ASSIMP_PATH) && \
		cd assimp-$(ASSIMP_VER) && \
		cmake -DASSIMP_BUILD_TESTS:BOOL=OFF && \
			make && \
		cd ../.. && \
		echo "\033$(GREEN)m✓\tassimp-$(ASSIMP_VER)installed !\033[0m"; \
	else \
		echo "\033$(GREEN)m✓\tassimp-$(ASSIMP_VER) already installed\033[0m"; \
	fi

SDL2:
	@if [ ! -d "./lib/sdl2" ]; then \
		echo "\033$(PINK)m⚠\tSDL2 is not installed ! ...\033[0m"; \
		echo "\033$(CYAN)m➼\tCompiling SDL2-$(SDL_VER) ...\033[0m"; \
		printf "\r\033$(YELLOW)m\tIn 3 ...\033[0m"; sleep 1; \
		printf "\r\033$(YELLOW)m\tIn 2 ...\033[0m"; sleep 1; \
		printf "\r\033$(YELLOW)3m\tIn 1 ...\033[0m"; sleep 1; printf "\n"; \
		curl -OL http://www.libsdl.org/release/SDL2-$(SDL_VER).tar.gz && \
		tar -zxvf SDL2-$(SDL_VER).tar.gz && \
		rm SDL2-$(SDL_VER).tar.gz && \
		mkdir -p $(SDL_PATH) && \
		cd SDL2-$(SDL_VER) && \
			sh configure --prefix=$(SDL_PATH) && \
			make && \
			make install && \
		cd .. && \
		rm -rf SDL2-$(SDL_VER);\
		echo "\033$(GREEN)m✓\tSDl2-$(SDL_VER) installed !\033[0m"; \
	else \
		echo "\033$(GREEN)m✓\tSDl2-$(SDL_VER) already installed\033[0m"; \
	fi
SDL_MIXER: SDL2
	@if [ ! -d "./lib/sdl2_mixer" ]; then \
		export SDL2_CONFIG=$(addprefix $(SDL_PATH), /bin/sdl2-config); \
		echo "\033$(CYAN)m➼\tCompiling SDL2_MIXER-$(SDL_MIXER_VER) ...\033[0m"; \
		curl -OL http://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-$(SDL_MIXER_VER).tar.gz && \
		tar -zxvf SDL2_mixer-$(SDL_MIXER_VER).tar.gz && \
		rm SDL2_mixer-$(SDL_MIXER_VER).tar.gz && \
		mkdir -p $(SDL_MIXER_PATH) && \
		cd SDL2_mixer-$(SDL_MIXER_VER) && \
			sh configure --prefix=$(SDL_MIXER_PATH) && \
			make && \
			make install && \
		cd .. && \
		rm -rf SDL2_mixer-$(SDL_MIXER_VER);\
	else \
		echo "\033$(GREEN)m✓\tSDl2_mixer-$(SDL_MIXER_VER) already installed\033[0m"; \
	fi

CHECK_LIB_DIR:
	@if [ ! -d "./lib" ]; then \
		mkdir lib;\
	fi

print_name:
	@echo "\033[033m➼\t\033[033mCompiling $(NAME) ...\033[0m"

print_end:
	@echo $(MESSAGE)
.PHONY: all clean fclean re rm_obj exe SDL2 rm_SDL2 re_SDL2 GLAD ASSIMP\
		 re_sanitize sanitize CHECK_LIB_DIR
