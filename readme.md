Hello!
For my project I chose 3 different json libraries: Nlohmann, Jsoncpp and Simd.

To change it should only require to change the cached variable JSON_LIBRARY inside CMakePresets.json, although I encountered myself the bug explained in this post:
https://github.com/microsoft/vscode-cmake-tools/issues/2952
Essentially CMake stop registering changes to the file after the first update. To solve the issue, I added an additional line to uncomment (in CMakeLists.txt) that will force the cached variable to the desired library.
Either test if CMakePresets.json works or directly use the force cache CMake directive.

Once the CMake builds, it will fetch the REQUESTED LIBRARY ONLY and it will link it to the project. Additionally, precompiled definitions get added to the project to statically switch implementation in the code.

The library folder contains the sub-CMakeLists.txt that imports the json library as well as my JsonParser interface.
The program folder, containing the main.cpp, doesn't have any preprocessor definitions and remains the same regardless of the CMake configuration.

The interface works as a wrapper for the json parsers. Every parser has an operator[] and getter methods, but they might work differently. My interface provides passthrough methods that safeguard and abstract the specific implementations of those.
JsonParser, the interface wrapper class, when it must returns a reference to a specific json construction (example: nlohmann::json type through the operator[]), it instead returns a new object to self that references the json construction (the copies share a shared_ptr to the main resource loaded in memory, making them very light weight).

The implementation is very flexible. Nlohmann json uses a single data object, which means that the JsonParser interface will only use references; if another library, like simd json, would instead use delegate objects that act themselves as references to the main binary, the Interface will instead create copies of them.