#
# Gerson Carvalho
# GravitySand v0.01b
#

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -g
STDRULE = -std=c++11
NAME = gravsim
DEBUG = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=./valgrind.supp -s

SRC =	./includes/imgui/imgui_demo.cpp		\
		./includes/imgui/imgui_tables.cpp	\
		./includes/imgui/rlImGui.cpp		\
		./includes/imgui/imgui.cpp			\
		./includes/imgui/imgui_draw.cpp		\
		./includes/imgui/imgui_widgets.cpp	\
		./srcs/input.cpp					\
		./srcs/menu.cpp						\
		./srcs/main.cpp

INCS = -I./classes/							\
	   -L./classes/							\
	   -I./includes							\
	   -L./includes/						\
	   -I./includes/imgui/					\
	   -L./includes/imgui/					\
	   -I./includes/imgui/extras/			\
	   -L./includes/imgui/extras/			\
	   ./includes/raylib/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11

INCLUDES = ./includes/Game.hpp											\
		   ./includes/imgui/imgui.h							\
		   ./includes/imgui/rlImGui.h							\
		   ./includes/imgui/imconfig.h							\
		   ./includes/imgui/rlImGuiColors.h					\
		   ./includes/imgui/imgui_internal.h					\
		   ./includes/imgui/imstb_rectpack.h					\
		   ./includes/imgui/imstb_textedit.h					\
		   ./includes/imgui/imstb_truetype.h					\
		   ./includes/imgui/imgui_impl_raylib.h				\
		   ./includes/imgui/extras/IconsFontAwesome6.h			\
		   ./includes/imgui/extras/FA6FreeSolidFontData.h		\
		   ./includes/raylib/rlgl.h										\
		   ./includes/raylib/raylib.h									\
		   ./includes/raylib/raymath.h

OBJS = $(SRC:.cpp=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(STDRULE) $(OBJS) -o $(NAME) $(INCS)

%.o: %.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) $(STDRULE) -c $< -o $@ $(INCS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: all
	./$(NAME)

debug:
	$(DEBUG) ./$(NAME)

.PHONY: all clean fclean re run debug
