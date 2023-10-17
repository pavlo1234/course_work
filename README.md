# course_work

- Server project:
   - Requires: CMake, Conan (Python, pip)
   - Building steps:
        1. ../server> conan profile detect --force --- creating Conan default profile (setting OS, build architecture and compiler setting defaut parameters, may be changed in ../.conan2/profiles/default)
        2. ../server> conan install . --output-folder=build --build=missing --- downloading dependencies (libraries, frameworks, packages) and generating required files
        3. ../server> cmake . -DCMAKE_TOOLCHAIN_FILE="build/conan_toolchain.cmake" --- generating CMake cache
        4. ../server> cmake --build . --- generating executables
