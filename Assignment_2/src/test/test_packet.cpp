#include <gtest/gtest.h>
#include "../packet.h"

TEST(PacketValidatorTest, ValidatePackets) {
  PacketValidator validator;
  std::vector<int> modules = {1, 2, 3, 4, 5};

  validator.setPacketModules(modules);
  validator.validatePackets();

  std::vector<bool> validation = validator.getValidation();

  ASSERT_EQ(validation.size(), modules.size());
  EXPECT_TRUE(validation[0]);
  EXPECT_TRUE(validation[1]);
}

TEST(PacketValidatorTest, ValidatePackets2) {
  PacketValidator validator;
  std::vector<int> modules = {1, 2, 3, 4, 5};

  validator.setPacketModules(modules);
  validator.validatePackets();

  std::vector<bool> validation = validator.getValidation();

  ASSERT_EQ(validation.size(), modules.size());
  EXPECT_TRUE(validation[0]);
  EXPECT_TRUE(validation[1]);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}