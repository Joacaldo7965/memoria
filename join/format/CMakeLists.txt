# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx".  The extensions are automatically found.


add_executable (off2vtk_normal

../geometry/Point.o ../geometry/Face.o ../geometry/FaceContainer.o

../read_write/ReadOff.o

OffToVTK_normals
)

add_executable (m3d2dolfinXML

../geometry/Point.o ../geometry/PointM3d.o ../geometry/Element.o 
../geometry/Hexahedra.o ../geometry/Prism.o ../geometry/Pyramid.o 
../geometry/Tetrahedra.o

../read_write/ReadM3d.o ../read_write/WriteDolfinXML.o

M3dToDolfinXML
)

add_executable (inp2m3d

../geometry/Point.o ../geometry/PointM3d.o ../geometry/Element.o 
../geometry/Hexahedra.o ../geometry/Prism.o ../geometry/Pyramid.o 
../geometry/Tetrahedra.o

../read_write/WriteM3d.o ../read_write/M3dPrinter.o
../read_write/ReadInp.o

InpToM3d
)

add_executable (ansys2quadAnsys

../geometry/Point.o ../geometry/Element.o ../geometry/Hexahedra.o 
../geometry/Prism.o ../geometry/Pyramid.o ../geometry/Tetrahedra.o
../geometry/Face.o ../geometry/FaceContainer.o

../read_write/ReadAnsys.o ../read_write/AnsysFormat.o

AnsysQuadEdge AnsysToQuadAnsys
)

add_executable (ansys2mixAnsys

../geometry/Point.o ../geometry/Element.o ../geometry/Hexahedra.o 
../geometry/Prism.o ../geometry/Pyramid.o ../geometry/Tetrahedra.o
../geometry/Face.o ../geometry/FaceContainer.o

../read_write/ReadAnsys.o ../read_write/AnsysFormat.o

AnsysToMixAnsys
)

add_executable (mdl2dolfinXML

../geometry/Point.o ../geometry/Face.o ../geometry/FaceContainer.o

../read_write/ReadMdl.o ../read_write/WriteDolfinTriangleXML.o

MdlToDolfinXML
)

add_executable (mdl2mdltri

../geometry/Point.o ../geometry/Face.o ../geometry/FaceContainer.o

../read_write/WriteMdl.o ../read_write/ReadMdl.o

MdlToMdlTriangle
)

add_executable (pascal2mdl

../geometry/Point.o ../geometry/Face.o ../geometry/FaceContainer.o

../read_write/WriteMdl.o ../read_write/ReadPascal.o

PascalToMdl
)

add_executable (mdl2matlab

../geometry/Point.o ../geometry/Face.o ../geometry/FaceContainer.o

../read_write/WriteMatlab.o ../read_write/ReadMdl.o

MdlToMatlab
)

add_executable (matlab2mdl

../geometry/Point.o ../geometry/Face.o ../geometry/FaceContainer.o

../read_write/ReadMatlab.o ../read_write/WriteMdl.o

MatlabToMdl
)

add_executable (mesh2ansys

../geometry/Point.o ../geometry/Element.o ../geometry/Hexahedra.o 
../geometry/Prism.o ../geometry/Pyramid.o ../geometry/Tetrahedra.o
../geometry/Face.o ../geometry/FaceContainer.o

../read_write/ReadMeshVolume.o ../read_write/WriteAnsys.o
../read_write/AnsysFormat.o

MeshToAnsys
)
add_executable (ansys2mesh 
../geometry/Point.o ../geometry/Element.o ../geometry/Hexahedra.o 
../geometry/Prism.o ../geometry/Pyramid.o ../geometry/Tetrahedra.o
../geometry/Face.o ../geometry/FaceContainer.o

../read_write/WriteMeshVolume.o ../read_write/ReadAnsys.o
../read_write/AnsysFormat.o

AnsysToMesh
)

add_executable (mesh2m3d

../geometry/Point.o ../geometry/PointM3d.o ../geometry/Element.o 
../geometry/Hexahedra.o ../geometry/Prism.o ../geometry/Pyramid.o 
../geometry/Tetrahedra.o

../read_write/WriteM3d.o ../read_write/M3dPrinter.o
../read_write/ReadMeshVolume.o

MeshToM3d
)

add_executable (joinoff

../geometry/Point.o ../geometry/Face.o ../geometry/FaceContainer.o 
../read_write/ReadOff.o ../read_write/WriteOff.o

JoinOff
)

add_executable (joinmdl

../geometry/Point.o ../geometry/Face.o ../geometry/FaceContainer.o 
../read_write/ReadMdl.o ../read_write/WriteMdl.o

JoinMdl
)

add_executable (m3d2mdlcloud

../geometry/Point.o ../geometry/PointM3d.o ../geometry/Element.o 
../geometry/Hexahedra.o ../geometry/Prism.o ../geometry/Pyramid.o 
../geometry/Tetrahedra.o ../geometry/Face.o ../geometry/FaceContainer.o 

../read_write/ReadM3d.o ../read_write/WriteMdl.o

M3dToMdlCloud
)

add_executable (smesh2m3d

../geometry/Point.o ../geometry/PointM3d.o ../geometry/Element.o 
../geometry/Hexahedra.o ../geometry/Prism.o ../geometry/Pyramid.o 
../geometry/Tetrahedra.o

../read_write/WriteM3d.o ../read_write/M3dPrinter.o
../read_write/ReadSmesh.o

SmeshToM3d
)

add_executable (smesh2ansys

../geometry/Point.o ../geometry/Element.o 
../geometry/Hexahedra.o ../geometry/Prism.o ../geometry/Pyramid.o 
../geometry/Tetrahedra.o

../read_write/WriteAnsys.o ../read_write/AnsysFormat.o
../read_write/ReadSmesh.o

SmeshToAnsys
)


add_executable (m3d2ansys

../geometry/Point.o ../geometry/PointM3d.o ../geometry/Element.o 
../geometry/Hexahedra.o ../geometry/Prism.o ../geometry/Pyramid.o 
../geometry/Tetrahedra.o

../read_write/ReadM3d.o ../read_write/WriteAnsys.o 
../read_write/AnsysFormat.o

M3dToAnsys
)

add_executable (ansys2m3d

../geometry/Point.o ../geometry/PointM3d.o ../geometry/Element.o 
../geometry/Hexahedra.o ../geometry/Prism.o ../geometry/Pyramid.o 
../geometry/Tetrahedra.o

../read_write/WriteM3d.o ../read_write/M3dPrinter.o
../read_write/ReadAnsys.o ../read_write/AnsysFormat.o

AnsysToM3d
)

add_executable (mesh2mdl

../geometry/Point.o ../geometry/Face.o ../geometry/FaceContainer.o 

../read_write/ReadMeshSurface.o ../read_write/WriteMdl.o

MeshToMdl
)

add_executable (off2mdl

../geometry/Point.o ../geometry/Face.o ../geometry/FaceContainer.o 

../read_write/ReadOff.o ../read_write/WriteMdl.o

OffToMdl
)

add_executable (off2off

../geometry/Point.o ../geometry/Face.o ../geometry/FaceContainer.o 

../read_write/ReadOff.o ../read_write/WriteOff.o

OffToOff_nc
)

add_executable (mdl2off

../geometry/Point.o ../geometry/Face.o ../geometry/FaceContainer.o 

../read_write/ReadMdl.o ../read_write/WriteOff.o

MdlToOff
)

add_executable (mdl2smesh

../geometry/Point.o ../geometry/Face.o ../geometry/FaceContainer.o 

../read_write/ReadMdl.o ../read_write/WriteSmesh.o

MdlToSmesh
)

