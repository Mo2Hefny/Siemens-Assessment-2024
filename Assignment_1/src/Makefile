# Set the arguments to run the program
# Normal Options Case
ARGS1 = test_normal_input.csv BufferData TimeOut
# Normal Options Case 2
ARGS2 = test_one_input.csv BufferData
# Normal Options Case 3
ARGS3 = test_three_input.csv BufferData TimeOut PacketLoss
# No Options Case
ARGS4 = test_empty_input.csv
# No Args Case
ARGS5 = 
# Duplicate Options Case
ARGS6 = test_duplicate_input.csv BufferData TimeOut BufferData
# Special Characters Case
ARGS7 = test_special_char_input.csv BufferData Ti/meOut P*acket

# Detect the OS
ifeq ($(OS), Windows_NT)
    # Windows settings
    VENV = venv
    PYTHON = $(VENV)/Scripts/python.exe
    PIP = $(VENV)/Scripts/pip.exe
    TEST = $(VENV)/Scripts/pytest.exe
    PYTHON_CMD = python
    DEL = del /q /s
else
    # Unix settings
    VENV = venv
    PYTHON = $(VENV)/bin/python3
    PIP = $(VENV)/bin/pip3
    TEST = $(VENV)/bin/pytest
    PYTHON_CMD = python3
    DEL = rm -rf
endif

# Default target
.PHONY: all
all: install run

# Create virtual environment
$(VENV):
	$(PYTHON_CMD) -m venv $(VENV)

# Install dependencies
.PHONY: install
install: $(VENV)
	$(PIP) install -r requirements.txt

# Run tests
.PHONY: test
test: $(VENV) install
	$(TEST)

# Run the application
.PHONY: run
run: $(VENV) install
	$(PYTHON) app.py $(ARGS1)
	$(PYTHON) app.py $(ARGS2)
	$(PYTHON) app.py $(ARGS3)
	$(PYTHON) app.py $(ARGS4)
	$(PYTHON) app.py $(ARGS5)
	$(PYTHON) app.py $(ARGS6)
	$(PYTHON) app.py $(ARGS7)

# Clean the virtual environment
.PHONY: clean
clean:
	$(DEL) $(VENV)\Include
	$(DEL) $(VENV)\Lib
