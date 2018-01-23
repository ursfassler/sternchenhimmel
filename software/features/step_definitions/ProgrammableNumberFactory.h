/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include "NumberFactory.h"

#include <list>
#include <stdexcept>


class ProgrammableNumberFactory :
    public NumberFactory
{
  public:
    int produce() override
    {
      if (numbers.empty()) {
        throw std::runtime_error{"no more numbers available"};
      }

      const auto number = numbers.front();
      numbers.pop_front();

      return number;
    }

    std::list<int> numbers{};

};

