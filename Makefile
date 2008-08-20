# stdbar makefile
# ©2008 - Henrik 'hrkfrd' Friedrichsen 
#

OUT = 		stdbar
OBJ = 		main.o atoms.o events.o
CC ?= 		cc

INC =		`pkg-config --cflags x11`
LIB =		`pkg-config --libs x11`

CFLAGS = 	-O2

all: $(OUT)

.c.o:
	@echo [CC] $<
	@$(CC) -c $(CFLAGS) $(INC) $<

$(OUT): $(OBJ)
	@echo [LD] $@
	@$(CC) $(LDFLAGS) $(OBJ) $(LIB) -o $(OUT)

clean:
	rm -rf $(OBJ) $(OUT)
