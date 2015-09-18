SRC	=main.cpp \
	 core.cpp \
	 mesh.cpp \
	 material.cpp \
	 controller.cpp \
	 uniform.cpp \
	 AssimpProgressHandlerOverload.cpp \
	 GPUBuffer.cpp \
	 camera.cpp \
	 texture.cpp \
	 renderTexture.cpp

EXT     =cpp
NAME	=demo
DEFINE 	=-D THREAD_SHOW
DEBUG 	= -g -fsanitize=memory
OPTIM= -march=native -O2
GLM_DEFINE=-DGLM_SWIZZLE -DGLM_FORCE_AVX
CXXFLAGS= -Wall -Wextra -W -std=c++0x -I./ -I./include $(GLM_DEFINE) $(OPTIM) $(DEFINE) $(DEBUG)
LIBDEVIL= ./libs/libILUT.a ./libs/libILU.a ./libs/libIL.a -ljpeg -lpng16 -ltiff -lGLU
LIBASSIMPANDDEPS= ./libs/libassimp.a ./libs/libminizip.a ./libs/libz.a
DISPLAYLIBS=./libs/libGLEW.a ./libs/libglfw.a -lXrandr -lXi -lGL -lpthread -lX11 -lXxf86vm
LDFLAGS	= $(LIBDEVIL) $(LIBASSIMPANDDEPS) $(DISPLAYLIBS) $(OPTIM)
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

