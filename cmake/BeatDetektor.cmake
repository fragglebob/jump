file(GLOB_RECURSE BEAT_DETEKTOR_CPP
        "libs/beatdetektor/BeatDetektor.cpp"
        )



include_directories(libs/beatdetektor)


add_library(BeatDetektor STATIC ${BEAT_DETEKTOR_CPP})
target_compile_definitions(BeatDetektor PUBLIC DEVTEST_BUILD)
