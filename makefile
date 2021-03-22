
SDL = -ldl `sdl2-config --libs`
LDFLAGS = $(SDL) -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lSDL2_mixer


PepiteDeFight: obj/main.o obj/actions.o obj/draw.o obj/init.o obj/input.o obj/sockets.o obj/sounds.o obj/timer.o
	gcc obj/main.o obj/actions.o obj/draw.o obj/init.o obj/input.o obj/sockets.o obj/sounds.o obj/timer.o $(LDFLAGS) -o PepiteDeFight


obj/main.o: src/main.c include/struct.h include/defs.h
	gcc -o obj/main.o -Wall src/main.c -c `sdl2-config --cflags`

obj/actions.o: src/actions.c include/actions.h include/struct.h include/defs.h
	gcc -o obj/actions.o -Wall src/actions.c -c `sdl2-config --cflags`

obj/draw.o: src/draw.c include/draw.h include/struct.h include/defs.h
	gcc -o obj/draw.o -Wall src/draw.c -c `sdl2-config --cflags`

obj/init.o: src/init.c include/init.h include/struct.h include/defs.h
	gcc -o obj/init.o -Wall src/init.c -c `sdl2-config --cflags`

obj/input.o: src/input.c include/input.h include/struct.h include/defs.h
	gcc -o obj/input.o -Wall src/input.c -c `sdl2-config --cflags`

obj/sockets.o: src/sockets.c include/sockets.h include/struct.h include/defs.h
	gcc -o obj/sockets.o -Wall src/sockets.c -c `sdl2-config --cflags`

obj/sounds.o: src/sounds.c include/sounds.h include/struct.h include/defs.h
	gcc -o obj/sounds.o -Wall src/sounds.c -c `sdl2-config --cflags`

obj/timer.o: src/timer.c include/timer.h include/struct.h include/defs.h
	gcc -o obj/timer.o -Wall src/timer.c -c `sdl2-config --cflags`


clean:
	-rm obj/*.o
	-rm PepiteDeFight
	@echo "Cleanup complete!"
