CC = gcc
CFLAGS = -I/usr/include/SDL2 -D_GNU_SOURCE=1 -D_REENTRANT -I.
LIBS = -L/usr/lib -lSDL2

all:
	$(CC) pong.c Cloudy/Entity/entity.c Cloudy/Events/events.c Cloudy/Ext/misc.c Cloudy/Input/input_man.c Cloudy/Physics/physics.c Cloudy/Render/drawing.c Cloudy/Render/simple_window.c -o PongGameDemo $(CFLAGS) $(LIBS)
