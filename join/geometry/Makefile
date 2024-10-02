#Flags: 
CC=g++
ALL = Element.o FaceContainer.o PointM3d.o Prism.o Tetrahedra.o Hexahedra.o Pyramid.o


all: *.cpp *.h
	make $(ALL)

Point.o: Point.cpp Point.h
	$(CC) -g -c Point.cpp

PointM3d.o: PointM3d.h PointM3d.cpp Point.o
	$(CC) -g -c PointM3d.cpp

Element.o: Element.cpp Element.h
	$(CC) -g -c Element.cpp

Hexahedra.o: Hexahedra.cpp Hexahedra.h Element.o
	$(CC) -g -c Hexahedra.cpp

Tetrahedra.o: Tetrahedra.cpp Tetrahedra.h Element.o
	$(CC) -g -c Tetrahedra.cpp

Pyramid.o: Pyramid.cpp Pyramid.h Element.o
	$(CC) -g -c Pyramid.cpp

Prism.o: Prism.cpp Prism.h Element.o
	$(CC) -g -c Prism.cpp

Face.o: Face.cpp Face.h
	$(CC) -g -c Face.cpp

FaceContainer.o: FaceContainer.cpp FaceContainer.h Face.o
	$(CC) -g -c FaceContainer.cpp

clean:
	rm *.o
