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

![image](https://github.com/pavlo1234/course_work/assets/38382532/773c8666-5093-463d-92ed-ac6a9167c401)

![image](https://github.com/pavlo1234/course_work/assets/38382532/e5b492e9-9e69-4d07-a8d9-71d9d4c94caf)

![image](https://github.com/pavlo1234/course_work/assets/38382532/5b37adf2-a6c1-4be0-857b-6b84d195e1ed)


