set(CMAKE_SYSTEM_NAME Windows)

set(CROSS_COMPILE_SYSROOT /usr/x86_64-w64-mingw32/sys-root/mingw/)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_FIND_ROOT_PATH ${CROSS_COMPILE_SYSROOT})

set(PKG_CONFIG_EXECUTABLE /usr/bin/x86_64-w64-mingw32-pkg-config)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_INSTALL_DIR ${CROSS_COMPILE_SYSROOT}/lib/cmake/)
set(CMAKE_INSTALL_INCLUDEDIR ${CROSS_COMPILE_SYSROOT}/include/)
set(CMAKE_INSTALL_LIBDIR ${CROSS_COMPILE_SYSROOT}/lib/)
set(CMAKE_INSTALL_BINDIR ${CROSS_COMPILE_SYSROOT}/bin/)
set(CMAKE_INSTALL_PREFIX ${CROSS_COMPILE_SYSROOT})

set(ENV{PKG_CONFIG_LIBDIR} ${CMAKE_FIND_ROOT_PATH}/lib/pkgconfig:${CMAKE_FIND_ROOT_PATH}/sys-root/mingw/lib/pkgconfig)
set(ENV{PKG_CONFIG_PATH} ${CMAKE_FIND_ROOT_PATH}/lib/pkgconfig:${CMAKE_FIND_ROOT_PATH}/sys-root/mingw/lib/pkgconfig)

if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
  set(CMAKE_INSTALL_LIBDIR ${PROJECT_SOURCE_DIR}/bin/lib)
endif()

if(NOT DEFINED CMAKE_INSTALL_INCLUDEDIR)
  set(CMAKE_INSTALL_INCLUDEDIR ${PROJECT_SOURCE_DIR}/bin/include)
endif()
