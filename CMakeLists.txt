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
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

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
set( ${APP_NAME}_SOURCE_FILES
        src/main.cpp
        src/ofxBeat.cpp
        src/fft.cpp
        src/ofApp.cpp
        src/ofSol.cpp
        src/myPostProcessing.cpp
        src/MidiMix.cpp
        src/PostPasses/MyKidoPass.cpp
        src/PostPasses/SliceWavePass.cpp
        src/PostPasses/GridShiftPass.cpp
        )

find_package(Lua51 REQUIRED)
include_directories(/usr/local/include ${LUA_INCLUDE_DIR})
set(EXTRA_LIBS asound ${LUA_LIBRARIES})

set(OFX_ADDONS_ACTIVE ofxMidi ofxPostProcessing Gist kiss_fft BeatDetektor)

include(cmake/ofxMidi.cmake)
include(cmake/ofxPostProcessing.cmake)


include(cmake/Gist.cmake)
include(cmake/kissfft.cmake)
include(cmake/BeatDetektor.cmake)

# =========================================================================
# ============================== OpenFrameworks ===========================
# =========================================================================
# include( ${OF_DIRECTORY_BY_USER}/addons/ofxCMake/modules/main.cmake )
# =========================================================================

include(cmake/openFrameworks.cmake)

if( UNIX )
        include(cmake/openFrameworksLinux.cmake)
else()
    message( FATAL_ERROR "Operating System not supported" )
endif()


include_directories(${OF_CORE_HEADERS})

# ============================================================================
# ----------------------------- Setting Libraries ----------------------------
add_library( core       OBJECT ${OF_SOURCE_FILES} )
add_library( of_static     STATIC $<TARGET_OBJECTS:core> )
add_library( of_shared  SHARED $<TARGET_OBJECTS:core> )

# -------------------------------- Linking --------------------------------
target_link_libraries(  of_static ${OF_CORE_LIBS} )
target_link_libraries(  of_shared ${OF_CORE_LIBS} )

# -------------------------------- Properties --------------------------------
set_target_properties( of_static PROPERTIES OUTPUT_NAME openFrameworksStatic)
set_target_properties( of_shared PROPERTIES OUTPUT_NAME openFrameworksShared)









# ============================================================================
# ------------------------------ Compiler Flags ------------------------------
set_source_files_properties( ${OF_SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pthread")
set_source_files_properties( ${${APP_NAME}_SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pthread")

# ============================================================================
# ------------------------------ Compile and Link ----------------------------
add_executable( ${APP_NAME} ${${APP_NAME}_SOURCE_FILES} )


set_target_properties( of_shared PROPERTIES POSITION_INDEPENDENT_CODE TRUE )

set_target_properties( of_shared
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
        )

set_target_properties( of_static PROPERTIES POSITION_INDEPENDENT_CODE TRUE )

set_target_properties( of_static
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
        )


target_link_libraries( ${APP_NAME} $<TARGET_FILE:of_static> ${OF_CORE_LIBS} ${OFX_ADDONS_ACTIVE} ${EXTRA_LIBS} )

set_target_properties( ${APP_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY    ${PROJECT_SOURCE_DIR}/bin
        )