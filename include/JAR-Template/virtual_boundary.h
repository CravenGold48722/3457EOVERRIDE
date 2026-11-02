#pragma once
#include "vex.h"
struct BoundaryLine {
  double x1, y1;
  double x2, y2;
  double allowed_sign; 
  bool   active = false;
};
void set_boundary(double x1, double y1, double x2, double y2);
void clear_boundary();
bool within_boundary(double x, double y);
bool safe_to_move_to(double target_x, double target_y);
void start_boundary_monitor();
