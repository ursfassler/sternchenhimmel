/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include "RandomNumberFactory.h"

#include <cstdlib>


RandomNumberFactory::RandomNumberFactory()
{
  srand(0);
}

int RandomNumberFactory::produce()
{
  return lrand48();
}
