# Homework 5
EXE=TerrainGenerator
CXX=g++-17
# Main target
all: $(EXE)

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -f *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
RES=$(shell uname -r|sed -E 's/(.).*/\1/'|tr 12 21)
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=$(RES)
LIBS=-framework GLUT -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Dependencies
TerrainGenerator.o: TerrainGenerator.cpp CSCIx229.hpp Light.hpp Vector3.hpp Camera.hpp Cube.hpp Plane.hpp Terrain.hpp
DisplayObject.o: DisplayObject.cpp Vector3.hpp Material.hpp CSCIx229.hpp
Cube.o: Cube.cpp DisplayObject.hpp CSCIx229.hpp
Camera.o: Camera.cpp Vector3.hpp CSCIx229.hpp
Plane.o: Plane.cpp DisplayObject.hpp CSCIx229.hpp
Scene.o: Scene.cpp DisplayObject.hpp CSCIx229.hpp
Light.o: Light.cpp Light.hpp Vector3.hpp CSCIx229.hpp
fatal.o: fatal.cpp CSCIx229.hpp
errcheck.o: errcheck.cpp CSCIx229.hpp
print.o: print.cpp CSCIx229.hpp
loadtexbmp.o: loadtexbmp.cpp CSCIx229.hpp
loadobj.o: loadobj.cpp CSCIx229.hpp
projection.o: projection.cpp CSCIx229.hpp
Terrain.o: Terrain.cpp CSCIx229.hpp

#  Create archive
CSCIx229.a:fatal.o errcheck.o print.o loadtexbmp.o loadobj.o projection.o Light.o DisplayObject.o Cube.o Camera.o Plane.o Scene.o Terrain.o
	ar -rcs $@ $^


# Compile rules
.c.o:
	gcc -c $(CFLG)  $<
.cpp.o:
	g++ -c $(CFLG)  $<

#  Link
TerrainGenerator:TerrainGenerator.o   CSCIx229.a
	g++ $(CFLG) -o $@ $^  $(LIBS)

#  Clean
clean:
	$(CLEAN)
