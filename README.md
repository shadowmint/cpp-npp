# cpp-npp

Common base library.

## Install

From your project folder:

    npm init
    npm install shadowmint/cpp-npp --save

Add a dependency to your CMakeLists.txt:

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/node_modules/cpp-npp)
    include_directories(${NPP_INCLUDE_DIRS})
    target_link_libraries(${PROJECT} ${NPP_LIBS})

### Tests

    mkdir build
    cd build
    cmake ..
    cmake --build .
    ctest
