```
conan install conanfile.py --build=missing
cmake --preset=conan-release
cmake --build --preset=conan-release
./build/Release/boost-asio-learn

conan install conanfile.py --build=missing --settings=build_type=Debug
cmake --preset=conan-debug
cmake --build --preset=conan-debug
./build/Debug/boost-asio-learn
```