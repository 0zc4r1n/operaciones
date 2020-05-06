SRC = \
operaciones.c

OBJ = $(SRC:.c=.o)
OUT = liboperaciones.a
INCLUDES = -I.
DEFINES =

.SUFFIXES: .c

default: $(OUT)

.c.o:
	gcc $(INCLUDES) $(DEFINES) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ)
