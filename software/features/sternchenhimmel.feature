#
# Copyright 2018 Urs Fässler
# SPDX-License-Identifier: AGPL-3.0-or-later
#

# language: en

Feature: Start the system
  As a viewer
  I want to have a smooth show
  In order to come down


Scenario: Boot the system
  Given all lamps have the brightness percentage 100

  When I boot the system

  Then I expect the lamps to have the brightness percentage:
    | value |
    |     0 |
    |     0 |
    |     0 |
    |     0 |


Scenario: After some time, some lights are turned on
  Given I boot the system
  And I provide the random numbers:
    | number |
    |      0 |
    |      9 |
    |      7 |
    |      4 |

  When I wait for the fade time

  Then I expect the lamps to have the brightness percentage:
    | value |
    |     0 |
    |   100 |
    |   100 |
    |     0 |


Scenario: The lights are turned on slowely
  Given I boot the system
  And I provide the random numbers:
    | number |
    |      0 |
    |      4 |
    |      9 |
    |      7 |

  When I wait 0.25 times the fade time

  Then I expect the lamps to have the brightness percentage:
    | value |
    |     0 |
    |     0 |
    |     2 |
    |     2 |


Scenario: After a period, new lights are turned on
  Given I boot the system
  And I provide the random numbers:
    | number |
    |      0 |
    |      0 |
    |      0 |
    |      0 |
  And I wait 1 period
  And I provide the random numbers:
    | number |
    |      1 |
    |      1 |
    |      0 |
    |      0 |

  When I wait for the fade time

  Then I expect the lamps to have the brightness percentage:
    | value |
    |   100 |
    |   100 |
    |     0 |
    |     0 |


