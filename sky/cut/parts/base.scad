$fa=0.1;
$fs=0.5;

ledDiameter_mm = 5;
bottomRotation = 20;

module led(x, y) {
  translate([x*2.54, y*2.54, -8]) {
    cylinder(d=ledDiameter_mm, h=8);
  }
}

module ledHole(x, y) {
  translate([x*2.54, y*2.54, 0]) {
    circle(d=ledDiameter_mm);
  }
}

module ledModule() {
  cube([19*2.54, 4*2.54, 2], center = true);
  led(8, -0.5);
  led(-8, 0.5);
  translate([-0.5*2.54, -1.5*2.54, 0]) {
    cube([2.54, 3*2.54, 5]);
  }
}

module cpuPcb() {
  translate([-16*2.54, 5*2.54, 4]) {
    cube([21*2.54, 15*2.54, 2]);
    translate([0.5*2.54, 2.5*2.54, 11]) {
      cube([23*2.54, 10*2.54, 2]);
    }
  }
}

module ledModuleHoles() {
  ledHole(8, -0.5);
  ledHole(-8, 0.5);
}

ModulePosition = [
  [[-6.5, 22], 0],
  [[11, 18.5], 90],
  [[-25, 5.5], 90],
  [[-15, -5.5], 90],
  [[5.5, 0], 0],
  [[27, 3.5], 90],
  [[-3.5, -26], 0],
  [[14.5, -15], 0],
];

module ledModules() {
  for (mp = ModulePosition) {
    pos = 2.54 * mp[0];
    translate([pos[0], pos[1], 4]) {
      rotate(mp[1], [0,0,1]) {
        ledModule();
      }
    }
  }
}

module ledHoles() {
  for (mp = ModulePosition) {
    pos = 2.54 * mp[0];
    translate([pos[0], pos[1], 0]) {
      rotate(mp[1], [0,0,1]) {
        ledModuleHoles();
      }
    }
  }
}

Thickness = 4;

module side() {
  contur = [
    [0,0], 
    [20,0], 
    [20,15], 
    [76,60],
    [85,60],
    [85,80], 
    [75,80], 
    [0,20]
  ];

  difference() {
    union() {
      polygon(contur);
    }
    translate([20,10,0]) {
      square([10,Thickness], true);
    }
    translate([30,45,0]) {
      square([10,Thickness], true);
      square([5,10]);
    }
    translate([85,70,0]) {
      square([10,Thickness], true);
    }
  }
}


NumSides = 3;
sideAngles = [ for (i = [0:NumSides-1]) i*360/NumSides ];

module bottom() {
  difference() {
    circle(r=90); 
    rotate(bottomRotation, [0,0,1]) {
      ledHoles();
    }
    for (i = sideAngles) {
      rotate(i, [0,0,1]) {
        translate([90,0,0]) {
          square([10,Thickness], true);
        }
      }
    }
  }
}
  
module middle() {
  difference() {
    difference() {
      circle(r=65); 
      circle(r=55); 
    }
    for (i = sideAngles) {
      rotate(i, [0,0,1]) {
        translate([55,0,0]) {
          square([10,Thickness], true);
        }
      }
    }
  }
}

module top() {
  difference() {
    circle(r=20); 
    rotate(30, [0,0,1]) {
      translate([5,0,0]) {
        circle(r=2.5); 
      }
      translate([-5,0,0]) {
        circle(r=2.5); 
      }
    }
    for (i = sideAngles) {
      rotate(i, [0,0,1]) {
        translate([20,0,0]) {
          square([10,Thickness], true);
        }
      }
    }
  }
}

