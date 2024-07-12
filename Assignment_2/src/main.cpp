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

  validator.setPacketModules(packetModules);
  validator.validatePackets();
  validator.saveValidation();

  return 0;
}