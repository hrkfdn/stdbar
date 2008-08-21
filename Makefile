# stdbar makefile
# ©2008 - Henrik 'hrkfrd' Friedrichsen 
#

VERSION = 	0.1

OUT = 		stdbar
OBJ = 		main.o atoms.o events.o draw.o
CC ?= 		cc

INC =		`pkg-config --cflags x11` -g
LIB =		`pkg-config --libs x11` -g

CFLAGS = 	-O2

all: $(OUT)

.c.o:
	@echo [CC] $<
	@$(CC) -c $(CFLAGS) -DVERSION=\"$(VERSION)\" $(INC) $<

$(OUT): $(OBJ)
	@echo [LD] $@
	@$(CC) $(LDFLAGS) $(OBJ) $(LIB) -o $(OUT)

clean:
	rm -rf $(OBJ) $(OUT)
