### Test Case Documentation

- This documentation lists all test cases used to test the `Server` and `Client` classes, and the input validation function in the main program.

## Table of Contents for Test Cases
#### TestServerOptions Tests
  1. **[test_normal_option](#1-test_normal_option)**
  2. **[test_empty_options](#2-test_empty_options)**
  3. **[test_empty_args](#3-test_empty_args)**
  4. **[test_duplicate_options](#4-test_duplicate_options)**
  5. **[test_special_char_options](#5-test_special_char_options)**

#### TestClient Tests
  1. **[test_empty_configureServer_master](#1-test_empty_configureServer_master)**
  2. **[test_empty_configureServer](#2-test_empty_configureServer)**
  3. **[test_configureServer_master](#3-test_configureServer_master)**
  4. **[test_valid_configureServer_client](#4-test_valid_configureServer_client)**
  5. **[test_valid_configureServer_client_with_empty_master](#5-test_valid_configureServer_client_with_empty_master)**
  6. **[test_invalid_configureServer_client](#6-test_invalid_configureServer_client)**
  7. **[test_invalid_options_type](#7-test_invalid_options_type)**
  8. **[test_invalid_options_size](#8-test_invalid_options_size)**
  9. **[test_invalid_options_content](#9-test_invalid_options_content)**

#### TestServer Tests
  1. **[test_invalid_setup_size](#1-test_initial_state)**
  2. **[test_initial_state](#2-test_initial_state)**
  3. **[test_configure_valid_tc_master](#3-test_configure_valid_tc_master)**
  4. **[test_configure_valid_tc_client](#4-test_configure_valid_tc_client)**
  5. **[test_configure_valid_tc_client_for_empty_master](#5-test_configure_valid_tc_client_for_empty_master)**
  6. **[test_configure_invalid_tc](#6-test_configure_invalid_tc)**
  7. **[test_configure_all_true](#7-test_configure_all_true)**
  8. **[test_configure_all_none](#8-test_configure_all_none)**
  9. **[test_configure_mixed](#9-test_configure_mixed)**
  10. **[test_configure_invalid_options_size](#10-test_configure_invalid_options_size)**

## TestServerOptions Class

The `TestServerOptions` class contains unit tests for the `validate_server_options` function.

### 1. test_normal_option
**Description:** 
Tests the validation with normal options.

**Input:**
```py
args = ["test_case.csv", "BufferData"]
args1 = ["test_case.csv", "BufferData", "TimeOut"]
args2 = ["test_case.csv", "BufferData", "TimeOut", "PacketLoss"]
```

**Expected Result:**
 - The system options list provided by the user.

### 2. test_empty_options
**Description:** 
Tests the validation with empty options.

**Input:**
```py
args = ["test_case.csv"]
```

**Expected Result:**
 - Raises a `ValueError`due to the invalid logic.

### 3. test_empty_args
**Description:** 
Tests the validation with empty arguments.

**Input:**
```py
args = []
```

**Expected Result:**
 - Raises a `ValueError`due to the invalid logic.

### 4. test_duplicate_options
**Description:** 
Tests the validation with duplicate options.

**Input:**
```py
args = ["test_case.csv", "BufferData", "TimeOut", "BufferData"]
```

**Expected Result:**
 - Raises a `ValueError`due to the invalid logic.

### 5. test_special_char_options
**Description:** 
Tests the validation with options containing special characters.

**Input:**
```py
args = ["test_case.csv", "BufferData", "Ti/meOut", "P*acket", "Sp ace"]
```

**Expected Result:**
 - Raises a `ValueError`due to the invalid input.
  

----
## TestClient Class

The `TestClient` class contains unit tests for the `Client` class, specifically focusing on the `configureServer` method.

### 1. test_empty_configureServer_master
**Description:** 
Tests the configuration by the master with all `None` options.

**Input:**
```py
master = Client(is_master=True)
options = [None, None, None]
```

**Expected Result:**
 - The server options are set to `[True, True, True]` and the test case is valid.

### 2. test_empty_configureServer
**Description:** 
Tests the configuration by a non-master client with all `None` options after the master has configured the server with all `None`.

**Input:**
```py
master = Client(is_master=True)
master.configureServer([None, None, None])

client = Client(is_master=False)
options = [None, None, None]
```

**Expected Result:**
 - The server options remain `[True, True, True]` and the test case is valid.

### 3. test_configureServer_master
**Description:** 
Tests the configuration by the master with mixed options.

**Input:**
```py
master = Client(is_master=True)
options = [True, False, None]
```

**Expected Result:**
 - The server options are set to `[True, False, True]` and the test case is valid.

### 4. test_valid_configureServer_client
**Description:** 
Tests the valid configuration by a non-master client after the master has configured the server.

**Input:**
```py
master = Client(is_master=True)
master.configureServer([True, False, None])

client = Client(is_master=False)
options = [True, None, None]
```

**Expected Result:**
 - The server options remain `[True, False, True]` and the test case is valid.

### 5. test_valid_configureServer_client_with_empty_master
**Description:** 
Tests the valid configuration by a non-master client with options `[True, None, None]` when the master hasn't configured the server.

> [!Note]
> This case is an assumption to an edge case, which is explained in more details in the Assessment's Report.

**Input:**
```py
master = Client(is_master=True)
master.configureServer([None, None, None])

client = Client(is_master=False)
options = [True, None, None]
```

**Expected Result:**
 - The server options remain `[True, True, True]` and the test case is valid.

### 6. test_invalid_configureServer_client
**Description:** 
Tests the invalid configuration by a non-master client after the master has configured the server.

**Input:**
```py
master = Client(is_master=True)
master.configureServer([True, False, None])

client = Client(is_master=False)
options = [False, None, None]
```

**Expected Result:**
 - The server options are set to `[None, None, None]` and the test case is invalid.

### 7. test_invalid_options_type
**Description:** 
Tests the configuration with an invalid options type.

**Input:**
```py
options = "invalid"
```

**Expected Result:**
 - Raises a `TypeError` because the input is not a list.

### 8. test_invalid_options_size
**Description:** 
Tests the configuration with an invalid options size.

**Input:**
```py
server = Server(system_option_size=3)
options = [True, False]
```

**Expected Result:**
 - Raises a `ValueError` because the input length is not matching the server's expected size.

### 9. test_invalid_options_content
**Description:** 
Tests the configuration with invalid options content.

**Input:**
```py
options = [True, "invalid", None]
```

**Expected Result:**
 - Raises a `TypeError` because options list contains non-boolean and non-None values.

## TestServer Class

The `TestServer` class contains unit tests for the `Server` class, specifically focusing on the `configure` method.

### 1. test_invalid_setup_size
**Description:** 
Tests the setup of the server with non-positive number of system options.

**Input:**
```py
system_option_size = 0
```

**Expected Result:**
 - Raises a `ValueError`.

### 2. test_initial_state
**Description:** 
Tests the initial state of the server.

**Input:**
```py
self.server = Server(system_option_size=3)
```

**Expected Result:**
 - The server options are `[True, True, True]` and the test case is valid.

### 3. test_configure_valid_tc_master
**Description:** 
Tests the valid configuration by the master with mixed options.

**Input:**
```py
options = [None, False, True]
is_master = True
```

**Expected Result:**
 - The server options are set to `[True, False, True]` and the test case is valid.

### 4. test_configure_valid_tc_client
**Description:** 
Tests the valid configuration by a non-master client after the master has configured the server.

**Input:**
```py
server.configure([None, False, True], is_master=True)
options = [None, False, True]
is_master = False
```

**Expected Result:**
 - The server options remain `[True, False, True]` and the test case is valid.

### 5. test_configure_valid_tc_client_for_empty_master
**Description:** 
Tests the valid configuration by a non-master client with options when the master hasn't configured the server.

> [!Note]
> This case is an assumption to an edge case, which is explained in more details in the Assessment's Report.

**Input:**
```py
server.configure([None, None, None], is_master=True)
options = [None, True, True]
is_master = False
```

**Expected Result:**
 - The server options remain `[True, True, True]` and the test case is valid.

### 6. test_configure_invalid_tc
**Description:** 
Tests the invalid configuration by a non-master client with options after the master has configured the server.

**Input:**
```py
server.configure([None, False, True], is_master=True)
options = [None, True, None]
is_master = False
```

**Expected Result:**
 - The server options are set to `[None, None, None]` and the test case is invalid.

### 7. test_configure_all_true
**Description:** 
Tests the configuration with all options set to `True`.

**Input:**
```py
options = [True, True, True]
is_master = True
```

**Expected Result:**
 - The server options are set to `[True, True, True]` and the test case is valid.

### 8. test_configure_all_none
**Description:** 
Tests the configuration with all options set to `None`.

**Input:**
```py
options = [None, None, None]
is_master = True
```

**Expected Result:**
 - The server options remain `[True, True, True]` as their default value and the test case is valid.

### 9. test_configure_mixed
**Description:** 
Tests the configuration with mixed options.

**Input:**
```py
options = [True, None, False]
is_master = True
```

**Expected Result:**
 - The server options are set to `[True, True, False]` and the test case is valid.

### 10. test_configure_invalid_options_size
**Description:** 
Tests the configuration with an invalid options size.

**Input:**
```py
server = Server(system_option_size=3)
options = [True, False]
```

**Expected Result:**
 - Raises a `ValueError` because the input length is not matching the server's expected size.