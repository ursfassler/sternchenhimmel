/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include "TimerListener.h"
#include "Filter.h"
#include "NumberFactory.h"
#include "ValueListener.h"

#include <array>
#include <algorithm>


template<std::size_t N>
class Generator :
    public TimerListener,
    public Filter
{
  public:
    Generator(NumberFactory &numberFactory_, ValueListener<N> &listener_) :
      numberFactory{numberFactory_},
      listener{listener_}
    {
    }

    void reset() override
    {
    }

    void tick(std::chrono::milliseconds delta) override
    {
    }

    void timeout() override
    {
      const auto randomNumber = [this]() {
        return numberFactory.produce() % 2;
      };
      std::array<double, N> target;
      std::generate(target.begin(), target.end(), randomNumber);
      listener.changed(target);
    }

  private:
    NumberFactory &numberFactory;
    ValueListener<N> &listener;
};
