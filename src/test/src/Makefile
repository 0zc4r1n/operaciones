SRC = test.c
OBJ = $(SRC:.c=.o)
OUT = test
INCLUDES = -I.

.SUFFIXES: .c

default: $(OUT)

.c.o:
	gcc $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	gcc -o $(OUT) $(OBJ) $(LDFLAGS) $(LIBS)
