# Test Case Documentation for `PacketValidator` Class

- This documentation lists all test cases used to test the `PacketValidator` class. 
- Each test case is designed to verify the correct behavior of the class under different scenarios.

## Table of Contents for Test Cases
1. [AccumulativeValues](#1-accumulativevalues)
2. [EqualValues](#2-equalvalues)
3. [NegativeValues](#3-negativevalues)
4. [MixValues](#4-mixvalues)
5. [ZeroValues](#5-zerovalues)
6. [UnorderedPositiveValues](#6-unorderedpositivevalues)
7. [UnorderedPositiveValuesWithDups](#7-unorderedpositivevalueswithdups)
8. [FullCycleVector](#8-fullcyclevector)
9. [EmptyVector](#9-emptyvector)
10. [MaxValues](#10-maxvalues)
11. [MaxValuesCycle](#11-maxvaluescycle)
12. [EnormousValues](#12-enormousvalues)

## Test Cases

### 1. AccumulativeValues

**Description**: 
Test the `PacketValidator` with a sequence of positive increasing values.

**Input**: 
```cpp
vector<int> modules = {1, 2, 3, 4, 5};
```

**Expected Output**:
- The last module number should be `5`.
- The size of the validation vector should match the size of the input vector.
- All validation results should be `true`.

### 2. EqualValues

**Description**: 
Test the `PacketValidator` with a sequence of equal positive values.

**Input**: 
```cpp
vector<int> modules = {1, 1, 1, 1, 1};
```

**Expected Output**:
- The last module number should be `1`.
- The size of the validation vector should match the size of the input vector.
- All validation results should be `true`.

### 3. NegativeValues

**Description**: 
Test the `PacketValidator` with a sequence of negative values.

**Input**: 
```cpp
vector<int> modules = {-1, -2, -3, -4, -5};
```

**Expected Output**:
- An `invalid_argument` exception should be thrown when setting the packet modules.
- The last module number should be set to `0` since the arguments are invalid.
- The validation vector should be empty.

### 4. MixValues

**Description**: 
Test the `PacketValidator` with a mix of positive and negative values.

**Input**: 
```cpp
vector<int> modules = {6, -2, 2, -1, 7};
```

**Expected Output**:
- An `invalid_argument` exception should be thrown when setting the packet modules.
- The last module number should be `0` since the arguments are invalid.
- The validation vector should be empty.

### 5. ZeroValues

**Description**: 
Test the `PacketValidator` with a sequence of zero values.

**Input**: 
```cpp
vector<int> modules = {0, 0, 0, 0, 0};
```

**Expected Output**:
- An `invalid_argument` exception should be thrown when setting the packet modules.
- The last module number should be `0` since the arguments are invalid.
- The validation vector should be empty.

### 6. UnorderedPositiveValues

**Description**: 
Test the `PacketValidator` with unordered positive values.

**Input**: 
```cpp
vector<int> modules = {6, 1, 2, 3, 7, 2};
```

**Expected Output**:
- The size of the validation vector should match the size of the input vector.
- The last module number should be `7`.
- The validation results should be: `{true, false, true, true, false, false}`.

### 7. UnorderedPositiveValuesWithDups

**Description**: 
Test the `PacketValidator` with unordered positive values including duplicates.

**Input**: 
```cpp
vector<int> modules = {4, 4, 2, 1, 1};
```

**Expected Output**:
- The size of the validation vector should match the size of the input vector.
- The validation results should be: `{true, true, false, false, true}`.

### 8. FullCycleVector

**Description**: 
Test the `PacketValidator` with a vector that forms a full cycle from the last module number to the first module number.

**Input**: 
```cpp
vector<int> modules = {4, 5, 6, 1, 1};
```

**Expected Output**:
- The size of the validation vector should match the size of the input vector.
- All validation results should be `true`.

### 9. EmptyVector

**Description**: 
Test the `PacketValidator` with an empty vector.

**Input**: 
```cpp
vector<int> modules;
```

**Expected Output**:
- An `invalid_argument` exception should be thrown when setting the packet modules.
- The validation vector should be empty.

### 10. MaxValues

**Description**:
Test the PacketValidator with a sequence of maximum integer values.

**Input**: 

```cpp
vector<int> modules = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};
```

**Expected Output**:
- The last module number should be `INT_MAX`.
- The size of the validation vector should match the size of the input vector.
- All validation results should be `true`.

### 11. MaxValuesCycle

**Description**:
Test the PacketValidator with a mix of maximum integer values and small integers to check for overflowing.

**Input**: 

```cpp
vector<int> modules = {INT_MAX, INT_MAX, 1, 2};
```

**Expected Output**:
- The last module number should be `INT_MAX`.
- The size of the validation vector should match the size of the input vector.
- All validation results should be `true`.

### 12. EnormousValues

**Description**:
Test the PacketValidator with a mix of large integer values near the maximum integer limit.

**Input**: 

```cpp
vector<int> modules = {INT_MAX - 4, INT_MAX - 1, INT_MAX, INT_MAX};
```

**Expected Output**:
- The last module number should be `INT_MAX`.
- The size of the validation vector should match the size of the input vector.
- The validation results should be: {true, false, true, true}`.