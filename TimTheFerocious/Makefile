CXX = g++

# Warnings frequently signal eventual errors:
CXXFLAGS=`sdl2-config --cflags` -g -W -Wall -std=c++11 -Weffc++ -Wextra -pedantic -mwindows -O0 -I `sdl2-config --prefix`/include/

LDFLAGS = `sdl2-config --libs` -lm -lexpat -lSDL2_ttf -lSDL2_image -lSDL2_mixer -mwindows

OBJS = \
  renderContext.o \
	ioMod.o \
	parseXML.o \
	gamedata.o \
	viewport.o \
	world.o \
	triple.o \
	light.o \
	lights.o \
	spriteSheet.o \
	image.o \
	imageFactory.o \
	sound.o \
	sprite.o \
	twoWaySprite.o \
	multisprite.o \
	twoWayMultiSprite.o \
	shooterSprite.o \
	player.o \
	smartSprite.o \
	goalSprite.o \
	explodingSprite.o \
	chunk.o \
	bullet.o \
	bullets.o \
	hud.o \
	collisionStrategy.o \
	vector2f.o \
	clock.o \
	menu.o \
	menuEngine.o \
	engine.o \
	WinMain.o
EXEC = run

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
	rm -rf frames/*.bmp
