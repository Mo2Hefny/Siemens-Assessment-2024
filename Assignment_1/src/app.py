#!/usr/bin/python3
import sys
import re
import csv
import time
from itertools import product
from server import Server
from client import Client

def create_combinations(system_options_num):
	"""
	Creates combinations of boolean values and None.

	Args:
		system_options_num (int): Number of system options for which combinations are generated.
															Each option can be True, False, or None.

	Returns:
		list: List of tuples, where each tuple represents a combination of boolean values and None.
					The length of each tuple is 2 times the system_options_num.
	"""
	options = [True, False, None]
	combinations = list(product(options, repeat=2*system_options_num))
	return combinations


def save_csv_file(file_name, header, test_cases):
	"""
	Saves test cases to a CSV file.

	Args:
		header (list): List containing the header row for the CSV file.
		test_cases (list of lists): List of test cases, where each test case is represented as a list.

	Raises:
		IOError: If the file 'test_cases.csv' is already opened and cannot be accessed immediately.
	"""
	try:
		with open(f'outputs/{file_name}', 'w', newline='') as file:
			writer = csv.writer(file)
			writer.writerow(header)
			writer.writerows(test_cases)
	except IOError:
		print("File is opened and can't be accessed. Please close the file.")
		# Retry logic: Wait and try again until the file can be accessed
		while True:
			time.sleep(2)  # Wait for 2 seconds
			try:
				with open(f'outputs/{file_name}', 'w', newline='') as file:
					writer = csv.writer(file)
					writer.writerow(header)  # Write the header row
					writer.writerows(test_cases)  # Write all test cases
					break  # Exit loop if successful
			except IOError:
				continue  # Retry if IOError occurs again
	print("CSV File saved.")


def validate_server_options(args):
	"""
	Validates the input System Options provided by the user.

	Args:
		args (list of Strings): List containing the name of the CSV file and the system options.

	Raises:
		ValueError: If the args are empty or doesn't contain any options or the options are invalid.
	"""
	if len(args) <= 1:  #No options
		raise ValueError("Invalid Logic")

	system_options = []
	special_char = []
	for option in args[1:]:
		if re.match('^[\\w-]+$', option) is None:   #Special characters
			special_char.append(option)
		if option in system_options:    #Same options
			raise ValueError("Invalid Logic")
		system_options.append(option)
	if len(special_char) != 0:
		raise ValueError(f"Invalid Input: {special_char} contain special characters.")
	return system_options


if __name__ == '__main__':
	system_options = None
	csv_file_name = None
	try:
		system_options = validate_server_options(sys.argv[1:])
		csv_file_name = sys.argv[1]
	except ValueError as e:
		print(f"Input Error: {e}")
		exit(0)

	system_options_num = len(system_options)

	# Create the Server
	server = Server(system_options_num)
	Client.server = server

	# Create the master and slave
	master = Client(True)
	slave = Client(False)

	# Create the master and slave options combinations
	combinations = create_combinations(system_options_num)

	# Check the options combinations
	test_cases = []
	test_case_id = 1
	for comb in combinations:
		master_options = list(comb[:system_options_num])
		slave_options = list(comb[system_options_num:])
	
		master.configureServer(master_options)
		slave.configureServer(slave_options)
		valid_tc, expected_options = server.state
	
		# Store test cases
		test_case = [test_case_id]
		for option in master_options:
				test_case.append("NA" if option is None else option)
		for option in slave_options:
				test_case.append("NA" if option is None else option)
		test_case.append("YES" if valid_tc else "NO")
		for option in expected_options:
				test_case.append("NA" if option is None else option)
				
		test_cases.append(test_case)
		test_case_id = test_case_id + 1

	# Write the test cases to a CSV file
	header = ["TestCase ID"]
	for option in system_options:
		header.append("Master Option For " + option)
	for option in system_options:
		header.append("Client Option For " + option)
	header.append("Valid TC")
	for option in system_options:
		header.append("Expected " + option)
	save_csv_file(csv_file_name, header, test_cases)

		
