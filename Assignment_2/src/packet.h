#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

class PacketValidator
{
  int modulesSize;
  vector<int> packetsModule;
  vector<bool> validation;

public:
  /**
   * setPacketModules - Sets the packet modules for validation.
   *
   * @param modulesNumber Vector of the packets' module numbers to validate.
   *
   * @throws invalid_argument if the input array is empty or contains non-positive numbers.
   */
  void setPacketModules(vector<int> &modulesNumber)
  {
    // Clear the variables in case of invalid input
    validation.clear();
    packetsModule.clear();
    modulesSize = 0;

    if (modulesNumber.empty())
      throw invalid_argument("Array can't be empty");
    if (*min_element(modulesNumber.begin(), modulesNumber.end()) <= 0)
      throw invalid_argument("Values can't be negative");
    modulesSize = *max_element(modulesNumber.begin(), modulesNumber.end());
    packetsModule = modulesNumber;
    validation.resize(packetsModule.size(), false);
  }

  /**
   * evaluatePacketModule - Evaluates if a packet module number is valid based on the previous module number.
   *
   * @param moduleNum The module number to evaluate.
   * @param prevNum The previous module number.
   *
   * @returns true if the module number is valid, false otherwise.
   */
  bool evaluatePacketModule(int moduleNum, int prevNum)
  {
    return moduleNum == prevNum || moduleNum == ((prevNum + 1) % modulesSize);
  }

  /**
   * validatePackets - Validates all packets based on the packets' assigned module numbers.
   */
  void validatePackets()
  {
    if (packetsModule.empty())
      return;

    int prevNum = packetsModule[0];
    for (int i = 0; i < packetsModule.size(); i++)
    {
      validation[i] = evaluatePacketModule(packetsModule[i] - 1, prevNum - 1);
      prevNum = packetsModule[i];
    }
  }

  /**
   * getModuleSize - Retrieves the largest module number in the cycle, 
   * indicating the last module M.
   * 
   * @returns The biggest packet's module number.
   */
  int getModuleSize()
  {
    return modulesSize;
  }

  /**
   * getValidation - Retrieves the validation results of each packet.
   * 
   * @returns Vector of boolean values indicating whether each packet is valid.
   */
  vector<bool> getValidation()
  {
    return validation;
  }

  /**
   * saveValidation - Saves the validation results to a CSV file.
   * File format:
   *   PacketID,ModuleNumber,ValidModule
   *   1,1,Yes
   *   2,3,No
   *   3,4,Yes
   *   4,4,Yes
   */
  void saveValidation()
  {
    std::ofstream outputFile("./src/output/packet_validation.csv");
    if (!outputFile)
    {
      cerr << "Error opening output file!" << endl;
      return;
    }

    outputFile << "PacketID,ModuleNumber,ValidModule" << endl;

    int id = 1;
    for (int i = 0; i < packetsModule.size(); i++)
    {
      outputFile << id++ << "," << packetsModule[i] << "," << (validation[i] ? "Yes" : "No") << endl;
    }
  }
};