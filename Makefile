SRC	=main.cpp \
	 core.cpp \
	 mesh.cpp \
	 material.cpp \
	 controller.cpp \
	 uniform.cpp \
	 GPUBuffer.cpp \
	 camera.cpp \
	 texture.cpp \
	 renderTexture.cpp \
	 depthTexture.cpp

EXT     =cpp
NAME	=demo
CXXFLAGS= -Wall -Wextra -W -std=c++0x -I./ -I./include
LIBDEVIL= ./libs/libILUT.a ./libs/libILU.a ./libs/libIL.a -ljpeg -lpng16 -ltiff -lIlmImf
#LIBDEVIL= -lIL -lILU -lILUT
LIBASSIMPANDDEPS= ./libs/libassimp.a ./libs/libminizip.a ./libs/libz.a
DISPLAYLIBS=./libs/libGLEW.a ./libs/libglfw.a -lXrandr -lXi -lGL -lpthread -lX11 -lXxf86vm
LDFLAGS	= $(LIBDEVIL) $(LIBASSIMPANDDEPS) $(DISPLAYLIBS)
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

