include <base.scad>

bottom();

translate([160,0,0]) {
  middle();
  top();
}

translate([230,-60,0]) {
  for (i = [0:NumSides-1]) {
      translate([i*40,0,0]) {
          side();
      }
  }
}
