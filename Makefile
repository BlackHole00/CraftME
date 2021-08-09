# Project: 	CraftME
# Author:	Vicix
# Makefile originally created by Dev-C++ 4.9.9.2

CPP  	= g++.exe
CC   	= gcc.exe
WINDRES = windres.exe
RES  	=
OBJ  	= main.o Window/window.o gfx/gl_call.o gfx/buffer.o utils/vector.o utils/option.o utils/mem.o utils/panic.o utils/dummy_func.o gfx/layout.o gfx/camera.o utils/math.o gfx/renderer.o gfx/mesh.o game/chunk.o game/block.o game/world.o $(RES)
LINKOBJ = main.o Window/window.o gfx/gl_call.o gfx/buffer.o utils/vector.o utils/option.o utils/mem.o utils/panic.o utils/dummy_func.o gfx/layout.o gfx/camera.o utils/math.o gfx/renderer.o gfx/mesh.o game/chunk.o game/block.o game/world.o $(RES)
LIBS 	= -L"C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/lib" -mwindows -lopengl32 -lglu32
INCS 	= -I"C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/include"
BIN  	= CraftME.exe
CFLAGS 	= $(INCS) -std=c99 -O3
RM 		= rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before CraftME.exe all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o "CraftME.exe" $(LIBS)

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

Window/window.o: Window/window.c
	$(CC) -c Window/window.c -o Window/window.o $(CFLAGS)

gfx/gl_call.o: gfx/gl_call.c
	$(CC) -c gfx/gl_call.c -o gfx/gl_call.o $(CFLAGS)

gfx/buffer.o: gfx/buffer.c
	$(CC) -c gfx/buffer.c -o gfx/buffer.o $(CFLAGS)

utils/vector.o: utils/vector.c
	$(CC) -c utils/vector.c -o utils/vector.o $(CFLAGS)

utils/option.o: utils/option.c
	$(CC) -c utils/option.c -o utils/option.o $(CFLAGS)

utils/mem.o: utils/mem.c
	$(CC) -c utils/mem.c -o utils/mem.o $(CFLAGS)

utils/panic.o: utils/panic.c
	$(CC) -c utils/panic.c -o utils/panic.o $(CFLAGS)

utils/dummy_func.o: utils/dummy_func.c
	$(CC) -c utils/dummy_func.c -o utils/dummy_func.o $(CFLAGS)

gfx/layout.o: gfx/layout.c
	$(CC) -c gfx/layout.c -o gfx/layout.o $(CFLAGS)

gfx/camera.o: gfx/camera.c
	$(CC) -c gfx/camera.c -o gfx/camera.o $(CFLAGS)

utils/math.o: utils/math.c
	$(CC) -c utils/math.c -o utils/math.o $(CFLAGS)

gfx/renderer.o: gfx/renderer.c
	$(CC) -c gfx/renderer.c -o gfx/renderer.o $(CFLAGS)

gfx/mesh.o: gfx/mesh.c
	$(CC) -c gfx/mesh.c -o gfx/mesh.o $(CFLAGS)

game/chunk.o: game/chunk.c
	$(CC) -c game/chunk.c -o game/chunk.o $(CFLAGS)

game/block.o: game/block.c
	$(CC) -c game/block.c -o game/block.o $(CFLAGS)

game/world.o: game/world.c
	$(CC) -c game/world.c -o game/world.o $(CFLAGS)
