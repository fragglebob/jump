# ============================================================================
# ---------------------------- Source Files ----------------------------------
list( APPEND OF_SOURCE_FILES
        ${OF_DIRECTORY_ABSOLUTE}/libs/openFrameworks/video/ofGstUtils.cpp
        ${OF_DIRECTORY_ABSOLUTE}/libs/openFrameworks/video/ofGstVideoGrabber.cpp
        ${OF_DIRECTORY_ABSOLUTE}/libs/openFrameworks/video/ofGstVideoPlayer.cpp
        ${OF_DIRECTORY_ABSOLUTE}/libs/openFrameworks/sound/ofRtAudioSoundStream.cpp
        )

# ============================================================================
# --------------------------- Include Folders --------------------------------

# ------------------ Putting the includes into one list ----------------------
list( APPEND OF_CORE_HEADERS ${OF_DIRECTORY_ABSOLUTE}/libs/kiss/include)

# ============================================================================
# ------------------------------ Libraries -----------------------------------

# ---- shared
set( LIB_FMODEX ${OF_DIRECTORY_ABSOLUTE}/libs/fmodex/lib/linux64/libfmodex.so )

set( PLATFORM_STATIC_LIBS
#        ${OF_DIRECTORY_ABSOLUTE}/libs/glfw/lib/linux64/libglfw3.a
        ${OF_DIRECTORY_ABSOLUTE}/libs/kiss/lib/linux64/libkiss.a
#        ${OF_DIRECTORY_ABSOLUTE}/libs/poco/lib/linux64/libPocoCrypto.a
#        ${OF_DIRECTORY_ABSOLUTE}/libs/poco/lib/linux64/libPocoFoundation.a
#        ${OF_DIRECTORY_ABSOLUTE}/libs/poco/lib/linux64/libPocoNet.a
#        ${OF_DIRECTORY_ABSOLUTE}/libs/poco/lib/linux64/libPocoNetSSL.a
#        ${OF_DIRECTORY_ABSOLUTE}/libs/poco/lib/linux64/libPocoUtil.a
#        ${OF_DIRECTORY_ABSOLUTE}/libs/poco/lib/linux64/libPocoXML.a
#        ${OF_DIRECTORY_ABSOLUTE}/libs/poco/lib/linux64/libPocoJSON.a
        ${OF_DIRECTORY_ABSOLUTE}/libs/tess2/lib/linux64/libtess2.a
        )

# ============================================================================
# ----------------------------- System Frameworks ----------------------------
set(CMAKE_MODULE_PATH
  "${CMAKE_MODULE_PATH}"
  "${CMAKE_CURRENT_LIST_DIR}")

find_package(PkgConfig REQUIRED)
find_package(GStreamer REQUIRED)
find_package(Boost REQUIRED system filesystem)
find_package(Threads REQUIRED)

PKG_SEARCH_MODULE( ALSA "REQUIRED" alsa )
PKG_SEARCH_MODULE( CAIRO "REQUIRED" cairo )
PKG_SEARCH_MODULE( RTAUDIO "REQUIRED" rtaudio )

include_directories( ${CAIRO_INCLUDE_DIRS} )
include_directories( ${OPENAL_INCLUDE_DIRS} )
include_directories( ${ALSA_INCLUDE_DIRS} )
include_directories( ${GSTREAMER_APP_INCLUDE_DIRS} )
include_directories( ${GSTREAMER_BASE_INCLUDE_DIRS} )
include_directories( ${GSTREAMER_VIDEO_INCLUDE_DIRS} )
include_directories( ${RTAUDIO_INCLUDE_DIRS} )


set(PLATFORM_LIBRARIES z
        Threads::Threads
        gstapp-1.0
        gstvideo-1.0
        gstbase-1.0
        gstreamer-1.0
        udev
        fontconfig
        freetype
        sndfile
        openal
        curl
        glfw
        rtaudio
        pulse-simple
        pulse
        asound
        GLEW
        GLU
        GL
        gtk-3
        gdk-3
        pangocairo-1.0
        pango-1.0
        atk-1.0
        cairo-gobject
        cairo
        gdk_pixbuf-2.0
        gio-2.0
        gobject-2.0
        glib-2.0
        mpg123
        glut
        X11
        Xrandr
        Xxf86vm
        Xi
        Xcursor
        dl
        freeimage
        boost_filesystem
        boost_system
        pugixml
        uriparser
        Xinerama
)

set(PLATFORM_SHARED_LIBRARIES ${LIB_FMODEX})
set(OF_CORE_LIBS ${PLATFORM_LIBRARIES} ${PLATFORM_STATIC_LIBS} ${PLATFORM_SHARED_LIBRARIES})
