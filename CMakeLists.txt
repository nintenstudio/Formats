# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Formats CXX)
add_library(Formats STATIC "Public/Formats/Resource.h" "Public/Formats/Resources/BYML/BYML.h" "Private/Formats/Resources/BYML/BYML.cpp" "Public/Formats/Resources/AAMP/AAMP.h" "Private/Formats/Resources/AAMP/AAMP.cpp" "Public/Formats/Resources/BFRES/BFRES.h" "Private/Formats/Resources/BFRES/BFRES.cpp" "Public/Formats/Resources/BFRES/Versions/V0.10.0.0/0.10.0.0.h" "Private/Formats/Resources/BFRES/Versions/V0.10.0.0/0.10.0.0.cpp" "Public/Formats/Resources/BYML/Versions/V7/V7.h" "Private/Formats/Resources/BYML/Versions/V7/V7.cpp" "Public/Formats/IO/BinaryIOStream.h" "Public/Formats/IO/Endianness.h" "Public/Formats/Aliases/Primitives.h"   "Public/Formats/Resources/BYML/Versions/V7/Nodes/String.h" "Public/Formats/Resources/BYML/Node.h" "Private/Formats/Resources/BYML/Versions/V7/Nodes/String.cpp" "Public/Formats/Resources/BYML/Versions/V7/Nodes/BinaryData.h" "Public/Formats/Resources/BYML/Nodes/BinaryData.h" "Public/Formats/Resources/BYML/Nodes/Array.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/Array.h" "Public/Formats/Resources/BYML/Nodes/StringHash.h" "Public/Formats/Resources/BYML/Nodes/Float.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/Float.h" "Public/Formats/Resources/BYML/Nodes/UInt.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/UInt.h" "Public/Formats/Resources/BYML/Nodes/Int64.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/Int64.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/UInt64.h" "Public/Formats/Resources/BYML/Nodes/Double.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/Double.h" "Public/Formats/Resources/BYML/Nodes/Null.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/Null.h" "Private/Formats/Resources/BYML/Versions/V7/Nodes/StringTable.cpp" "Public/Formats/Resources/BYML/Versions/V7/NodeType.h" "Public/Formats/Primitives/Int24.h" "Public/Formats/Primitives/UInt24.h" "Private/Formats/Resources/BYML/Versions/V7/Nodes/Array.cpp" "Private/Formats/Resource.cpp" "Public/Formats/Resources/BYML/Versions/V7/Nodes/PlainHash.h" "Public/Formats/Resources/BYML/Nodes/PlainHash.h" "Public/Formats/Resources/BYML/Nodes/ValueHash.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/ValueHash.h" "Public/Formats/Resources/BYML/Nodes/FileData.h" "Public/Formats/Resources/BYML/Versions/V7/Nodes/FileData.h"  "Private/Formats/Resources/BYML/Versions/V7/Nodes/PlainHash.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/StringHash.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/BinaryData.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/Bool.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/FileData.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/Double.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/Float.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/UInt.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/Int64.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/Null.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/Int.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/UInt64.cpp" "Private/Formats/Resources/BYML/Versions/V7/Nodes/ValueHash.cpp" "Public/Formats/Resources/BYML/Versions/V7/Node.h" "Public/Formats/IO/BinaryIOStreamBasic.h"  "Public/Formats/Resources/ZSTD/ZSTD.h" "Public/Formats/Resources/Binary/Binary.h" "Private/Formats/Resources/Binary/Binary.cpp" "Public/Formats/Resources/ZSTD/ZSTDBackend.h" "Private/Formats/Resources/ZSTD/ZSTDBackend.cpp" "Public/Formats/Resources/ZSTD/CompressionInfo.h" "Public/Formats/IO/BinaryIOStreamBasics/Buffer/Buffer.h" "Public/Formats/IO/BinaryIOStreams/Buffer/Buffer.h" "Private/Formats/IO/BinaryIOStreams/Buffer/Buffer.cpp" "Public/Formats/IO/BinaryIOStreams/Buffer/Big.h" "Public/Formats/IO/BinaryIOStreams/Buffer/Little.h" "Private/Formats/IO/BinaryIOStreamBasics/Buffer/Buffer.cpp" "Public/Formats/Resources/TXTG/TXTG.h" "Private/Formats/Resources/TXTG/TXTG.cpp" "Public/Formats/Resources/TXTG/Versions/V0x11/V0x11.h" "Private/Formats/Resources/TXTG/Versions/V0x11/V0x11.cpp" "Public/Formats/Resources/TXTG/Surface.h" "Public/Formats/Resources/TXTG/Versions/V0x11/Surface.h" "Public/Formats/Swizzling/Format.h")

include (TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
	target_compile_definitions(Formats PUBLIC FORMATS_BIGENDIAN=true)
else()
	target_compile_definitions(Formats PUBLIC FORMATS_BIGENDIAN=false)
endif()

option(FORMATS_RESOURCES_BYML_ACCEPTLESSERVERSIONS "Allow code for greater BYML versions to act as a fallback if the target version is not implemented." ON)
if (FORMATS_RESOURCES_BYML_ACCEPTLESSERVERSIONS)
	target_compile_definitions(Formats PUBLIC FORMATS_RESOURCES_BYML_ACCEPTLESSERVERSIONS=true)
else()
	target_compile_definitions(Formats PUBLIC FORMATS_RESOURCES_BYML_ACCEPTLESSERVERSIONS=false)
endif()

target_include_directories(Formats PRIVATE Private)
target_include_directories(Formats PUBLIC Public)

add_subdirectory("Lib/YAML-CPP")
target_link_libraries(Formats PUBLIC yaml-cpp)

set(ZSTD_BUILD_STATIC ON CACHE BOOL "" FORCE)
set(ZSTD_BUILD_SHARED OFF CACHE BOOL "" FORCE)
add_subdirectory("Lib/ZSTD/build/cmake")
target_include_directories(Formats PRIVATE Lib/ZSTD/lib)
target_link_libraries(Formats PRIVATE libzstd_static)

#set(Rust_CARGO_TARGET "aarch64-nintendo-switch-freestanding")

FetchContent_Declare(
    Corrosion
    GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
    GIT_TAG v0.4 # Optionally specify a commit hash, version tag or branch here
)
FetchContent_MakeAvailable(Corrosion)

corrosion_import_crate(MANIFEST_PATH Lib/Tegra-Swizzle/Cargo.toml CRATES tegra_swizzle CRATE_TYPES staticlib FEATURES ffi FLAGS -Zbuild-std=core,compiler_builtins,alloc -Zbuild-std-features=compiler-builtins-mem)
target_link_libraries(Formats PUBLIC tegra_swizzle)