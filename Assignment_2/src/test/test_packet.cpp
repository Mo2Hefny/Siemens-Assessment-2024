#include <gtest/gtest.h>
#include "../packet.h"
#include <climits>

TEST(PacketValidatorTest, AccumulativeValues) {
  PacketValidator validator;
  vector<int> modules = {1, 2, 3, 4, 5};

  validator.setPacketModules(modules);
  EXPECT_EQ(validator.getModuleSize(), 5);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  ASSERT_EQ(validation.size(), modules.size());
  for (const auto& result: validation)
    EXPECT_TRUE(result);
}

TEST(PacketValidatorTest, EqualValues) {
  PacketValidator validator;
  vector<int> modules = {1, 1, 1, 1, 1};

  validator.setPacketModules(modules);
  EXPECT_EQ(validator.getModuleSize(), 1);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  ASSERT_EQ(validation.size(), modules.size());
  for (const auto& result: validation)
    EXPECT_TRUE(result);
}

TEST(PacketValidatorTest, NegativeValues) {
  PacketValidator validator;
  vector<int> modules = {-1, -2, -3, -4, -5};

  EXPECT_THROW(validator.setPacketModules(modules), invalid_argument);
  EXPECT_EQ(validator.getModuleSize(), 0);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  EXPECT_TRUE(validation.empty());
}

TEST(PacketValidatorTest, MixValues) {
  PacketValidator validator;
  vector<int> modules = {6, -2, 2, -1, 7};

  EXPECT_THROW(validator.setPacketModules(modules), invalid_argument);
  EXPECT_EQ(validator.getModuleSize(), 0);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  EXPECT_TRUE(validation.empty());
}

TEST(PacketValidatorTest, ZeroValues) {
  PacketValidator validator;
  vector<int> modules = {0, 0, 0, 0, 0};

  EXPECT_THROW(validator.setPacketModules(modules), invalid_argument);
  EXPECT_EQ(validator.getModuleSize(), 0);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  EXPECT_TRUE(validation.empty());
}

TEST(PacketValidatorTest, UnorderedPositiveValues) {
  PacketValidator validator;
  vector<int> modules = {6, 1, 2, 3, 7, 2};

  validator.setPacketModules(modules);
  EXPECT_EQ(validator.getModuleSize(), 7);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  EXPECT_EQ(validation.size(), modules.size());
  EXPECT_EQ(validation, vector<bool> ({true, false, true, true, false, false}));
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
  for (const auto& result: validation)
    EXPECT_TRUE(result);
}

TEST(PacketValidatorTest, EmptyVector) {
  PacketValidator validator;
  vector<int> modules;

  EXPECT_THROW(validator.setPacketModules(modules), invalid_argument);

  vector<bool> validation = validator.getValidation();

  EXPECT_TRUE(validation.empty());
}

TEST(PacketValidatorTest, MaxValues) {
  PacketValidator validator;
  vector<int> modules = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};

  validator.setPacketModules(modules);
  EXPECT_EQ(validator.getModuleSize(), INT_MAX);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  EXPECT_EQ(validation.size(), modules.size());
  for (const auto& result: validation)
    EXPECT_TRUE(result);
}

TEST(PacketValidatorTest, MaxValuesCycle) {
  PacketValidator validator;
  vector<int> modules = {INT_MAX, INT_MAX, 1, 2};

  validator.setPacketModules(modules);
  EXPECT_EQ(validator.getModuleSize(), INT_MAX);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  EXPECT_EQ(validation.size(), modules.size());
  for (const auto& result: validation)
    EXPECT_TRUE(result);
}

TEST(PacketValidatorTest, EnormousValues) {
  PacketValidator validator;
  vector<int> modules = {INT_MAX-4, INT_MAX-1, INT_MAX, INT_MAX};

  validator.setPacketModules(modules);
  EXPECT_EQ(validator.getModuleSize(), INT_MAX);
  validator.validatePackets();

  vector<bool> validation = validator.getValidation();

  EXPECT_EQ(validation.size(), modules.size());
  EXPECT_EQ(validation, vector<bool> ({true, false, true, true}));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}