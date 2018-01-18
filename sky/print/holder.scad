/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later OR CC-BY-SA-4.0
 */

module holder() {
  HoleHeight = 6;
  
  difference() {
    union() {
      translate([0,0,HoleHeight]) {
        rotate(-90, [1,0,0]) {
          cylinder(5, r=6, center=true, $fn=24);
        }
      }
      translate([-7,-3.5,0]) {
        cube([14,7,HoleHeight], center=false);
      }
    }

    translate([0,0,HoleHeight]) {
      rotate(-90, [1,0,0]) {
        cylinder(20, r=2, center=true, $fn=24);
      }
    }
  }
}
