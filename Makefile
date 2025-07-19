#
# Gerson Carvalho
# GravitySand v0.11b
#

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -g -fopenmp
STDRULE = -std=c++11
NAME = gravsim
DEBUG = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=./valgrind.supp -s

SRC =	./includes/imgui/imgui_demo.cpp		\
		./includes/imgui/imgui_tables.cpp	\
		./includes/imgui/rlImGui.cpp		\
		./includes/imgui/imgui.cpp			\
		./includes/imgui/imgui_draw.cpp		\
		./includes/imgui/imgui_widgets.cpp	\
		./classes/Particle.cpp				\
		./classes/QuadTree.cpp				\
		./classes/Gravity.cpp				\
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

INCLUDES = ./includes/Game.hpp		\
		   ./classes/Particle.hpp	\
		   ./classes/Gravity.hpp	\
		   ./classes/QuadTree.hpp

OBJS = $(SRC:.cpp=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(STDRULE) $(OBJS) -o $(NAME) $(INCS)

%.o: %.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

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
