# Assignment 2 Report

## Table of Content
1. **[Assumptions](#assumptions)**
2. **[Program Input](#program-input)**
3. **[Program output](#program-output)**
4. **[Code Structure](#program-output)**

## Assumptions

- Since the last module `M` isn't given as a Program input, it is indicated as the largest module number in the given module numbers array.

## Program Input

### According to the Assignment

- Number of packets.
- Module number of each packet.

### In the Application
- The input is provided via the console.
- In any case where the user enters invalid values (characters, strings, etc), the program will throw an `invalid_argument` error and prompt the user to try again without restarting.
- Any float number is floored to the nearest integer.

## Program Output

### According to the Assignment

- CSV file in the following format.

  | PacketID | ModuleNumber | ValidModule |
  | -------- | ------------ | ----------- |
  | 1        | 1            | Yes         |
  | 2        | 3            | No          |
  | 3        | 4            | Yes         |
  | 4        | 4            | Yes         |

### In the Application
- The CSV file is saved by calling the **saveValidation** method of the `PacketValidator` class.
- The CSV file is automatically saved in the `src/output` folder.

## Code Structure

### 1. Main Program `main.cpp`

1. The main program prompts the user to input the number of packets and their module numbers.

2. The program creates an object from the `PacketValidator` class to validate the module numbers and save this data to a CSV file.

#### Functions:

- **readInteger**: Reads and returns an integer or rounds a float from the console and throws an error if invalid input was given, and then tries again.

### 2. PacketValidator Class `packet.h`

1. The `PacketValidator` class is designed to validate packets based on their assigned module numbers.

2. The `PacketValidator` class is designed to save the validation result to a CSV file in the `src\output` folder.

#### Methods:

- **setPacketModules**: Sets the packet modules for validation and initializes the validation vector.
- **evaluatePacketModule**: Evaluates if a packet module number is valid based on the previous module number.
- **validatePackets**: Validates all packets based on the packets' assigned module numbers.
- **getModuleSize**: Retrieves the largest module number in the cycle, indicating the last module `M`.
- **getValidation**: Retrieves the validation results of each packet.
- **saveValidation**: Saves the validation results to a CSV file.

### 3. Unit Test `test_packet.cpp`

1. The `Unit Test` operates using `googletest`.

2. The `Unit Test` is intended for testing the `PacketValidator` class.

#### Tests:
For more information about the testcases used to test the `PacketValidator`, check out the **[TEST.md document](TESTS.md)**.