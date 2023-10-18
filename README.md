# course_work

- Server project:
   - Requires: CMake, Conan 
   - Building steps:
        1. ../server> conan profile detect --force --- creating Conan default profile (setting OS, build architecture and compiler setting defaut parameters, may be changed in ../.conan2/profiles/default)
        2. ../server> conan install . --output-folder=build --build=missing --settings=build_type=(Debug\Release) --- downloading dependencies (libraries, frameworks, packages) and generating required files
        3. For Windows: ../server/build> cmake ..-DCMAKE_TOOLCHAIN_FILE="build/conan_toolchain.cmake" 
           For Linux: ../server/build> cmake .. -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=(Debug\Release) --- generating CMake cache
        4. ../server/build> cmake --build . --- generating executables
