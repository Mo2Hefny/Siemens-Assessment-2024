import sys
import os

parent_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), os.pardir))
sys.path.insert(0, parent_dir)

import unittest
from server import Server

class TestServer(unittest.TestCase):
	"""
		Test case for the Server class, specifically the configure method
	"""

	def setUp(self):
		self.server = Server(system_option_size=3)

	def test_invalid_setup_size(self):
		self.assertRaises(ValueError, Server(system_option_size=0))

	def test_initial_state(self):
		self.assertEqual(self.server.state, (True, [True, True, True]))

	def test_configure_valid_tc_master(self):
		options = [None, False, True]
		self.server.configure(options, is_master=True)
		self.assertEqual(self.server.state, (True, [True, False, True]))

	def test_configure_valid_tc_client(self):
		options = [None, False, True]
		self.server.configure(options, is_master=True)
		options = [None, False, True]
		self.server.configure(options, is_master=False)
		self.assertEqual(self.server.state, (True, [True, False, True]))

	def test_configure_valid_tc_client_for_empty_master(self):
		# NOTE: If the master doesn't configure the system
		# while the client configures it, the client's options
		# are compared with the default server's values instead of the
		# master's unconfigured system options
		# Ex:
		# Master:               None  None  None
		# Server's Default:     True  True  True
		# Client:               True  None  None
		#
		# Outputs: Valid_tc = True, Expected_Output = [True, True, True]
		options = [None, None, None]
		self.server.configure(options, is_master=True)
		options = [None, True, True]
		self.server.configure(options, is_master=False)
		self.assertEqual(self.server.state, (True, [True, True, True]))

	def test_configure_invalid_tc(self):
		options = [None, False, True]
		self.server.configure(options, is_master=True)
		options = [None, True, None]
		self.server.configure(options, is_master=False)
		self.assertEqual(self.server.state, (False, [None, None, None]))

	def test_configure_all_true(self):
		options = [True, True, True]
		self.server.configure(options, is_master=True)
		self.assertEqual(self.server.state, (True, [True, True, True]))

	def test_configure_all_none(self):
		options = [None, None, None]
		self.server.configure(options, is_master=True)
		self.assertEqual(self.server.state, (True, [True, True, True]))

	def test_configure_mixed(self):
		options = [True, None, False]
		self.server.configure(options, is_master=True)
		self.assertEqual(self.server.state, (True, [True, True, False]))

	def test_configure_invalid_options_size(self):
		options = [True, False]
		self.assertRaises(ValueError, self.server.configure, options, True)

if __name__ == '__main__':
	unittest.main()
