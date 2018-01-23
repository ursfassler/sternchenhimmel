/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include "Filter.h"
#include "TimerListener.h"

#include <chrono>


class Timer :
    public Filter
{
  public:
    Timer(std::chrono::milliseconds timeout_, TimerListener &listener_) :
      timeout{timeout_},
      time{timeout_},
      listener{listener_}
    {
    }

    void reset() override
    {
      time = timeout;
    }

    void tick(std::chrono::milliseconds delta) override
    {
      if (time >= timeout) {
        time = std::chrono::milliseconds{0};
        listener.timeout();
      }
      time += delta;
    }

  private:
    const std::chrono::milliseconds timeout;
    std::chrono::milliseconds time;
    TimerListener &listener;
};

