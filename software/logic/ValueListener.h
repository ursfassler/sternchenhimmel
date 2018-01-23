/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include <array>


template<std::size_t N>
class ValueListener
{
  public:
    virtual void changed(const std::array<double,N> &values) = 0;
};
