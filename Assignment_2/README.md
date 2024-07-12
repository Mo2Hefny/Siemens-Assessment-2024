# Get googletest latest change
git submodule update --init --recursive
cmake -S . -B build
cmake --build build -j 12


# run
ctest -C Debug --test-dir build --output-on-failure -j12