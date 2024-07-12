#include "packet.h"

int main()
{
  int packetsNum;
  cout << "Enter number of packets: ";
  cin >> packetsNum;

  PacketValidator validator;

  vector<int> packetModules(packetsNum);
  cout << "Enter module numbers for each packet:" << endl;
  for (auto &moduleNumber : packetModules)
    cin >> moduleNumber;

  try {
    validator.setPacketModules(packetModules);
    validator.validatePackets();
    validator.saveValidation();
  }
  catch (const invalid_argument& e) {
    cerr << "Caught invalid_argument: " << e.what() << endl;
  }

  return 0;
}