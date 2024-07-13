#!/usr/bin/python3
from itertools import repeat

class Server:
  """
  Server class simulates a configurable server with options and validation states.
  """

  def __init__(self, system_option_size: int) -> None:
    if system_option_size <= 0:
      raise ValueError("Number of system options must be positive")
    
    self.options_size = system_option_size
    self.options = list(repeat(True, system_option_size))
    self.valid_tc = True

  def configure(self, options: list, is_master: bool) -> None:
    """
    Configures the server with a list of options from the client.
    
    Args:
        options (list): List of options from a client to configure the server with.
        is_master (bool): Boolean flag indicating if the client is the master.
    
    Raises:
        ValueError: If the length of options does not match the expected options size.
    """
    if len(options) != self.options_size:
      raise ValueError("You must configure the Server with the same number of options")
    if is_master:
      self.options = list(map(lambda x: True if x is None else x, options))
      self.valid_tc = True
    else:
      for i in range(0, self.options_size):
        if options[i] is not None and options[i] != self.options[i]:
          self.options = list(repeat(None, self.options_size))
          self.valid_tc = False
          break

  @property
  def state(self) -> tuple:
    return self.valid_tc, self.options