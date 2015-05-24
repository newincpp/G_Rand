SRC	=main.cpp \
	 core.cpp \
	 mesh.cpp \
	 material.cpp \
	 controller.cpp \
	 uniform.cpp \
	 GPUBuffer.cpp \
	 camera.cpp

EXT     =cpp
NAME	=demo
CXXFLAGS= -Wall -Wextra -W -std=c++0x -I./ -I./include
LDFLAGS	= ./libs/libassimp.a ./libs/libminizip.a ./libs/libz.a ./libs/libGLEW.a ./libs/libglfw.a   -lXrandr -lXi -lGL -lpthread -lX11 -lXxf86vm 
OBJS	= $(SRC:.$(EXT)=.o)
RM	= rm -f
CXX	= clang++
LINKER	= $(CXX)

all: $(NAME)

$(NAME): $(OBJS)
	$(LINKER) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS) *.swp *~ *#

fclean: clean
	$(RM) $(NAME)

re: make -B -j4

.PHONY: all clean fclean re

