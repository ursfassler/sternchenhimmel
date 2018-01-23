/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../logic/SternchenHimmel.h"
#include "RandomNumberFactory.h"
#include "LedWriter.h"

static const std::array<gpio_num_t, 16> GPIO_FOR_LED_PWM = {
  GPIO_NUM_25,
  GPIO_NUM_26,
  GPIO_NUM_27,
  GPIO_NUM_14,
  GPIO_NUM_12,
  GPIO_NUM_13,
  GPIO_NUM_16,
  GPIO_NUM_17,
  GPIO_NUM_4,
  GPIO_NUM_2,
  GPIO_NUM_15,
  GPIO_NUM_10,
  GPIO_NUM_23,
  GPIO_NUM_19,
  GPIO_NUM_22,
  GPIO_NUM_21,
};

static constexpr std::chrono::seconds Period{9};
static constexpr std::chrono::seconds FadeTime{3};
static constexpr std::chrono::milliseconds TickTime{10};

extern "C"
{


void delay(std::chrono::milliseconds delta)
{
  vTaskDelay(delta.count() / portTICK_PERIOD_MS);
}

void app_main()
{
    RandomNumberFactory numbers{};
    LedWriter<16> ledWriter{GPIO_FOR_LED_PWM};
    SternchenHimmel<16> sternchen{numbers, ledWriter, FadeTime, Period};

    sternchen.reset();

    while (true)
    {
      sternchen.tick(TickTime);
      delay(TickTime);
    }
}


}
