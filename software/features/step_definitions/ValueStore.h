/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include "ValueListener.h"

#include <array>


template<std::size_t N>
class ValueStore :
    public ValueListener<N>
{
  public:

    void changed(const std::array<double,N> &values) override
    {
      this->values = values;
    }

    std::array<double,N> values{};
};



