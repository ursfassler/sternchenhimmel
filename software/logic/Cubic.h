/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include "Filter.h"
#include "ValueListener.h"

#include <functional>
#include <algorithm>


template<std::size_t N>
class Cubic :
    public ValueListener<N>,
    public Filter
{
  public:
    Cubic(ValueListener<N> &listener_) :
      listener{listener_}
    {
    }

    void changed(const std::array<double,N> &values) override
    {
      std::array<double,N> out;

      const std::function<double(double)> delinearize = [](double value) {
        return value * value * value;
      };
      std::transform(values.cbegin(), values.cend(), out.begin(), delinearize);

      listener.changed(out);
    }

    void reset() override
    {
    }

    void tick(std::chrono::milliseconds) override
    {
    }

  private:
    ValueListener<N> &listener;
};

