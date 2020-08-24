INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_VDIF vdif)

FIND_PATH(
    VDIF_INCLUDE_DIRS
    NAMES vdif/api.h
    HINTS $ENV{VDIF_DIR}/include
        ${PC_VDIF_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    VDIF_LIBRARIES
    NAMES gnuradio-vdif
    HINTS $ENV{VDIF_DIR}/lib
        ${PC_VDIF_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/vdifTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(VDIF DEFAULT_MSG VDIF_LIBRARIES VDIF_INCLUDE_DIRS)
MARK_AS_ADVANCED(VDIF_LIBRARIES VDIF_INCLUDE_DIRS)
