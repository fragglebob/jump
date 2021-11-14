# ============================================================================
# ------------------------------ Compiler Flags ------------------------------
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_C_FLAGS "") # -x objective-c

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "-std=c++14 -stdlib=libc++ -D__MACOSX_CORE__") # Removed "-stdlib=libstdc++
set_source_files_properties( ${OF_SOURCE_FILES} PROPERTIES COMPILE_FLAGS "-x objective-c++" )

#set(CMAKE_OSX_ARCHITECTURES i386)
set(CMAKE_OSX_ARCHITECTURES x86_64)
add_compile_options(-Wno-deprecated-declarations)

# add_compile_definitions(OF_USING_STD_FS)

# ============================================================================
# ------------------------------ Compile and Link ----------------------------
add_executable( ${APP_NAME} MACOSX_BUNDLE ${${APP_NAME}_SOURCE_FILES} )

target_link_libraries(  ${APP_NAME}
                        $<TARGET_FILE:of_shared>
                        ${opengl_lib}               # TODO Why is this needed here?
                        ${OFX_ADDONS_ACTIVE}
                        ${EXTRA_LIBS}
)

# ============================================================================
ADD_CUSTOM_COMMAND( TARGET ${APP_NAME}
        POST_BUILD
        COMMAND ${CMAKE_INSTALL_NAME_TOOL}
        ARGS -change "@rpath/libopenFrameworks.dylib" "@loader_path/../Frameworks/libopenFrameworks.dylib" $<TARGET_FILE:${APP_NAME}>
)

# TODO Explain the excecutable bindings
ADD_CUSTOM_COMMAND( TARGET of_shared
        POST_BUILD
        COMMAND ${CMAKE_INSTALL_NAME_TOOL}
        ARGS -change ./libfmod.dylib "@loader_path/libfmod.dylib" $<TARGET_FILE:of_shared>
)

ADD_CUSTOM_COMMAND( TARGET of_shared
        POST_BUILD
        COMMAND /bin/cp
        ARGS ${LIB_FMOD} ${PROJECT_SOURCE_DIR}/bin/${APP_NAME}.app/Contents/Frameworks
)

ADD_CUSTOM_COMMAND( TARGET ${APP_NAME}
        POST_BUILD
        COMMAND /bin/cp
        ARGS ../src/osx/Info.plist ${PROJECT_SOURCE_DIR}/bin/${APP_NAME}.app/Contents
)   