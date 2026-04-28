CC = gcc
CFLAGS = -I/usr/include/SDL2 -D_GNU_SOURCE=1 -D_REENTRANT -I.
LIBS = -L/usr/lib -lSDL2 -lSDL2_ttf

OBJS = pong.o Cloudy/Entity/entity.o Cloudy/Events/events.o \
       Cloudy/Ext/misc.o Cloudy/Input/input_man.o \
       Cloudy/Physics/physics.o Cloudy/Render/drawing.o \
       Cloudy/Render/simple_window.o Cloudy/UI/ui.o

all: $(OBJS)
	$(CC) $(OBJS) -o PongGameDemo $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) PongGameDemo
