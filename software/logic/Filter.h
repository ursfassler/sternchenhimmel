/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include <chrono>


class Filter
{
  public:
    virtual void reset() = 0;
    virtual void tick(std::chrono::milliseconds delta) = 0;
};
