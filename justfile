format:
    find . -type f -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i
build:
    cd build && cmake -DCMAKE_BUILD_TYPE=Release .. -GNinja && ninja -j20 && cd ..
debug:
    cd build && cmake -DCMAKE_BUILD_TYPE=Debug .. -GNinja && ninja -j20 && cd ..
compile:
    cd build && cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .. -GNinja && ninja && cd ..