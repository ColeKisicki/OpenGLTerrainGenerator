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
TerrainGenerator.o: TerrainGenerator.cpp CSCIx229.hpp Light.hpp Camera.hpp Cube.hpp Plane.hpp Terrain.hpp glm/glm.hpp basic_structures.hpp MarchingCubeTable.cpp
DisplayObject.o: DisplayObject.cpp Material.hpp CSCIx229.hpp glm/glm.hpp
Cube.o: Cube.cpp DisplayObject.hpp CSCIx229.hpp glm/glm.hpp
Camera.o: Camera.cpp CSCIx229.hpp glm/glm.hpp
Plane.o: Plane.cpp DisplayObject.hpp CSCIx229.hpp glm/glm.hpp
Scene.o: Scene.cpp DisplayObject.hpp CSCIx229.hpp glm/glm.hpp
Light.o: Light.cpp Light.hpp CSCIx229.hpp glm/glm.hpp
fatal.o: fatal.cpp CSCIx229.hpp glm/glm.hpp
errcheck.o: errcheck.cpp CSCIx229.hpp glm/glm.hpp
print.o: print.cpp CSCIx229.hpp glm/glm.hpp
loadtexbmp.o: loadtexbmp.cpp CSCIx229.hpp glm/glm.hpp
loadobj.o: loadobj.cpp CSCIx229.hpp glm/glm.hpp
projection.o: projection.cpp CSCIx229.hpp glm/glm.hpp
Terrain.o: Terrain.cpp CSCIx229.hpp glm/glm.hpp basic_structures.hpp MarchingCubeTable.cpp

#  Create archive
CSCIx229.a:fatal.o errcheck.o print.o loadtexbmp.o loadobj.o projection.o Light.o DisplayObject.o Cube.o Camera.o Plane.o Scene.o Terrain.o
	ar -rcs $@ $^


# Compile rules
.c.o:
	gcc -c $(CFLG)  $<
.cpp.o:
	g++ -c $(CFLG)  $<

#  Link
TerrainGenerator:TerrainGenerator.o CSCIx229.a
	g++ $(CFLG) -o $@ $^  $(LIBS)

#  Clean
clean:
	$(CLEAN)
