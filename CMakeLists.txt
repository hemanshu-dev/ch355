cmake_minimum_required(VERSION 3.2)

project(ch355)

include(ExternalProject)

find_package(PkgConfig REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/bin)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(BIN_DIR     ${PROJECT_SOURCE_DIR}/bin)
set(LIB_DIR     ${PROJECT_SOURCE_DIR}/lib)
set(SRC_DIR     ${PROJECT_SOURCE_DIR}/src)

set(HEADERS_DIR ${PROJECT_SOURCE_DIR}/inc)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build ncurses from source
file(MAKE_DIRECTORY ${LIB_DIR}/generated_libs)
file(MAKE_DIRECTORY ${LIB_DIR}/ncurses-snapshots/build)
file(MAKE_DIRECTORY ${LIB_DIR}/googletest/build)

ExternalProject_ADD(ncurses PREFIX              ${LIB_DIR}/ncurses-snapshots/
                            SOURCE_DIR          ${LIB_DIR}/ncurses-snapshots/
                            INSTALL_DIR         ${LIB_DIR}/generated_libs/
                            BINARY_DIR          ${LIB_DIR}/ncurses-snapshots/build
                            CONFIGURE_COMMAND   ${LIB_DIR}/ncurses-snapshots/configure --prefix=${LIB_DIR}/generated_libs --with-shared  --with-debug --with-pkg-config-libdir=${LIB_DIR}/generated_libs/lib64/pkgconfig/  --enable-widec  --enable-pc-files  --enable-ext-colors --enable-ext-mouse --with-gpm  --enable-sp-funcs --enable-check-size  --with-cxx-binding --with-normal  --enable-expanded  --enable-ext-putwin  --with-profile --with-trace  --with-valgrind  --with-manpages
                            BUILD_COMMAND   make -j$(nproc)
                            INSTALL_COMMAND make install
                            )
pkg_check_modules(NCURSESW REQUIRED ncurses++w)


# Build google test from source 
ExternalProject_ADD(googletest  PREFIX              ${LIB_DIR}/googletest/
                                SOURCE_DIR          ${LIB_DIR}/googletest/
                                INSTALL_DIR         ${LIB_DIR}/generated_libs/
                                BINARY_DIR          ${LIB_DIR}/googletest/build/
                                CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${LIB_DIR}/generated_libs)

add_executable(ch355)

target_sources(ch355 PRIVATE ${SRC_DIR}/main.cpp
                     PRIVATE ${SRC_DIR}/app.cpp
                     PRIVATE ${SRC_DIR}/chessboard.cpp)

target_include_directories(ch355 PRIVATE ${INCLUDE_DIR}
                                 PRIVATE ${LIB_DIR}/generated_libs/include)

target_link_directories(ch355 PRIVATE ${NCURSESW_LIBRARY_DIRS})

target_link_libraries(ch355 PRIVATE -lncursesw
                            PRIVATE -lmenuw)

