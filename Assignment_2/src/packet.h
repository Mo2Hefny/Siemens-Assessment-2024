#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class PacketValidator {
  int modulesSize;
  vector<int> packetsModule;
  vector<bool> validation;

public:

  void setPacketModules(vector<int>& modulesNumber) {
    modulesSize = *max_element(modulesNumber.begin(), modulesNumber.end());
    packetsModule = modulesNumber;
    validation.resize(packetsModule.size(), false);
  }

  /**
   * evaluatePacketModule
   */
  bool evaluatePacketModule(int moduleNum, int prevNum) {
    return moduleNum == prevNum || moduleNum == ((prevNum + 1) % modulesSize);
  }

  void validatePackets() {
    int prevNum = packetsModule[0];
    for (int i = 0; i < packetsModule.size(); i++) {
      validation[i] = evaluatePacketModule(packetsModule[i] - 1, prevNum - 1);
      prevNum = packetsModule[i];
    }
  }

  vector<bool> getValidation() {
    return validation;
  }

  void saveValidation() {
    std::ofstream outputFile("packet_validation.csv");
        if (!outputFile) {
            cerr << "Error opening output file!" << endl;
            return;
        }

        outputFile << "PacketID,ModuleNumber,ValidModule" << endl;

        int id = 1;
        for (int i = 0; i < packetsModule.size(); i++) {
          outputFile << id++ << "," << packetsModule[i] << "," << (validation[i] ? "Yes" : "No") << endl;
        }
  }
};