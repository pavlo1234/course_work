# course_work

- Server project:
   - Requires: CMake, Conan (Python, pip)
   - Building steps:
        1. ../server> conan profile detect --force --- creating Conan default profile (setting OS, build architecture and compiler setting defaut parameters, may be changed in ../.conan2/profiles/default)
        2. ../server> conan install . --output-folder=build --build=missing --- downloading dependencies (libraries, frameworks, packages) and generating required files
        3. ../server> cmake . -DCMAKE_TOOLCHAIN_FILE="build/conan_toolchain.cmake" --- generating CMake cache
        4. ../server> cmake --build . --- generating executables
- Results:
![image](https://github.com/pavlo1234/course_work/assets/38382532/441540aa-7586-4b01-902d-171be23f0ec8)

![image](https://github.com/pavlo1234/course_work/assets/38382532/7a91025f-9f0e-44ba-9959-9cbfd82c560b)
![image](https://github.com/pavlo1234/course_work/assets/38382532/0e864f0e-7edf-4f85-bddc-97ea4ea5c050)

![Зображення1](https://github.com/pavlo1234/course_work/assets/38382532/af75c098-5fbb-42a4-9aec-5072a6682764)
![image](https://github.com/pavlo1234/course_work/assets/38382532/89891c2b-f753-4ce7-93fa-6886e14ecbec)

