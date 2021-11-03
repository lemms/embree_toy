// main.cc
// Copyright Laurence Emms 2021

// Executable for toy embree tracer

#include <iostream>

#include "embree_toy.h"

int main(int argc, char** argv) {
#if DEBUG_LOGGING
    std::cout << "Toy Embree Tracer" << std::endl;
#endif

    embree_toy::run_trace();

#if DEBUG_LOGGING
    std::cout << "End Toy Embree Tracer" << std::endl;
#endif
    return 0;
}
