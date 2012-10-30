#
#
cmake_minimum_required(VERSION 2.6)
project(DevIL)

if (COMMAND cmake_policy)
  cmake_policy(SET CMP0003 OLD)
  cmake_policy(SET CMP0005 OLD)
  if(POLICY CMP0012)
    cmake_policy(SET CMP0012 OLD)
  endif()
endif (COMMAND cmake_policy)
if(NOT DEFINED ROOT_PROJECT_NAME)
set(ROOT_PROJECT_NAME "DevIL" CACHE STRING
 "The root project/makefile/solution name. Defaults to DevIL.")
endif(NOT DEFINED ROOT_PROJECT_NAME)
project(${ROOT_PROJECT_NAME})
INCLUDE (CheckIncludeFiles)
INCLUDE (CheckLibraryExists) 

CHECK_INCLUDE_FILES("dlfcn.h" HAVE_DLFCN_H)
CHECK_INCLUDE_FILES("GLUT/glut.h" HAVE_GLUT_GLUT_H)
CHECK_INCLUDE_FILES("GL/glut.h" HAVE_GL_GLUT_H)
CHECK_INCLUDE_FILES("GL/glu.h" HAVE_GL_GLU_H)
CHECK_INCLUDE_FILES("GL/gl.h" HAVE_GL_GL_H)
CHECK_INCLUDE_FILES("inttypes.h" HAVE_INTTYPES_H)
set(HAVE_LIBM True)
#CHECK_LIBRARY_EXISTS("m" HAVE_LIBM)
CHECK_LIBRARY_EXISTS("z" "zlibVersion" "" HAVE_LIBZ)
CHECK_INCLUDE_FILES("OpenGL/glu.h" HAVE_OPENGL_GLU_H)
CHECK_INCLUDE_FILES("OpenGL/gl.h" HAVE_OPENGL_GL_H)
CHECK_INCLUDE_FILES("threads.h" HAVE_PTHREAD)
CHECK_INCLUDE_FILES("stdint.h" HAVE_STDINT_H)
CHECK_INCLUDE_FILES("stdlib.h" HAVE_STDLIB_H)
CHECK_INCLUDE_FILES("strings.h" HAVE_STRINGS_H)
CHECK_INCLUDE_FILES("string.h" HAVE_STRING_H)
CHECK_INCLUDE_FILES("sys/stat.h" HAVE_SYS_STAT_H)
CHECK_INCLUDE_FILES("sys/types.h" HAVE_SYS_TYPES_H)
CHECK_INCLUDE_FILES("unistd.h" HAVE_UNISTD_H)
CHECK_INCLUDE_FILES("windows.h" HAVE_WINDOWS_H)
CHECK_INCLUDE_FILES("sys/stat.h" HAVE_SYS_STAT_H)
SET(IL_NO_BLP False)
SET(IL_NO_BMP False)
SET(IL_NO_DCX False)
SET(IL_NO_DDS False)
SET(IL_NO_DICOM False)
SET(IL_NO_EXR True)
SET(IL_NO_FITS False)
SET(IL_NO_GAMES True)
SET(IL_NO_GIF False)
SET(IL_NO_HDR False)
SET(IL_NO_ICNS False)
SET(IL_NO_ICON False)
SET(IL_NO_IFF False)
SET(IL_NO_ILBM False)
SET(IL_NO_IWI False)
SET(IL_NO_JP2 True)
SET(IL_NO_JPG False)
MESSAGE(STATUS "IL_NO_JPG: ${IL_NO_JPG}")
SET(IL_NO_LCMS True)
SET(IL_NO_LIF True)
SET(IL_NO_MDL True)
SET(IL_NO_MNG True)
SET(IL_NO_MP3 False)
SET(IL_NO_PCD True)
SET(IL_NO_PCX True)
SET(IL_NO_PIC True)
SET(IL_NO_PNG False)
SET(IL_NO_PNM True)
SET(IL_NO_PSD True)
SET(IL_NO_PSP True)
SET(IL_NO_PXR True)
SET(IL_NO_RAW True)
SET(IL_NO_ROT True)
SET(IL_NO_SGI True)
SET(IL_NO_SUN True)
SET(IL_NO_TEXTURE True)
SET(IL_NO_TGA True)
CHECK_INCLUDE_FILES("tiffio.h" HAVE_TIFFIO_H)
if( HAVE_TIFFIO_H )
    SET(IL_NO_TIF False)
else()
    SET(IL_NO_TIF True)
endif()
MESSAGE(STATUS "IL_NO_TIF: ${IL_NO_TIF} HAVE_TIFFIO_H: ${HAVE_TIFFIO_H}")
SET(IL_NO_TPL True)
SET(IL_NO_UTX True)
SET(IL_NO_VTF True)
SET(IL_NO_WAD True)
SET(IL_NO_WAL True)
SET(IL_NO_WBMP True)
SET(IL_NO_WDP True)
SET(IL_NO_XPM True)
SET(IL_USE_DXTC_NVIDIA False)
SET(IL_USE_DXTC_SQUISH False)
SET(IL_USE_JPEGLIB_UNMODIFIED False)
SET(LCMS_NODIRINCLUDE False)

ADD_DEFINITIONS(-DNOINLINE)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/IL/config.h.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/include/IL/config.h)

include_directories (
    ${CMAKE_CURRENT_BINARY_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/src-IL/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/src-ILU/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/src-ILUT/include/
)


set(IL_SRC src-IL/src)
set(IL_INCLUDE src-IL/include)
set( libIL_la_SOURCES 
        ${IL_SRC}/il_alloc.c
    ${IL_SRC}/il_doom.c
    ${IL_SRC}/il_stack.c
    ${IL_SRC}/il_pcx.c
    ${IL_SRC}/il_rle.c
    ${IL_SRC}/il_bits.c
    ${IL_SRC}/il_endian.c
    #   ${IL_SRC}/il_exr.cpp
    ${IL_SRC}/il_jpeg.c
    ${IL_SRC}/il_pic.c
    ${IL_SRC}/il_sgi.c
    ${IL_SRC}/il_bmp.c
    ${IL_SRC}/il_error.c
    ${IL_SRC}/il_lif.c
    ${IL_SRC}/il_png.c
    ${IL_SRC}/il_states.c
    ${IL_SRC}/il_convbuff.c
    ${IL_SRC}/il_files.c
    ${IL_SRC}/il_main.c
    ${IL_SRC}/il_pnm.c
    ${IL_SRC}/il_targa.c
    ${IL_SRC}/il_wdp.c
    ${IL_SRC}/il_convert.c
    ${IL_SRC}/il_gif.c
    ${IL_SRC}/il_manip.c
    ${IL_SRC}/il_profiles.c
    ${IL_SRC}/il_tiff.c
    ${IL_SRC}/il_cut.c
    ${IL_SRC}/il_header.c
    ${IL_SRC}/il_mdl.c
    ${IL_SRC}/il_quantizer.c
    ${IL_SRC}/il_utility.c
    ${IL_SRC}/il_dcx.c
    ${IL_SRC}/il_icon.c
    ${IL_SRC}/il_mng.c
    ${IL_SRC}/il_raw.c
    ${IL_SRC}/il_wal.c
    ${IL_SRC}/il_dds.c
    ${IL_SRC}/il_internal.c
    ${IL_SRC}/il_pal.c
    ${IL_SRC}/il_rawdata.c
    ${IL_SRC}/il_devil.c
    ${IL_SRC}/il_io.c
    ${IL_SRC}/il_pcd.c
    ${IL_SRC}/il_register.c
    ${IL_SRC}/il_psd.c
    ${IL_SRC}/il_fastconv.c
    ${IL_SRC}/il_neuquant.c
    ${IL_SRC}/il_dds-save.c
    ${IL_SRC}/il_psp.c
    ${IL_SRC}/il_pix.c
    ${IL_SRC}/il_pxr.c
    ${IL_SRC}/il_vtf.c
    ${IL_SRC}/il_xpm.c
    ${IL_SRC}/il_hdr.c
    ${IL_SRC}/il_icns.c
    ${IL_SRC}/il_jp2.c
    ${IL_SRC}/altivec_common.c
    ${IL_SRC}/altivec_typeconversion.c
    ${IL_SRC}/il_sun.c
    #${IL_SRC}/il_nvidia.cpp
    ${IL_SRC}/il_wbmp.c
    #${IL_SRC}/il_squish.cpp
    ${IL_SRC}/il_iff.c
    ${IL_SRC}/il_ilbm.c
    ${IL_SRC}/il_size.c
    ${IL_SRC}/il_tpl.c
    ${IL_SRC}/il_fits.c
    ${IL_SRC}/il_iwi.c
    ${IL_SRC}/il_blp.c
    ${IL_SRC}/il_ftx.c
    ${IL_SRC}/il_dicom.c
    ${IL_SRC}/il_rot.c
    ${IL_SRC}/il_texture.c
    ${IL_SRC}/il_dpx.c
    #${IL_SRC}/il_utx.cpp
    ${IL_SRC}/il_mp3.c
    ${IL_SRC}/il_mecel_portability.c

    ${IL_INCLUDE}/altivec_common.h
    ${IL_INCLUDE}/altivec_typeconversion.h
    ${IL_INCLUDE}/il_alloc.h
    ${IL_INCLUDE}/il_bits.h
    ${IL_INCLUDE}/il_bmp.h
    ${IL_INCLUDE}/il_dcx.h
    ${IL_INCLUDE}/il_dds.h
    ${IL_INCLUDE}/il_doompal.h
    ${IL_INCLUDE}/il_dpx.h
    ${IL_INCLUDE}/il_endian.h
    ${IL_INCLUDE}/il_exr.h
    ${IL_INCLUDE}/il_files.h
    ${IL_INCLUDE}/il_gif.h
    ${IL_INCLUDE}/il_hdr.h
    ${IL_INCLUDE}/il_icns.h
    ${IL_INCLUDE}/il_icon.h
    ${IL_INCLUDE}/il_internal.h
    ${IL_INCLUDE}/il_jp2.h
    ${IL_INCLUDE}/il_jpeg.h
    ${IL_INCLUDE}/il_lif.h
    ${IL_INCLUDE}/il_manip.h
    ${IL_INCLUDE}/il_mdl.h
    ${IL_INCLUDE}/il_pal.h
    ${IL_INCLUDE}/il_pcx.h
    ${IL_INCLUDE}/il_pic.h
    ${IL_INCLUDE}/il_pnm.h
    ${IL_INCLUDE}/il_psd.h
    ${IL_INCLUDE}/il_psp.h
    ${IL_INCLUDE}/il_q2pal.h
    ${IL_INCLUDE}/il_register.h
    ${IL_INCLUDE}/il_rle.h
    ${IL_INCLUDE}/il_sgi.h
    ${IL_INCLUDE}/il_stack.h
    ${IL_INCLUDE}/il_states.h
    ${IL_INCLUDE}/il_targa.h
    ${IL_INCLUDE}/il_utx.h
    ${IL_INCLUDE}/il_vtf.h
    ${IL_INCLUDE}/il_wdp.h
    include/IL/devil_internal_exports.h
)

add_library(IL SHARED
    ${libIL_la_SOURCES}
    )
if(NOT DEFINED PNG_LIBS )
    set(PNG_LIBS png14 )
endif()
if(NOT DEFINED JPEG_LIBS )
    set(JPEG_LIBS jpeg )
endif()

target_link_libraries( IL ${PNG_LIBS} ${JPEG_LIBS} )
install(TARGETS IL
    RUNTIME DESTINATION ${DEVIL_PREFIX}/${BIN_INSTALL_DIR}
    LIBRARY DESTINATION ${DEVIL_PREFIX}/${LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${DEVIL_PREFIX}/${LIB_INSTALL_DIR}
)

set(ILU_SRC src-ILU/src)
set(ILU_INCLUDE src-ILU/include)
set(libILU_la_SOURCES 
        ${ILU_SRC}/ilu_alloc.c
    ${ILU_SRC}/ilu_internal.c
    ${ILU_SRC}/ilu_noise.c
    ${ILU_SRC}/ilu_scale.c
    ${ILU_SRC}/ilu_error.c
    ${ILU_SRC}/ilu_main.c
    ${ILU_SRC}/ilu_rotate.c
    ${ILU_SRC}/ilu_scaling.c
    ${ILU_SRC}/ilu_filter.c
    ${ILU_SRC}/ilu_manip.c
    ${ILU_SRC}/ilu_scale2d.c
    ${ILU_SRC}/ilu_states.c
    ${ILU_SRC}/ilu_filter_rcg.c
    ${ILU_SRC}/ilu_mipmap.c
    ${ILU_SRC}/ilu_scale3d.c
    ${ILU_SRC}/ilu_utilities.c
    ${ILU_SRC}/ilu_region.c

    ${ILU_INCLUDE}/ilu_alloc.h
    ${ILU_INCLUDE}/ilu_filter.h
    ${ILU_INCLUDE}/ilu_internal.h
    ${ILU_INCLUDE}/ilu_region.h
    ${ILU_INCLUDE}/ilu_states.h
    include/IL/devil_internal_exports.h
    include/IL/ilu_region.h
    ${ILU_INCLUDE}/ilu_error/ilu_err-arabic.h
    ${ILU_INCLUDE}/ilu_error/ilu_err-dutch.h
    ${ILU_INCLUDE}/ilu_error/ilu_err-english.h
    ${ILU_INCLUDE}/ilu_error/ilu_err-french.h
    ${ILU_INCLUDE}/ilu_error/ilu_err-german.h
    ${ILU_INCLUDE}/ilu_error/ilu_err-japanese.h
    ${ILU_INCLUDE}/ilu_error/ilu_err-spanish.h 
)

add_library(ILU SHARED
    ${libILU_la_SOURCES}
)
target_link_libraries( ILU IL )
install(TARGETS ILU
    RUNTIME DESTINATION ${DEVIL_PREFIX}/${BIN_INSTALL_DIR}
    LIBRARY DESTINATION ${DEVIL_PREFIX}/${LIB_INSTALL_DIR}
    ARCHIVE DESTINATION ${DEVIL_PREFIX}/${LIB_INSTALL_DIR}
)

if(NOT DONT_BUILD_ILUT )
    set(ILUT_SRC src-ILUT/src)
    set(ILUT_INCLUDE src-ILUT/include)
    set(libILUT_la_SOURCES 
        ${ILUT_SRC}/ilut_main.c
        ${ILUT_SRC}/ilut_states.c
        ${ILUT_SRC}/ilut_internal.c  
        ${ILUT_SRC}/ilut_win32.c  
        ${ILUT_SRC}/ilut_opengl.c  
        ${ILUT_SRC}/ilut_directx.c  
        ${ILUT_SRC}/ilut_directx9.c  
        ${ILUT_SRC}/ilut_x11.c  
        ${ILUT_INCLUDE}/ilut_internal.h
        ${ILUT_INCLUDE}/ilut_states.h
        include/IL/devil_internal_exports.h
    )

    add_library(ILUT SHARED
        ${libILUT_la_SOURCES}
    )
    target_link_libraries( ILUT ILU IL )
    install(TARGETS ILUT
        RUNTIME DESTINATION ${DEVIL_PREFIX}/${BIN_INSTALL_DIR}
        LIBRARY DESTINATION ${DEVIL_PREFIX}/${LIB_INSTALL_DIR}
        ARCHIVE DESTINATION ${DEVIL_PREFIX}/${LIB_INSTALL_DIR}
    )
endif()

if(NOT DEFINED DEVIL_PREFIX)
    set(DEVIL_PREFIX ".")
endif()

EXPORT_LIBRARY_DEPENDENCIES(CMakeDepends.txt)
