#!/usr/bin/python3

class Client:
  """
  """
  # Static variable to store server instance
  server = None

  def __init__(self, is_master: bool) -> None:
    self.is_master = is_master

  def configureServer(self, options: list) -> tuple:
    """ Function to set the global configurations of the server
    Args:
        options (list of bool or None): List representing the clients's options configurations.
                                      Must have a length > 0 and be the same length of the server's options.

    Returns:
        tuple: A tuple containing:
            - valid_tc (bool): True if the test case is valid.
            - expected_options (list): Expected global configurations after master's and client's input.
    """

    server = Client.server

    # Validate the input for the Unittest
    if type(options) is not list:
        raise TypeError("Inputs must be a list of bool or None.")
    if len(options) != server.options_size or len(options) == 0:
        raise ValueError("Input lists must be the same size and bigger than 0.")
    if not all(isinstance(x, bool) or x is None for x in options):
        raise TypeError("Input lists must contain only boolean or None values.")

    server.configure(options, self.is_master)
    
    return server.state