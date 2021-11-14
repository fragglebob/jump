project(Jump)

# ======================= ofxCMake Vers. 0.1 =============
#  PUT THIS FILE INTO YOUR OPENFRAMEWORKS PROJECT FOLDER

# ========================================================
# ===================== CMake Settings ===================
# ========================================================
cmake_minimum_required( VERSION 3.3 )
cmake_policy( SET CMP0057 NEW)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 14)

# ========================================================
# ===================== User Settings ====================
# ========================================================
# ---------------------- App name  -----------------------
set( APP_NAME   ofApp )

# ------------------------ OF Path -----------------------
# --- If outside the OF structure, set an absolute OF path
set( OF_DIRECTORY_BY_USER "../../../of" )
get_filename_component( OF_DIRECTORY_ABSOLUTE ${OF_DIRECTORY_BY_USER} ABSOLUTE)

# --------------------- Source Files ---------------------


include_directories(
        "src"
        "src/PostPasses"
)

set( ${APP_NAME}_SOURCE_FILES
        src/main.cpp
        src/ofxBeat.cpp
        src/fft.cpp
        src/ofApp.cpp
        src/ofSol.cpp

        src/PostPasses/RenderPass.cpp

        src/myPostProcessing.cpp
        src/MidiMix.cpp

        src/PostPasses/RGBShiftPass.cpp
        src/PostPasses/MyKidoPass.cpp
        src/PostPasses/SliceWavePass.cpp
        src/PostPasses/GridShiftPass.cpp
        src/PostPasses/FeedbackPass.cpp
        src/PostPasses/ConvolutionPass.cpp
        src/PostPasses/BloomPass.cpp
        src/PostPasses/AsciiPass.cpp
        src/PostPasses/MatrixPass.cpp

        src/ofxAubioBlock.cpp
        src/ofxAubioBeat.cpp
        )

find_package(Lua51 REQUIRED)
include_directories(/usr/local/include ${LUA_INCLUDE_DIR})

# find_package(aubio REQUIRED)
# include_directories(/usr/local/include ${AUBIO_INCLUDE_DIR})


if( APPLE ) # Apple is a Unix, too. So dont ask only first UNIX
find_library(audio_lib aubio)
        set(EXTRA_LIBS 
                ${audio_lib}
                ${LUA_LIBRARIES}
        )
elseif( UNIX )
        set(EXTRA_LIBS 
                asound 
                fftw3
                audio
                ${LUA_LIBRARIES}
        )
        
else()
    message( FATAL_ERROR "Operating System not supported" )
endif()



set(OFX_ADDONS_ACTIVE ofxMidi ofxXmlSettings)

include(cmake/ofxMidi.cmake)
include(cmake/ofxXmlSettings.cmake)

# =========================================================================
# ============================== OpenFrameworks ===========================
# =========================================================================
# include( ${OF_DIRECTORY_BY_USER}/addons/ofxCMake/modules/main.cmake )
# =========================================================================

include(cmake/openFrameworks.cmake)

if( APPLE ) # Apple is a Unix, too. So dont ask only first UNIX
        include(cmake/openFrameworksApple.cmake)
elseif( UNIX )
        include(cmake/openFrameworksLinux.cmake)
else()
    message( FATAL_ERROR "Operating System not supported" )
endif()

include(cmake/config.cmake)

if( APPLE ) # Apple is a Unix, too. So dont ask only first UNIX
        include(cmake/configApple.cmake)
elseif( UNIX )
        include(cmake/configLinux.cmake)
else()
    message( FATAL_ERROR "Operating System not supported" )
endif()


# ============================================================================
# ------------------------------- APP CONFIGURATION --------------------------
# ============================================================================
add_dependencies( ${APP_NAME} of_shared )
set_target_properties( ${APP_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY    ${PROJECT_SOURCE_DIR}/bin
)