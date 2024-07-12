#include <gtest/gtest.h>
#include "../packet.h"

TEST(PacketValidatorTest, AccumulativeValues) {
  PacketValidator validator;
  vector<int> modules = {1, 2, 3, 4, 5};

  validator.setPacketModules(modules);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  ASSERT_EQ(validation.size(), modules.size());
  for (auto& result: validation)
    EXPECT_TRUE(result);
}

TEST(PacketValidatorTest, EqualValues) {
  PacketValidator validator;
  vector<int> modules = {1, 1, 1, 1, 1};

  validator.setPacketModules(modules);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  ASSERT_EQ(validation.size(), modules.size());
  for (auto& result: validation)
    EXPECT_TRUE(result);
}

TEST(PacketValidatorTest, NegativeValues) {
  PacketValidator validator;
  vector<int> modules = {-1, -2, -3, -4, -5};

  EXPECT_THROW(validator.setPacketModules(modules), invalid_argument);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  EXPECT_TRUE(validation.empty());
}

TEST(PacketValidatorTest, MixValues) {
  PacketValidator validator;
  vector<int> modules = {6, -2, 2, -1, 7};

  EXPECT_THROW(validator.setPacketModules(modules), invalid_argument);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  EXPECT_TRUE(validation.empty());
}

TEST(PacketValidatorTest, ZeroValues) {
  PacketValidator validator;
  vector<int> modules = {0, 0, 0, 0, 0};

  EXPECT_THROW(validator.setPacketModules(modules), invalid_argument);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  EXPECT_TRUE(validation.empty());
}

TEST(PacketValidatorTest, UnorderedPositiveValues) {
  PacketValidator validator;
  vector<int> modules = {6, 1, 2, 3, 7};

  validator.setPacketModules(modules);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  EXPECT_EQ(validation.size(), modules.size());
  EXPECT_EQ(validation, vector<bool> ({true, false, true, true, false}));
}

TEST(PacketValidatorTest, UnorderedPositiveValuesWithDups) {
  PacketValidator validator;
  vector<int> modules = {4, 4, 2, 1, 1};

  validator.setPacketModules(modules);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  EXPECT_EQ(validation.size(), modules.size());
  EXPECT_EQ(validation, vector<bool> ({true, true, false, false, true}));
}

TEST(PacketValidatorTest, FullCycleVector) {
  PacketValidator validator;
  vector<int> modules = {4, 5, 6, 1, 1};

  validator.setPacketModules(modules);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  EXPECT_EQ(validation.size(), modules.size());
  for (auto& result: validation)
    EXPECT_TRUE(result);
}

TEST(PacketValidatorTest, EmptyVector) {
  PacketValidator validator;
  vector<int> modules;

  EXPECT_THROW(validator.setPacketModules(modules), invalid_argument);

  vector<bool> validation = validator.getValidation();

  EXPECT_TRUE(validation.empty());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}