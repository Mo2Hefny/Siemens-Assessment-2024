import sys
import os

parent_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), os.pardir))
sys.path.insert(0, parent_dir)

import unittest
from server import Server
from client import Client

class TestClient(unittest.TestCase):
	"""
		Test case for the Client class, specifically the configureServer method
	"""

	def setUp(self):
		self.server = Server(3)
		Client.server = self.server

	def test_empty_configureServer_master(self):
		master = Client(is_master=True)
		options = [None, None, None]
			
		expected = (True, [True, True, True])
		self.assertEqual(master.configureServer(options), expected)

	def test_empty_configureServer(self):
		master = Client(is_master=True)
		master.configureServer([None, None, None])

		client = Client(is_master=False)
		options = [None, None, None]

		expected = (True, [True, True, True])
		self.assertEqual(client.configureServer(options), expected)

	def test_configureServer_master(self):
		master = Client(is_master=True)
		options = [True, False, None]

		expected = (True, [True, False, True])
		self.assertEqual(master.configureServer(options), expected)

	def test_valid_configureServer_client(self):
		master = Client(is_master=True)
		master.configureServer([True, False, None])

		client = Client(is_master=False)
		options = [True, None, None]

		expected = (True, [True, False, True])
		self.assertEqual(client.configureServer(options), expected)
		
	def test_valid_configureServer_client_with_empty_master(self):
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
		master = Client(is_master=True)
		master.configureServer([None, None, None])

		client = Client(is_master=False)
		options = [True, None, None]

		expected = (True, [True, True, True])
		self.assertEqual(client.configureServer(options), expected)

	def test_invalid_configureServer_client(self):
		master = Client(is_master=True)
		master.configureServer([True, False, None])

		client = Client(is_master=False)
		options = [False, None, None]

		expected = (False, [None, None, None])
		self.assertEqual(client.configureServer(options), expected)

	def test_invalid_options_type(self):
		master = Client(is_master=True)
		options = "invalid"

		self.assertRaises(TypeError, master.configureServer, options)

	def test_invalid_options_size(self):
		master = Client(is_master=True)
		options = [True, False]

		self.assertRaises(ValueError, master.configureServer, options)

	def test_invalid_options_content(self):
		master = Client(is_master=True)
		options = [True, "invalid", None]

		self.assertRaises(TypeError, master.configureServer, options)

		options = [True, 1, None]
		self.assertRaises(TypeError, master.configureServer, options)

if __name__ == '__main__':
		unittest.main()
