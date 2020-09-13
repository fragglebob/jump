file(GLOB GIST_CPP
        "libs/BTrack/*.cpp"
    )


include_directories(libs/BTrack)
add_library(BTrack STATIC ${GIST_CPP})
target_compile_definitions(BTrack PUBLIC USE_KISS_FFT)