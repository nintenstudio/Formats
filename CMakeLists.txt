# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Formats CXX)
add_library(Formats STATIC "Public/Formats/Resources/Resource.h" "Public/Formats/Resources/BYML/BYML.h" "Private/Formats/Resources/BYML/BYML.cpp" "Public/Formats/Resources/AAMP/AAMP.h" "Private/Formats/Resources/AAMP/AAMP.cpp" "Public/Formats/Resources/BFRES/BFRES.h" "Private/Formats/Resources/BFRES/BFRES.cpp" "Public/Formats/Resources/BFRES/Versions/V0.10.0.0/0.10.0.0.h" "Private/Formats/Resources/BFRES/Versions/V0.10.0.0/0.10.0.0.cpp" "Public/Formats/Resources/BYML/Versions/V7/V7.h" "Private/Formats/Resources/BYML/Versions/V7/V7.cpp" "Public/Formats/IO/BinaryIOStream.h" "Public/Formats/IO/Endianness.h" "Public/Formats/Aliases/Primitives.h" "Public/Formats/IO/BinaryIOStream_Versions/Little.h" "Public/Formats/IO/BinaryIOStream_Versions/Big.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/String.h" "Public/Formats/Resources/BYML/Versions/V7/Node.h" "Private/Formats/Resources/BYML/Versions/V7/Nodes/String.cpp" "Public/Formats/Resources/BYML/Versions/V7/Nodes/BinaryData.h" "Public/Formats/Resources/BYML/Nodes/BinaryData.h" "Public/Formats/Resources/BYML/Nodes/Array.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/Array.h" "Public/Formats/Resources/BYML/Nodes/StringHash.h" "Public/Formats/Resources/BYML/Nodes/Float.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/Float.h" "Public/Formats/Resources/BYML/Nodes/UInt.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/UInt.h" "Public/Formats/Resources/BYML/Nodes/Int64.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/Int64.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/UInt64.h" "Public/Formats/Resources/BYML/Nodes/Double.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/Double.h" "Public/Formats/Resources/BYML/Nodes/Null.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/Null.h" "Private/Formats/Resources/BYML/Versions/V7/Nodes/StringTable.cpp" "Public/Formats/Resources/BYML/Versions/V7/NodeType.h" "Public/Formats/Primitives/Int24.h" "Public/Formats/Primitives/UInt24.h" "Private/Formats/Resources/BYML/Versions/V7/Nodes/Array.cpp" "Private/Formats/Resources/Resource.cpp" "Public/Formats/Resources/BYML/Versions/V7/Nodes/PlainHash.h" "Public/Formats/Resources/BYML/Nodes/PlainHash.h" "Public/Formats/Resources/BYML/Nodes/ValueHash.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/ValueHash.h" "Public/Formats/Resources/BYML/Nodes/FileData.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/FileData.h" "Private/Formats/Resources/BYML/Versions/V7/Nodes/ValueHash.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/PlainHash.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/StringHash.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/BinaryData.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/Bool.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/FileData.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/Double.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/Float.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/UInt.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/Int64.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/Null.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/Int.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/UInt64.cpp")

include (TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
	target_compile_definitions(Formats PUBLIC FORMATS_BIGENDIAN=true)
else()
	target_compile_definitions(Formats PUBLIC FORMATS_BIGENDIAN=false)
endif()

target_include_directories(Formats PRIVATE Private Public)