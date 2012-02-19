#
# Frist set up minmal CMake info and project name
cmake_minimum_required(VERSION 2.6)
if (COMMAND cmake_policy)
  cmake_policy(SET CMP0003 OLD)
  cmake_policy(SET CMP0005 OLD)
endif (COMMAND cmake_policy)
if(NOT DEFINED ROOT_PROJECT_NAME)
set(ROOT_PROJECT_NAME "DevIL" CACHE STRING
 "The root project/makefile/solution name. Defaults to DevIL.")
endif(NOT DEFINED ROOT_PROJECT_NAME)
project(${ROOT_PROJECT_NAME})

#
# Includes to we can test headerfiles
#

INCLUDE (CheckIncludeFiles)
INCLUDE (CheckLibraryExists) 
INCLUDE (CheckPrototypeDefinition) 
INCLUDE (CheckCCompilerFlag) 

CHECK_C_COMPILER_FLAG(maltivec HAVE_ALTIVEC_GCC)
if(HAVE_ALTIVEC_GCC)
  SET(ALTIVEC_GCC True CACHE Bool "If to use Altivec instruction")
else()
  SET(ALTIVEC_GCC False CACHE Bool "If to use Altivec instruction")
endif()

SET(DEBUG False CACHE Bool "Enable debug code features")

CHECK_INCLUDE_FILES("allegro.h" HAVE_ALLEGRO_H)
if(HAVE_ALLEGRO_H)
  SET(ILUT_USE_ALLEGRO True CACHE Bool "Support Allegro API")
else()
  SET(ILUT_USE_ALLEGRO False CACHE Bool "Support Allegro API")
endif()

CHECK_INCLUDE_FILES("d3d8.h" HAVE_D3D8_H )
if(HAVE_D3D8_H)
  SET(ILUT_USE_DIRECTX8 True CACHE Bool "Support DirectX8 API")
else()
  SET(ILUT_USE_DIRECTX8 False CACHE Bool "Support DirectX8 API")
endif()

CHECK_INCLUDE_FILES("d3d9.h" HAVE_D3D9_H )
if(HAVE_D3D9_H)
  SET(ILUT_USE_DIRECTX9 True CACHE Bool "Support DirectX9 API")
else()
  SET(ILUT_USE_DIRECTX9 False CACHE Bool "Support DirectX9 API")
endif()

CHECK_INCLUDE_FILES("d3d10.h" HAVE_D3D10_H )
if(HAVE_D3D10_H)
  SET(ILUT_USE_DIRECTX10 True CACHE Bool "Support DirectX10 API")
else()
  SET(ILUT_USE_DIRECTX10 False CACHE Bool "Support DirectX10 API")
endif()

CHECK_INCLUDE_FILES("GL/gl.h" HAVE_GL_GL_H )
CHECK_INCLUDE_FILES("GL/glu.h" HAVE_GL_GLU_H )
CHECK_INCLUDE_FILES("OpenGL/gl.h" HAVE_OPENGL_GL_H )
CHECK_INCLUDE_FILES("OpenGL/glu.h" HAVE_OPENGL_GLU_H )
if(HAVE_GL_GLU_H OR HAVE_OPENGL_GLU_H)
  SET(ILUT_USE_OPENGL True CACHE Bool "Define if system supports OpenGL API")
else()
  SET(ILUT_USE_OPENGL False CACHE Bool "Define if system supports OpenGL API")
endif()

CHECK_INCLUDE_FILES("SDL.h" HAVE_SDL_H )
if(HAVE_SDL_H)
  SET(ILUT_USE_SDL True CACHE Bool "Support SDL API")
else()
  SET(ILUT_USE_SDL False CACHE Bool "Support SDL API")
endif()

CHECK_INCLUDE_FILES("X11/Xutil.h" HAVE_X11_XUTIL_H )
if(HAVE_X11_XUTIL_H)
  SET(ILUT_USE_X11 True CACHE Bool "Support X11 API")
else()
  SET(ILUT_USE_X11 False CACHE Bool "Support X11 API")
endif()

CHECK_INCLUDE_FILES("sys/ipc.h" HAVE_SYS_IPC_H )
CHECK_INCLUDE_FILES("sys/shm.h" HAVE_SYS_SHM_H )
CHECK_INCLUDE_FILES("X11/extensions/XShm.h" HAVE_EXTENTIONS_XSHM_H )
if(HAVE_SYS_IPC_H AND HAVE_SYS_SHM_H AND HAVE_EXTENTIONS_XSHM_H)
  SET(ILUT_USE_XSHM True CACHE Bool "Support X11 XShm extention")
else()
  SET(ILUT_USE_XSHM False CACHE Bool "Support X11 XShm extention")
endif()

check_prototype_definition(_wfopen "FILE *_wfopen( const wchar_t *filename, const wchar_t *mode )" NULL "stdio.h;wchar.h" HAVE_WIN32_WFOPEN)



SET(IL_NO_BLP False CACHE Bool "blp support (BLP is the texture format for Blizzard games.)")
SET(IL_NO_BMP False CACHE Bool "bmp support (BMP is a standard Windows bitmap.)")
SET(IL_NO_DCX False CACHE Bool "dcx support (DCX is a multi-page PCX file.)")
SET(IL_NO_DDS False CACHE Bool "dds support (DDS (DirectDraw Surface) is used by DirectX to load images (usually DXTC).)")
SET(IL_NO_DICOM False CACHE Bool "dicom support (DICOM (Digital Imaging and Communications in Medicine) is used extensively in medical imaging.)")
SET(IL_NO_EXR True "exr support (EXR is a HDR image file format standardized by Industrial Light and Magic. OpenEXR powered)")
SET(IL_NO_FITS False CACHE Bool "fits support (FITS (Flexible Image Transport System) is used for storing scientific images and is used extensively in astronomy.)")
SET(IL_NO_GAMES False CACHE Bool "Define if you want to disable support for various game formats")
SET(IL_NO_GIF False CACHE Bool "gif support (GIF is lossy and proprietary format used mainly to make animations)")
SET(IL_NO_HDR False CACHE Bool "hdr support (HDR is the Radiance High Dynamic Range format, using more bits per channel than normal.)")
SET(IL_NO_ICNS False CACHE Bool "icns support (ICNS is the icon format for the Mac OS X operation system.)")
SET(IL_NO_ICON False CACHE Bool "icon support (ICO is the icon format for the Windows operating system.)")
SET(IL_NO_IFF False CACHE Bool "iff support (IFF (Interchange File Format) is used to transfer images between software from different companies.)")
SET(IL_NO_ILBM False CACHE Bool "ilbm support (ILBM (Amiga Interleaved BitMap Format).)")
SET(IL_NO_IWI False CACHE Bool "iwi support (IWI is the Infinity Ward Image format used in the Call of Duty games.)")
include(FindJasper)
if(JASPER_FOUND)
  SET(IL_NO_JP2 False CACHE Bool "jp2 support (JP2 (JPEG 2000) is a better, but not so widespread, alternative to JPEG. JasPer powered)")
  include_directories ( ${JASPER_INCLUDE_DIR} )
  set(LINK_LIBRARIES ${LINK_LIBRARIES} ${JASPER_LIBRARIES} )
else()
  SET(IL_NO_JP2 True CACHE Bool "jp2 support (JP2 (JPEG 2000) is a better, but not so widespread, alternative to JPEG. JasPer powered)")
endif()
include(FindJPEG)
if(JPEG_FOUND)
  SET(IL_NO_JPG False CACHE Bool "jpeg support (JPEG is most common lossy format. libjpeg powered)")
  include_directories ( ${JPEG_INCLUDE_DIR} )
  set(LINK_LIBRARIES ${LINK_LIBRARIES} ${JPEG_LIBRARIES} )
else()
  SET(IL_NO_JPG True CACHE Bool "jpeg support (JPEG is most common lossy format. libjpeg powered)")
endif()
CHECK_INCLUDE_FILES("lcms/lcms.h" HAVE_LCMS_LCMS_H)
CHECK_INCLUDE_FILES("lcms.h" HAVE_LCMS_H)
SET(LCMS_NODIRINCLUDE False)
if(HAVE_LCMS_H)
  SET(IL_NO_LCMS False CACHE Bool "lcms color profile library support ()")
  SET(LCMS_NODIRINCLUDE True)
elseif(HAVE_LCMS_LCMS_H)
  SET(IL_NO_LCMS False CACHE Bool "lcms color profile library support ()")
  SET(LCMS_NODIRINCLUDE False)
else()
  SET(IL_NO_LCMS True CACHE Bool "lcms color profile library support ()")
  SET(LCMS_NODIRINCLUDE False)
endif()

SET(IL_NO_LIF True CACHE Bool "lif support (LIF is the image format of the
game Homeworld.)")
SET(IL_NO_MDL False CACHE Bool "mdl support (MDL is the format for models in
the game Half-Life.)")
CHECK_INCLUDE_FILES("libmng.h" HAVE_MNG_H)
if(HAVE_MNG_H)
  SET(IL_NO_MNG False CACHE Bool "mng support (MNG is basically the animated version of PNG but is not widespread.)")
  set(LINK_LIBRARIES ${LINK_LIBRARIES} mng )
else()
  SET(IL_NO_MNG True CACHE Bool "mng support (MNG is basically the animated version of PNG but is not widespread.)")
endif()
SET(IL_NO_MP3 False CACHE Bool "mp3 support (MP3 (MPEG-1 Audio Layer 3) sometimes have images in them, such as cover art.)")
SET(IL_NO_PCD False CACHE Bool "pcd support (PCD is the Kodak PhotoCD format.)")
SET(IL_NO_PCX False CACHE Bool "pcx support (PCX is one of the first widely accepted DOS imaging standards)")
SET(IL_NO_PIC False CACHE Bool "pic support (PIC is used by SoftImage software.)")
SET(IL_NO_PIX True CACHE Bool "pix support ()")
include(FindPNG)
if(PNG_FOUND)
  SET(IL_NO_PNG False CACHE Bool "png support (PNG is a smart, loseless and even open format. libpng powered.)")
  include_directories ( ${PNG_INCLUDE_DIRS} )
  add_definitions (${PNG_DEFINITIONS} )
  set(LINK_LIBRARIES ${LINK_LIBRARIES} ${PNG_LIBRARIES} )
else()
  SET(IL_NO_PNG True CACHE Bool "png support (PNG is a smart, loseless and even open format. libpng powered.)")
endif()
SET(IL_NO_PNM False CACHE Bool "pnm support (PNM (Portable aNy Map format) is considered the least-common-denominator for converting pixmap, graymap, or bitmap files between different platforms.)")
SET(IL_NO_PSD False CACHE Bool "psd support (PSD is the PhotoShop native file format.)")
SET(IL_NO_PSP True CACHE Bool "psp support (PSP is the Paint Shop Pro native file format.)")
SET(IL_NO_PXR True CACHE Bool "pxr support (PXR is used by Pixar.)")
SET(IL_NO_RAW True CACHE Bool "raw support (RAW is simply raw data.)")
SET(IL_NO_ROT True CACHE Bool "rot support (ROT is the image format for the game Homeworld 2.)")
SET(IL_NO_SGI False CACHE Bool "sgi support (SGI is the native raster graphics file format for Silicon Graphics workstations)")
SET(IL_NO_SUN False CACHE Bool "sun support (SUN is the image format used on Sun's operating systems.)")
SET(IL_NO_TEXTURE False CACHE Bool "texture support (TEXTURE is the format used in Medieval II: Total War (similar to DDS).)")
SET(IL_NO_TGA False CACHE Bool "tga support (TGA (aka TARGA file format) has been used mainly in games. It is open and simple.)")
include(FindTIFF)
if(TIFF_FOUND)
  SET(IL_NO_TIF False CACHE Bool "tiff support (TIFF is a lossless format supporting greater color depths. (libtiff powered)")
  include_directories ( ${TIFF_INCLUDE_DIR} )
  set(LINK_LIBRARIES ${LINK_LIBRARIES} ${TIFF_LIBRARIES} )
else()
  SET(IL_NO_TIF True CACHE Bool "tiff support (TIFF is a lossless format supporting greater color depths. (libtiff powered)")
endif()
SET(IL_NO_TPL False CACHE Bool "tpl support (TPL is the format used by many GameCube and Wii games.)")
SET(IL_NO_UTX False CACHE Bool "utx support (UTX is the format used in the Unreal Tournament game series.)")
SET(IL_NO_VTF False CACHE Bool "vtf support (VTF (Valve Texture Format) is used by games based on Valve's Source engine.)")
SET(IL_NO_WAD False CACHE Bool "doom support (WAD is the format for graphics in the original DooM I/II.)")
SET(IL_NO_WAL False CACHE Bool "wal support (WAL is the image format used for the game Quake 2.)")
SET(IL_NO_WBMP False CACHE Bool "wbmp support (WBMP (Wireless Application Protocol Bitmap) is a monochrome graphics file format optimized for mobile computing devices)")
SET(IL_NO_WDP False CACHE Bool "wdp support (WDP is Microsoft's successor to JPEG, able to store many different image types either lossy or losslessly, also known as HD Photo.)")
SET(IL_NO_XPM False CACHE Bool "xpm support (XPM (X PixMap) is an ASCII-based image used in X Windows.)")
CHECK_INCLUDE_FILES("nvtt/nvtt.h" HAVE_NVTT_NVTT_H )
CHECK_INCLUDE_FILES("nvcore/Memory.h" HAVE_NVCORE_MEMORY_H )
if(HAVE_NVTT_NVTT_H OR HAVE_NVCORE_MEMORY_H)
  SET(IL_USE_DXTC_NVIDIA True CACHE Bool "Define if you have nvidia texture tools library installed")
else()
  SET(IL_USE_DXTC_NVIDIA False CACHE Bool "Define if you have nvidia texture tools library installed")
endif()
CHECK_INCLUDE_FILES("squish.h" HAVE_SQUISH_H )
if(HAVE_SQUISH_H)
  SET(IL_USE_DXTC_SQUISH True CACHE Bool "Define if you have libsquish installed")
else()
  SET(IL_USE_DXTC_SQUISH False CACHE Bool "Define if you have libsquish installed")
endif()

set(HAVE_LIBM True CACHE Bool "If have math lib.")
#CHECK_LIBRARY_EXISTS("m" HAVE_LIBM)

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
	${IL_SRC}/il_exr.cpp
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
	${IL_SRC}/il_nvidia.cpp
	${IL_SRC}/il_wbmp.c
	${IL_SRC}/il_squish.cpp
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
	${IL_SRC}/il_utx.cpp
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
target_link_libraries(IL
    ${LINK_LIBRARIES}
)
SET(ILU_ENABLED True CACHE Bool "If to build the ILU library")
if(ILU_ENABLED)
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
endif()

set(ILUT_SRC src-ILUT/src)
set(ILUT_INCLUDE src-ILUT/include)
set(libILUT_la_SOURCES 
	${ILUT_SRC}/ilut_main.c
	${ILUT_SRC}/ilut_states.c
	${ILUT_SRC}/ilut_internal.c  
	${ILUT_INCLUDE}/ilut_internal.h
	${ILUT_INCLUDE}/ilut_states.h
	include/IL/devil_internal_exports.h
)

add_library(ILUT SHARED
	${libILUT_la_SOURCES}
)

install(DIRECTORY include/IL
        DESTINATION include
	)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/include/IL/config.h
	DESTINATION include/IL/
)

install(TARGETS IL ILU ILUT
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
if(${ROOT_PROJECT_NAME} STREQUAL "DevIL")
  include(CPack)
endif()
EXPORT_LIBRARY_DEPENDENCIES(CMakeDepends.txt)

add_executable(simple
    examples/simple_example/simple.c
)
target_link_libraries(simple
    IL
)

find_program( PYBOT_BIN pybot
)

if(PYBOT_BIN)
    message(STATUS "Have pybot: Acceptance Testing Enabeled")
    enable_testing()
    add_test(
      NAME acceptancetest
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMAND pybot -n loadtests -v binarydir:${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Tests
    )
endif()
