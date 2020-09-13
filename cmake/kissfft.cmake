file(GLOB_RECURSE KISS_FFT_C
        "libs/kiss_fft130/kiss_fft.c"
        )



include_directories(libs/kiss_fft130)

add_library(kiss_fft STATIC ${KISS_FFT_C})
