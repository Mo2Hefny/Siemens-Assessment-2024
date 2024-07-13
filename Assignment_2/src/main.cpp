#include "packet.h"
#include <sstream>
#include <limits>

/**
 * readInteger - Reads an integer or rounds a float from the console and throws an error if
 * invalid input was given then tries again.
 * 
 * @returns the read integer
 */
int readInteger() {
  int integer;
  bool failed;
  do
  {
    string input;
    cin >> input;
    istringstream iss(input);
    failed = !(iss >> integer);
    try
    {
      if (failed)
        throw invalid_argument("Input is not an integer. Try again.");
    }
    catch (const invalid_argument &e)
    {
      cerr << "Caught invalid_argument: " << e.what() << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  } while (failed);

  return integer;
}

int main()
{
  int packetsNum;
  cout << "Enter number of packets: ";
  packetsNum = readInteger();

  PacketValidator validator;

  vector<int> packetModules(packetsNum);
  cout << "Enter module numbers for each packet:" << endl;
  for (auto& moduleNumber : packetModules)
    moduleNumber = readInteger();

  try
  {
    validator.setPacketModules(packetModules);
    validator.validatePackets();
    validator.saveValidation();
  }
  catch (const invalid_argument &e)
  {
    cerr << "Caught invalid_argument: " << e.what() << endl;
  }

  return 0;
}