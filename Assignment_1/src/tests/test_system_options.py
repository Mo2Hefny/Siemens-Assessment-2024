#!/usr/bin/python3
"""
Unittest for app
"""
import sys
import os

parent_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), os.pardir))
sys.path.insert(0, parent_dir)

import unittest
from app import validate_server_options

class TestServerOptions(unittest.TestCase):
	"""
		Test case for the Validate Server Options function
	"""

	def test_normal_option(self):
		self.assertEqual(validate_server_options(["test_case.csv", "BufferData"]), ["BufferData"])
		self.assertEqual(validate_server_options(["test_case.csv", "BufferData", "TimeOut"]), ["BufferData", "TimeOut"])
		self.assertEqual(validate_server_options(["test_case.csv", "BufferData", "TimeOut", "PacketLoss"]), ["BufferData", "TimeOut", "PacketLoss"])

	def test_empty_options(self):
		self.assertRaises(ValueError, validate_server_options, ["test_case.csv"])

	def test_empty_args(self):
		self.assertRaises(ValueError, validate_server_options, [])

	def test_duplicate_options(self):
		self.assertRaises(ValueError, validate_server_options, ["test_case.csv", "BufferData", "TimeOut", "BufferData"])

	def test_special_char_options(self):
		self.assertRaises(ValueError, validate_server_options, ["test_case.csv", "BufferData", "Ti/meOut", "P*acket", "Sp ace"])