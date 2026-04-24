CC = gcc
CFLAGS = -I/usr/include/SDL2 -D_GNU_SOURCE=1 -D_REENTRANT -I.
LIBS = -L/usr/lib -lSDL2

all:
	$(CC) pong.c Cloudy/Render/simple_window.c Cloudy/Render/drawing.c Cloudy/Input/input_man.c Cloudy/Entity/entity.c Cloudy/Physics/physics.c Cloudy/Ext/misc.c -o PongGameDemo $(CFLAGS) $(LIBS)
