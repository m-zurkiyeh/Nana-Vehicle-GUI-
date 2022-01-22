# CMakeList.txt : CMake project for Final Project, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("FinalProject")

# Add source to this project's executable.
add_executable (FinalProject "Final Project.cpp" "Final Project.h"   "customer.cpp" "customer.h"  "Vehicle.h" "Vehicle.cpp" "RentalLocation.h" "RentalLocation.cpp")
add_definitions( -D_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
target_include_directories(FinalProject PUBLIC "c:\\nana\\include")
target_link_libraries(FinalProject "nana_v142_Debug_x64")
target_link_directories(FinalProject PUBLIC "c:\\nana\\build\\bin")

# TODO: Add tests and install targets if needed.
