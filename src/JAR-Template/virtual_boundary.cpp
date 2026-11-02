#include "vex.h"
extern Drive chassis;
static BoundaryLine boundary;
static double cross(double px, double py) {
  return (boundary.x2 - boundary.x1) * (py - boundary.y1)
       - (boundary.y2 - boundary.y1) * (px - boundary.x1);
}
void set_boundary(double x1, double y1, double x2, double y2) {
  boundary.x1 = x1;
  boundary.y1 = y1;
  boundary.x2 = x2;
  boundary.y2 = y2;
  double cx   = chassis.get_X_position();
  double cy   = chassis.get_Y_position();
  double side = cross(cx, cy);
  boundary.allowed_sign = (side >= 0.0) ? 1.0 : -1.0;
  boundary.active       = true;
}
void clear_boundary() {
  boundary.active = false;
}
bool within_boundary(double x, double y) {
  if (!boundary.active) return true;
  return (cross(x, y) * boundary.allowed_sign) >= 0.0;
}

bool safe_to_move_to(double target_x, double target_y) {
    return within_boundary(target_x, target_y);
}
static int boundary_monitor_fn() {
  while (true) {
    if (boundary.active) {
      double x = chassis.get_X_position();
      double y = chassis.get_Y_position();

      if (!within_boundary(x, y)) {
        chassis.drive_stop(vex::brakeType::hold);
      }
    }
    task::sleep(10);
  }
  return 0;
}

void start_boundary_monitor() {
  task monitor(boundary_monitor_fn);
}
