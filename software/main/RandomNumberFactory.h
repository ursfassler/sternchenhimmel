/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include "../logic/NumberFactory.h"


class RandomNumberFactory :
    public NumberFactory
{
  public:
    RandomNumberFactory();

    int produce() override;

};

