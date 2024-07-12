#!/usr/bin/python3
from itertools import repeat

class Server:
  """
  """
  # Static variable to store server instance
  server = None

  def __init__(self, system_option_size: int) -> None:
    self.options_size = system_option_size
    self.options = list(repeat(True, system_option_size))
    self.valid_tc = True

  def configure(self, options: list, is_master: bool) -> None:
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