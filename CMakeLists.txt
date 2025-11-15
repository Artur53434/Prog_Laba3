cmake_minimum_required(VERSION 3.16)

project(Prog_Consol_Project_Laba3_v0_5 LANGUAGES C)

add_executable(Prog_Consol_Project_Laba3_v0_5 main.c)

include(GNUInstallDirs)
install(TARGETS Prog_Consol_Project_Laba3_v0_5
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
