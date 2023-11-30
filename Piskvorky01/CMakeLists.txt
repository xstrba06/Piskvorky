# CMakeList.txt : CMake project for Piskvorky01, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Piskvorky01 "Piskvorky01.cpp" "Piskvorky01.h" "PiskvorkyFunkcie.h" "PiskvorkyFunkcie.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Piskvorky01 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
