# How to Run the Program

## Build
> [!Note]  
> This setup guide assumes that you are in the `Siemens-Assessment-2024` directory.

#### 1. Go to the Assignment 2 Folder
```
cd .\Assignment_2
```

#### 2. Configure CMAKE and Update the Submodules
```
cmake -S . -B build
```

#### 3. Build the Testing Files
```
cmake --build build -j 12
```

#### 4. Build the Main Program
```
g++ ./src/main.cpp -o ./bin/main
```

## Run

#### 1. Run `PacketValidator` Tests
```
ctest -C Debug --test-dir build --output-on-failure -j12
```

#### 2. Run the Main Program
```
./bin/main
```