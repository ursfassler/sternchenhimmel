/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include "Filter.h"
#include "ValueListener.h"

#include <chrono>
#include <functional>
#include <algorithm>


template<std::size_t N>
class Fader :
    public ValueListener<N>,
    public Filter
{
  public:
    Fader(std::chrono::milliseconds duration_, ValueListener<N> &listener_) :
      duration{duration_},
      listener{listener_}
    {
    }

    void changed(const std::array<double,N> &values) override
    {
      target = values;
    }

    void reset() override
    {
      const auto reset = [](double &value) {
        value = 0;
      };
      std::for_each(target.begin(), target.end(), reset);
      std::for_each(current.begin(), current.end(), reset);

      listener.changed(current);
    }

    void tick(std::chrono::milliseconds deltaTime) override
    {
      const auto delta = std::chrono::duration<double>(deltaTime) / std::chrono::duration<double>(duration);

      const std::function<double(double, double&)> fade = [delta](double target, double &value) {
        if (value < target) {
          return std::min(value + delta, 1.0);
        } else if (value > target){
          return std::max(value - delta, 0.0);
        }
        return target;
      };

      std::transform(target.cbegin(), target.cend(), current.begin(), current.begin(), fade);

      listener.changed(current);
    }

  private:
    const std::chrono::milliseconds duration;
    ValueListener<N> &listener;

    std::array<double, N> target;
    std::array<double, N> current;
};
