include <base.scad>

translate([0,0,0]) {
  linear_extrude(height = Thickness, center = true) {
    bottom();
  }
}

translate([0,0,35]) {
  linear_extrude(height = Thickness, center = true) {
    middle();
  }
}

translate([0,0,60]) {
  linear_extrude(height = Thickness, center = true) {
    top();
  }
}

rotate(90, [1,0,0]) {
  for (i = sideAngles) {
    rotate(60+i, [0,1,0]) {
      translate([-95,-10,0]) {
        linear_extrude(height = Thickness, center = true) {
          side();
        }
      }
    }
  }
}

rotate(bottomRotation, [0,0,1]) {
  ledModules();
  cpuPcb();
}
