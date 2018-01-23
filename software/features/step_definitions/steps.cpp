/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include <gmock/gmock.h>
#include <cucumber-cpp/autodetect.hpp>

#include "ProgrammableNumberFactory.h"
#include "ValueStore.h"
#include "SternchenHimmel.h"

#include <algorithm>
#include <chrono>

using cucumber::ScenarioScope;

static constexpr std::chrono::seconds Period{9};
static constexpr std::chrono::seconds FadeTime{3};
static constexpr std::chrono::milliseconds TickTime{10};



class Context
{
  public:
    ProgrammableNumberFactory numbers{};
    ValueStore<4> lamp;
    SternchenHimmel<4> sternchenHimmel{numbers, lamp, FadeTime, Period};
};

GIVEN("^all lamps have the brightness percentage 100$")
{
  ScenarioScope<Context> context;

  auto &lamp = context->lamp.values;
  std::for_each(lamp.begin(), lamp.end(), [](double &value) { value = 1; });
}

GIVEN("^I provide the random numbers:$")
{
  TABLE_PARAM(table);

  ScenarioScope<Context> context;
  auto &numbers = context->numbers.numbers;

  numbers.clear();
  const auto entryToInt = [](std::map<std::string,std::string> v) -> int {
    return std::stoi(v["number"]);
  };
  const auto &s = table.hashes();
  std::transform(s.begin(), s.end(), std::back_inserter(numbers), entryToInt);
}

WHEN("^I boot the system$")
{
  ScenarioScope<Context> context;

  context->sternchenHimmel.reset();
}

WHEN("^I wait for the fade time$")
{
  ScenarioScope<Context> context;

  for (auto time = std::chrono::milliseconds{0}; time < FadeTime; time += TickTime) {
    context->sternchenHimmel.tick(TickTime);
  }
}

WHEN("^I wait 0\\.25 times the fade time$")
{
  ScenarioScope<Context> context;

  const auto EndTime = FadeTime * 0.25;

  for (auto time = std::chrono::milliseconds{0}; time < EndTime; time += TickTime) {
    context->sternchenHimmel.tick(TickTime);
  }
}

GIVEN("^I wait 1 period$")
{
  ScenarioScope<Context> context;

  for (auto time = std::chrono::milliseconds{0}; time < Period; time += TickTime) {
    context->sternchenHimmel.tick(TickTime);
  }
}

THEN("^I expect the lamps to have the brightness percentage:$")
{
  TABLE_PARAM(brightness);

  const auto entryToInt = [](std::map<std::string,std::string> v) -> int {
    return std::stoi(v["value"]);
  };
  const auto &s = brightness.hashes();
  std::vector<int> ordinals;
  std::transform(s.begin(), s.end(), std::back_inserter(ordinals), entryToInt);

  const auto toPercentage = [](double v) -> int {
    return std::round(v * 100);
  };
  ScenarioScope<Context> context;
  const auto &lamps = context->lamp.values;
  std::vector<int> actual{};
  std::transform(lamps.begin(), lamps.end(), std::back_inserter(actual), toPercentage);

  ASSERT_EQ(ordinals, actual);
}
