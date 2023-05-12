# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project(Formats CXX)
add_library(Formats STATIC "Public/Formats/Resource.h" "Public/Formats/Resources/BYML.h" "Private/Formats/Resources/BYML.cpp" "Public/Formats/Resources/AAMP.h" "Private/Formats/Resources/AAMP.cpp" "Public/Formats/Resources/BFRES.h" "Private/Formats/Resources/BFRES.cpp" "Public/Formats/Resources/BFRES_Versions/0.10.0.0.h" "Private/Formats/Resources/BFRES_Versions/0.10.0.0.cpp" "Public/Formats/Resources/BYML_Versions/7.h" "Private/Formats/Resources/BYML_Versions/7.cpp" "Public/Formats/IO/BinaryIOStream.h" "Public/Formats/IO/Endianness.h" "Public/Formats/Aliases/Primitives.h" "Public/Formats/IO/BinaryIOStream_Versions/Little.h" "Public/Formats/IO/BinaryIOStream_Versions/Big.h")

set_property(TARGET Formats PROPERTY CXX_STANDARD 20)
set_property(TARGET Formats PROPERTY CMAKE_CXX_STANDARD_REQUIRED True)

include (TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
	target_compile_definitions(Formats PUBLIC FORMATS_BIGENDIAN=true)
else()
	target_compile_definitions(Formats PUBLIC FORMATS_BIGENDIAN=false)
endif()

target_include_directories(Formats PRIVATE Private Public)