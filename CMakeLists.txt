cmake_minimum_required(VERSION 3.16)

project(Prog_Laba3 LANGUAGES C)

add_executable(Prog_Laba3 main.c
    integral.h)

include(GNUInstallDirs)
install(TARGETS Prog_Laba3
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
