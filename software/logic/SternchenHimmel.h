/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include "Cubic.h"
#include "Fader.h"
#include "Generator.h"
#include "Timer.h"


template<std::size_t N>
class SternchenHimmel
{
  public:

    SternchenHimmel(
        NumberFactory &numberFactory_,
        ValueListener<N> &lamp_,
        std::chrono::milliseconds fadeTime,
        std::chrono::milliseconds period) :
      cubic{lamp_},
      fader{fadeTime, cubic},
      generator{numberFactory_, fader},
      timer{period, generator}
    {
    }

    void reset()
    {
      cubic.reset();
      fader.reset();
      generator.reset();
      timer.reset();
    }

    void tick(std::chrono::milliseconds delta)
    {
      timer.tick(delta);
      generator.tick(delta);
      fader.tick(delta);
      cubic.tick(delta);
    }

  private:
    Cubic<N> cubic;
    Fader<N> fader;
    Generator<N> generator;
    Timer timer;

};

