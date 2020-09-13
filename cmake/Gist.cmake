


file(GLOB GIST_CPP
        "libs/Gist/*.cpp"
        "libs/Gist/core/*.cpp"
        "libs/Gist/pitch/*.cpp"
        "libs/Gist/fft/WindowFunctions.cpp"
        "libs/Gist/mfcc/*.cpp"
        "libs/Gist/onset-detection-functions/*.cpp"
        )


include_directories(libs/Gist)
include_directories(libs/Gist/core)
include_directories(libs/Gist/ftt)
include_directories(libs/Gist/mfcc)
include_directories(libs/Gist/pitch)
include_directories(libs/Gist/onset-detection-functions)

add_library(Gist STATIC ${GIST_CPP})



target_compile_definitions(Gist PUBLIC USE_KISS_FFT)