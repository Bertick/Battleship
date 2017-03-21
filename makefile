CXX = g++
CXXFLAGS = -g
LDFLAGS = -lm -lncurses
OBJECTS = main.o Functions.o Game.o Player.o Ship.o Grid.o Point.o

main : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o main.out $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

.PHONY : clean
clean :
	rm -f $(objects) *.o
