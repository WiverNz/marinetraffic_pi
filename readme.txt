Install and add cmake and mingw 4.9.2 add bin to PATH (and Tools\mingw492_32\i686-w64-mingw32\lib)
E:\adept\Qt5.6.1\Tools\mingw492_32\bin;E:\adept\Qt5.6.1\Tools\mingw492_32\i686-w64-mingw32\include;E:\adept\Qt5.6.1\Tools\mingw492_32\i686-w64-mingw32\bin;E:\adept\Qt5.6.1\Tools\mingw492_32\i686-w64-mingw32\lib;E:\adept\Qt5.6.1\Tools\QtCreator\bin;E:\adept\Qt5.6.1\5.6\mingw49_32\bin;E:\adept\Projects\wxWidgets-3.1.0\lib\gcc_dll;E:\adept\Projects\wxWidgets-3.1.0\lib\gcc_dll\mswu;E:\adept\Projects\wxWidgets-3.1.0;
run mingw49_32\bin\qtenv2.bat
build wxWidgets-3.1.0
cd wxWidgets-3.1.0\build\msw
mingw32-make -f -j4 makefile.gcc BUILD=release SHARED=1 MONOLITHIC=0 UNICODE=1 WXUNIV=0 USE_OPENGL=1 USE_GDIPLUS=1 USE_XRC=1 USE_XUI=1 USE_SVG=1
copy all files (dll, lib) from OpenCPN\buildwin\gtk to wxWidgets-3.1.0\lib\gcc_dll (for resolve libs path when compile opencpn)
in lib\gcc_lib\mswu\wx\setup.h #define wxUSE_GRAPHICS_CONTEXT 1 #define wxUSE_GLCANVAS 1
and I did it again mingw32-make -f makefile.gcc -j4 BUILD=release SHARED=1 MONOLITHIC=0 UNICODE=1 WXUNIV=0 USE_OPENGL=1 USE_GDIPLUS=1 USE_XRC=1 USE_XUI=1 USE_SVG=1
cp ../../lib/gcc_dll/libwxzlib.a ../../lib/gcc_dll/libwxzlib-2.8.a

add wxWidgets-3.1.0 root directory to PATH variable
install poedit and add Poedit\GettextTools\bin to PATH
#download and compile curl: mingw32-make mingw32
in OpenCPN comment all lines in chartdldr_pi.cpp and chartdldr_pi.h that contains wxEVT_DOWNLOAD_EVENT
#in new build directory for OpenCPN copy from curl/lib/libcurldll.a to lib/libcurl.a
in cmake variables in qtcreator add CMAKE_MAKE_PROGRAM = jom.exe and Tool arguments -j4
build opencpn.

boost:
C:\boost_1_52_0> bootstrap.bat gcc
BuildingBoost.Build engine
...
b2 variant=debug,release toolset=gcc link=shared -j 4

+Debug
chartdldrgui.cpp
-- bSizerCatalogBtns->Add( m_bUpdateAllCharts, 0, wxALIGN_BOTTOM|wxALL|wxEXPAND, 5 );
++ bSizerCatalogBtns->Add( m_bUpdateAllCharts, 0, /*wxALIGN_BOTTOM|*/wxALL|wxEXPAND, 5 );
tri.c
-- inline int int_min(ipoint_t *yval, ipoint_t *v0, ipoint_t *v1)
++ int int_min(ipoint_t *yval, ipoint_t *v0, ipoint_t *v1)
-- inline int int_max(ipoint_t *yval, ipoint_t *v0, ipoint_t *v1)
++ int int_max(ipoint_t *yval, ipoint_t *v0, ipoint_t *v1)
-- inline int int_is_left_of(int segnum, ipoint_t *v)
++ int int_is_left_of(int segnum, ipoint_t *v)
pluginmanager.cpp
#ifdef __WXMSW__
#ifdef _DEBUG
get_flags = wxDIR_FILES;
#endif 
#endif

#ifdef __WXMSW__FALSE
#ifdef _DEBUG
get_flags = wxDIR_FILES;
#endif 
#endif

wx/math.h

#include <cmath> after math.h

#elif defined(__GNUG__)||defined(__GNUWIN32__)
..
#define wxIsNaN(x) std::isnan(x)

in opencpn/cmakelist.txt

after PROJECT(OpenCPN)

IF(MINGW)
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED on)
ENDIF(MINGW)

void OCPNPlatform::HideBusySpinner( void )
{
#ifdef __OCPN__ANDROID__
    androidHideBusyIcon();
#else
    #if wxCHECK_VERSION(2, 9, 0 )
    if( ::wxIsBusy() )
    {
        ::wxEndBusyCursor();
    }
    #endif
#endif    
}

https://www.fugawi.com/contact 
http://opencpn.org/ocpn/download 
http://www.marinetraffic.com/ru/ais/home/centerx:-74/centery:40/zoom:11
https://habrahabr.ru/post/212027/
add WXWIN C:\wxWidgets-2.8.12
PATH C:\Qt\Qt5.6.0\Tools\mingw492_32\bin;C:\Program Files (x86)\CMake\bin;C:\wxWidgets-2.8.12;C:\wxWidgets-2.8.12\lib\gcc_lib;C:\Program Files (x86)\Poedit\GettextTools\bin;
mingw32-make -f makefile.gcc BUILD=release SHARED=1 MONOLITHIC=0 UNICODE=1 WXUNIV=0 USE_OPENGL=1
C:\wxWidgets-2.8.12\lib\gcc_lib\mswu\wx\setup.h
#define wxUSE_GLCANVAS 1
-G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=./build
Запускаю cmd, перехожу в папку с распакованным Curl, выполняю mingw32-make mingw32
https://curl.haxx.se/download.html
-G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=./build
PATH C:\Users\askibin\develop\curl-7.49.1\lib
перенести libcurldll.a  в build-OpenCPN-Qt_5_6_0_mingw49_32-Default\lib\libcurl.a

C:\Qt\Qt5.6.0\Tools\mingw492_32\bin;C:\Qt\4.8.1\bin;C:\mingw-4.4.0\mingw-4.4.0\bin;C:\Python27\;C:\Qt\Qt5.5.0\Tools\QtCreator\bin;C:\ProgramData\Oracle\Java\javapath;C:\dev\Perl\site\bin;C:\dev\Perl\bin;C:\Python27\x64\;C:\Python27\Lib\site-packages\PyQt4;C:\Python27\;C:\Python27\Scripts;C:\Program Files (x86)\Intel\iCLS Client\;C:\Program Files\Intel\iCLS Client\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\Intel\OpenCL SDK\3.0\bin\x86;C:\Program Files (x86)\Intel\OpenCL SDK\3.0\bin\x64;C:\Program Files\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files\Intel\Intel(R) Management Engine Components\IPT;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\IPT;C:\Program Files\Mercurial\;C:\Program Files\Microsoft SQL Server\Client SDK\ODBC\110\Tools\Binn\;C:\Program Files (x86)\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files (x86)\Microsoft SQL Server\120\Tools\Binn\ManagementStudio\;C:\Program Files (x86)\Microsoft SQL Server;C:\Program Files (x86)\Skype\Phone\;c:\Program Files (x86)\Microsoft SQL Server\110\Tools\Binn\;c:\Program Files\Microsoft SQL Server\110\Tools\Binn\;c:\Program Files\Microsoft SQL Server\110\DTS\Binn\;C:\Program Files\TortoiseHg\;C:\Program Files\CMake\bin;C:\Program Files (x86)\CMake\bin;C:\Program Files (x86)\Poedit\GettextTools\bin;C:\Users\askibin\develop\wxWidgets-3.1.0;C:\Users\askibin\develop\wxWidgets-3.1.0\lib\gcc_lib;C:\Users\askibin\develop\curl-7.49.1\lib


if(WIN32)
MESSAGE("WINDOWS!")
add_library(curlSTATICIMPORTED)
#set(CURL_INCLUDE_DIRE:/adept/libs/curl-7.49.1/include)
SET_PROPERTY(TARGETcurlPROPERTYIMPORTED_LOCATIONE:/adept/libs/curl-7.49.1/lib/libcurl.dll)
file(GLOBCURL_LIBRARYE:/adept/libs/curl-7.49.1/lib/libcurl.a)
file(GLOBCURL_DEBUG_LIBRARYE:/adept/libs/curl-7.49.1/lib/libcurl.a)
set_property(TARGETcurlPROPERTYIMPORTED_LOCATION_RELEAES${CURL_LIBRARY})
set_property(TARGETcurlPROPERTYIMPORTED_LOCATION_DEBUG${CURL_DEBUG_LIBRARY})
FIND_PACKAGE(CURLREQUIRED)
 
endif(WIN32)
 
add_definitions(-DCURL_STATICLIB)
set(CURL_STATICLIBtrue)
set(BUILD_CURL_EXEfalse)
 
#add_subdirectory(./lib)
#set(TARGET_NAME"curltest3")
#set(LIBCURL_DIR${PROJECT_SOURCE_DIR}/dep/curl)
 
#aux_source_directory(srcSRC_LIST)
#add_executable(${TARGET_NAME}${SRC_LIST})
 
#find_path(LIBCURL_INCLUDE_DIRcurl/curl.hHINTS${LIBCURL_DIR}/include)
#include_directories(${LIBCURL_INCLUDE_DIR})
 
#add_dependencies(${TARGET_NAME}libcurl)
 
#set(LIBS${LIBS}ws2_32)
#set(LIBS${LIBS}iphlpapi)
#set(LIBS${LIBS}libcurl)
 
 
 
add_executable(${PROJECT_NAME}${SRC_LIST})
target_link_libraries(${PROJECT_NAME}curl)

E:\adept\libs\curl-7.49.1\lib;E:\adept\libs\curl-7.49.1\include;C:\lib\Perl64\site\bin;C:\lib\Perl64\bin;E:\adept\Qt5.6.0\Tools\mingw492_32\bin;E:\adept\Projects\wxWidgets-3.1.0\lib\gcc_lib;C:\Program Files (x86)\Poedit;C:\Program Files\CMake\bin;E:\adept\Projects\wxWidgets-3.1.0\lib\vc_dll;E:\adept\Projects\wxWidgets-3.1.0;C:\Program Files (x86)\Poedit\GettextTools\bin;E:\adept\Qt\4.8.1\include\QtGui;E:\adept\Qt\mingw-4.4.0\bin;E:\adept\Qt\qtcreator-4.0.0\bin;E:\adept\Qt5.6.0\5.6\mingw49_32\bin;E:\adept\Qt5.6.0\Tools\mingw492_32\bin;E:\adept\Qt\4.8.1\bin;C:\ProgramData\Oracle\Java\javapath;C:\lib\Python27\32\;C:\lib\Python27\32\Scripts;C:\lib\Python27\;C:\lib\Python27\Scripts;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files\TortoiseHg\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files (x86)\Skype\Phone\;C:\Program Files\Common Files\Autodesk Shared\;C:\Program Files (x86)\Autodesk\Backburner\;C:\Program Files (x86)\CMake\bin;C:\Program Files\Git\cmd;C:\Program Files (x86)\Intel\OpenCL SDK\2.0\bin\x86;C:\Program Files (x86)\Intel\OpenCL SDK\2.0\bin\x64;C:\OpenCV-3.1.0\opencv\build\x64\c12\bin;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files\Microsoft SQL Server\Client SDK\ODBC\110\Tools\Binn\;C:\Program Files (x86)\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\DTS\Binn\;C:\Program Files (x86)\Microsoft SQL Server\120\Tools\Binn\ManagementStudio\;C:\Program Files (x86)\Microsoft SQL Server\120\DTS\Binn;