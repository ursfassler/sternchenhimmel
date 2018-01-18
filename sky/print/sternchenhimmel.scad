/*
 * Copyright 2018 Urs Fässler
 * SPDX-License-Identifier: AGPL-3.0-or-later OR CC-BY-SA-4.0
 */

include <ledHole.scad>
include <holder.scad>

module led() {
  ledDiameter = 5;
  ledHeight = 10;
  
  ledHole(ledDiameter/2, 10);
}

Stars = [
  [69,-33],
  [60,44],
  [55,6],
  [36,-60],
  [26,27],
  [25,-16],
  [14,67],
  [5,-50],
  [-10,41],
  [-11,3],
  [-27,-26],
  [-28,-68],
  [-33,62],
  [-47,5],
  [-65,-31],
  [-71,31],
];

module stars() {
  AddNumbers = false;
  for (i = [0:len(Stars)-1]) {
    s = Stars[i];
    translate([s[0],s[1],0]) {
      led();
      if (AddNumbers) {
        translate([4,0,4]) {
          linear_extrude(2) {
            text(str(i), 7);
          }
        }
      }
    }
  }
}

module holders() {
  for (i = [0:2]) {
    rotate(20 + i*120, [0,0,1]) {
      translate([70,0,4]) {
        holder();
      }
    }
  }
}

module boardHolder() {
  rotate(-20, [0,0,1]) {
    translate([0,0,4]) {
      Width = 45.72;
      Length = 50.8;
      
      translate([Length/2, Width/2, 0]) {
        holder();
      }
      translate([Length/2, -Width/2, 0]) {
        holder();
      }
      translate([-Length/2, Width/2, 0]) {
        holder();
      }
      translate([-Length/2, -Width/2, 0]) {
        holder();
      }
    }
  }
}

difference() {
  union() {
    cylinder(5, r=90, center=false, $fn=120);
    holders();
    boardHolder();
  }
  stars();
}

