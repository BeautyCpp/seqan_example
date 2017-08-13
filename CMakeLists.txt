# ===========================================================================
cmake_minimum_required(VERSION 3.0)


# ===========================================================================
# We use hunter for package manage
# ===========================================================================
include("cmake/Hunter/HunterGate.cmake")
HunterGate(
        URL "https://github.com/ruslo/hunter/archive/v0.16.24.tar.gz"
        SHA1 "00ab627d3d4fe5151e15b6ab2b1b1da17650984a"
)
cmake_policy(SET CMP0054 NEW)
# custom cmake scripts
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (seqan_example CXX)

set(SeqAnRoot /home/tom/z.git.github.beautycpp/seqan)

hunter_add_package(Catch)
find_package(Catch CONFIG REQUIRED)

include_directories(${SeqAnRoot}/include)

enable_testing(true)

add_subdirectory(index)