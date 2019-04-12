CXX = g++
#LDFLAGS = -fsanitize=address

SRC = graph.h main.cpp
OBJ = $(SRC:.cc=.o)
EXEC = main.out

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(EXEC)