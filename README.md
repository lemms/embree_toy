# embree_toy
A toy embree3 ray tracer

# Build instructions

1. Make a build directory

'''
mkdir build
cd build
'''

2. Run conan

'''
conan install ../embree_toy
'''

3. Run CMake

'''
cmake -DCMAKE_BUILD_TYPE=Release ../embree_toy
'''
