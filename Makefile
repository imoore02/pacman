
#To compile: 'make'
#To destory object files: 'make clean'
#To recompile: 'make re'

CC = g++

#This top CFLAGS is for my computer cos i installed SFML the lazy way - so when u use the makefile just comment out this CFLAGS and uncomment yours xx
CFLAGS = -std=c++11 -Wall -Wextra -g -I/opt/homebrew/Cellar/sfml/2.5.1_2/include/

LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib/ -lsfml-graphics -lsfml-window -lsfml-system

#Shrada's CFLAGS:
#CFLAGS = -Wall -Wextra -Werror -g -lsfml-graphics -lsfml-window -lsfml-system

TARGET = pacwoman
SRCS = main.cpp Maze.cpp Pacman.cpp Game.cpp Ghosts.cpp Irene.cpp P.cpp B.cpp C.cpp UnitTest.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)
	@ echo "\033[0;35mWOMPAC MANWO PACWOMAN!\033[0m"
	@ echo "\033[1;35mType './pacwoman' to play...\033[0m"

$(TARGET): $(OBJS)
	@ $(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	@ $(CC) $(CFLAGS) -c $< -o $@

main.pch: main.h
	@ $(CC) $(CFLAGS) -c $< -o $@

$(OBJS): main.pch

clean:
	@ rm -f $(OBJS) $(TARGET) main.pch
	@ echo 'cleaning...'
	@ echo 'clean!'

re: clean $(TARGET)
	@ echo 'recompiling...'  
