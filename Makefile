SRC	=main.cpp \
	 engine.cpp
EXT     =cpp
NAME	=demo
CXXFLAGS= -Wall -Wextra -W -std=c++0x -I./ `pkg-config --cflags glfw3`
LDFLAGS	=`pkg-config --static --libs glfw3` 
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

