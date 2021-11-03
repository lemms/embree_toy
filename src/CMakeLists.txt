add_executable(embree_toy
    embree_toy.cc
    main.cc
)

set_property(
    TARGET embree_toy
    APPEND PROPERTY PUBLIC_HEADER
        embree_toy.h
)

target_compile_definitions(
    embree_toy
    PRIVATE
        DEBUG_LOGGING=1
)

target_compile_features(embree_toy PUBLIC cxx_std_20)

target_link_libraries(embree_toy
    PUBLIC
        ${CONAN_LIBS}
)
