/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later OR CC-BY-SA-4.0
 */

module cone(radius) {
  BottomRadius = radius * 2;
  Height = BottomRadius * 2;
  cylinder(Height, r1=BottomRadius, r2=0, center=true, $fn=24);
}

module hole(radius, height) {
  ledHeight = height * 2 + 1;
  holderHeight = ledHeight + 1;
  
  InnerRadius = radius;
  OuterRadius = InnerRadius + 0.5;
  HolderRadius = 2;
  HolderCount = 3;
  HolderDistance = InnerRadius + HolderRadius;
  
  difference() {
    cylinder(ledHeight, r=OuterRadius, center=true, $fn=24);

    for (i = [0:HolderCount-1]) {
      rotation = 360 / HolderCount * i;
      rotate(rotation , [0,0,1]) {
        translate([HolderDistance,0,0]) {
          cylinder(holderHeight, r=HolderRadius, center=true, $fn=24);
        }
      }
    }
  }
}

module ledHole(radius, height) {
  hole(radius, height);
  cone(radius + 1);
}
