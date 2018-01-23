/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include "../logic/ValueListener.h"

#include "driver/gpio.h"
#include "driver/ledc.h"

#include <array>


template<std::size_t N>
class LedWriter :
    public ValueListener<N>
{
  public:
    LedWriter(const std::array<gpio_num_t, N> &gpio) :
      ledc_channel{led_pwm_configuration(gpio)}
    {
      init_timer();
      init_channel(ledc_channel);
    }

    void changed(const std::array<double,N> &values) override
    {
      for (std::size_t i = 0; i < N; i++) {
        setBrightness(i, values[i]);
      }
    }

  private:
    const std::array<ledc_channel_config_t, N> ledc_channel;

    static const auto LEDC_HS_TIMER = LEDC_TIMER_0;
    static const auto LEDC_HS_MODE = LEDC_HIGH_SPEED_MODE;
    static const auto LEDC_LS_TIMER = LEDC_TIMER_1;
    static const auto LEDC_LS_MODE = LEDC_LOW_SPEED_MODE;

    void setLedTo(std::size_t index, uint32_t duty)
    {
      const auto &config = ledc_channel[index];

      ledc_set_duty(config.speed_mode, config.channel, duty);
      ledc_update_duty(config.speed_mode, config.channel);
    }

    void setBrightness(std::size_t index, float value)
    {
      setLedTo(index, static_cast<uint32_t>(4095 * value));
    }

    static std::array<ledc_channel_config_t, N> led_pwm_configuration(const std::array<gpio_num_t, N> &gpio)
    {
      static_assert(N <= 16, "a maximum of 16 LEDs are supported");
      std::array<ledc_channel_config_t, N> ledc_channel;

      for (std::size_t i = 0; i < N; i++)
      {
        ledc_channel[i].channel    = static_cast<ledc_channel_t>(i % 8);
        ledc_channel[i].duty       = 0;
        ledc_channel[i].gpio_num   = gpio[i];
        ledc_channel[i].speed_mode = i < 8 ? LEDC_HS_MODE : LEDC_LS_MODE;
        ledc_channel[i].timer_sel  = i < 8 ? LEDC_HS_TIMER : LEDC_LS_TIMER;
      }

      return ledc_channel;
    }

    void init_timer()
    {
      /*
       * Prepare and set configuration of timers
       * that will be used by LED Controller
       */
      ledc_timer_config_t ledc_timer;
      ledc_timer.duty_resolution = LEDC_TIMER_13_BIT; // resolution of PWM duty
      ledc_timer.freq_hz = 5000;                      // frequency of PWM signal
      ledc_timer.speed_mode = LEDC_HS_MODE;           // timer mode
      ledc_timer.timer_num = LEDC_HS_TIMER;            // timer index
      // Set configuration of timer0 for high speed channels
      ledc_timer_config(&ledc_timer);

      // Prepare and set configuration of timer1 for low speed channels
      ledc_timer.speed_mode = LEDC_LS_MODE;
      ledc_timer.timer_num = LEDC_LS_TIMER;
      ledc_timer_config(&ledc_timer);
    }

    static void init_channel(const std::array<ledc_channel_config_t, N> &ledc_channel)
    {
      // Set LED Controller with previously prepared configuration
      for (const auto &config : ledc_channel) {
          ledc_channel_config(&config);
      }
    }
};
