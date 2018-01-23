/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once


class TimerListener
{
  public:
    virtual void timeout() = 0;
};
