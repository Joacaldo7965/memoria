#Flags: 
CC=g++
ALL = AnsysFormat.o ReadInp.o ReadM3d.o ReadMeshVolume.o M3dPrinter.o WriteM3d.o ReadMdl.o ReadSmesh.o WriteMdl.o ReadAnsys.o ReadMeshSurface.o WriteAnsys.o WriteSmesh.o ReadOff.o WriteMeshVolume.o WriteOff.o ReadMatlab.o WriteMatlab.o ReadPascal.o WriteDolfinXML.o WriteDolfinTriangleXML.o
OBJS_G_E = ../geometry/Element.o ../geometry/Hexahedra.o ../geometry/Prism.o ../geometry/Pyramid.o ../geometry/Tetrahedra.o
OBJS_G_P = ../geometry/Point.o ../geometry/PointM3d.o
OBJS_G_F = ../geometry/FaceContainer.o ../geometry/Face.o

all: *.cpp *.h
	make $(ALL)

WriteDolfinTriangleXML.o: WriteDolfinTriangleXML.h WriteDolfinTriangleXML.cpp
	$(CC) -g -c WriteDolfinTriangleXML.cpp

WriteDolfinXML.o: WriteDolfinXML.h WriteDolfinXML.cpp
	$(CC) -g -c WriteDolfinXML.cpp

ReadPascal.o: ReadPascal.h ReadPascal.cpp
	$(CC) -g -c ReadPascal.cpp

ReadInp.o: ReadInp.h ReadInp.cpp
	$(CC) -g -c ReadInp.cpp

ReadMatlab.o: ReadMatlab.h ReadMatlab.cpp
	$(CC) -g -c ReadMatlab.cpp

WriteMatlab.o: WriteMatlab.h WriteMatlab.cpp
	$(CC) -g -c WriteMatlab.cpp

AnsysFormat.o: AnsysFormat.h AnsysFormat.cpp FileFormat.h
	$(CC) -g -c AnsysFormat.cpp

M3dPrinter.o: M3dPrinter.h M3dPrinter.cpp
	$(CC) -g -c M3dPrinter.cpp 

ReadM3d.o: ReadM3d.h ReadM3d.cpp
	$(CC) -g -c ReadM3d.cpp 

ReadMeshVolume.o: ReadMeshVolume.h ReadMeshVolume.cpp
	$(CC) -g -c ReadMeshVolume.cpp 

WriteMeshVolume.o: WriteMeshVolume.h WriteMeshVolume.cpp
	$(CC) -g -c WriteMeshVolume.cpp

WriteM3d.o: WriteM3d.h WriteM3d.cpp M3dPrinter.o
	$(CC) -g -c WriteM3d.cpp 

ReadMdl.o: ReadMdl.cpp ReadMdl.h
	$(CC) -g -c ReadMdl.cpp 

ReadSmesh.o: ReadSmesh.h ReadSmesh.cpp
	$(CC) -g -c ReadSmesh.cpp 

WriteMdl.o: WriteMdl.h WriteMdl.cpp
	$(CC) -g -c WriteMdl.cpp 

ReadOff.o: ReadOff.cpp ReadOff.h
	$(CC) -g -c ReadOff.cpp

WriteOff.o: WriteOff.h WriteOff.cpp
	$(CC) -g -c WriteOff.cpp 

ReadAnsys.o: ReadAnsys.h ReadAnsys.cpp AnsysFormat.o
	$(CC) -g -c ReadAnsys.cpp 

ReadMeshSurface.o: ReadMeshSurface.h ReadMeshSurface.cpp
	$(CC) -g -c ReadMeshSurface.cpp 

WriteAnsys.o: WriteAnsys.h WriteAnsys.cpp AnsysFormat.o
	$(CC) -g -c WriteAnsys.cpp 

WriteSmesh.o: WriteSmesh.h WriteSmesh.cpp
	$(CC) -g -c WriteSmesh.cpp 

clean:
	rm *.o
