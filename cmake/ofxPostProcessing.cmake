file( GLOB_RECURSE OFX_PP_CPP
        "${OF_DIRECTORY_ABSOLUTE}/addons/ofxPostProcessing/src/*.cpp"
        )

add_library(ofxPostProcessing
        STATIC
        ${OFX_PP_CPP}
        )

include_directories(
        "${OF_DIRECTORY_ABSOLUTE}/addons/ofxPostProcessing/src"
)

include_directories(
        "src/PostPasses"
)