#include <vex.h>
void approach_tag(float stopWidth) {
  while (true) {
    AIVision.takeSnapshot(aivision::ALL_TAGS);
    if (AIVision.objectCount > 0) {
      float w = AIVision.objects[0].width;
      if (w >= stopWidth) { chassis.drive_distance(0); break; }
      chassis.drive_with_voltage(4.8, 4.8);
    }
    wait(10, msec);
  }
}
void align_to_tag(float targetID) {
  while (true) {
    AIVision.takeSnapshot(aivision::ALL_TAGS);

    if (AIVision.objectCount > 0) {
      float id  = AIVision.objects[0].id;
      float cx  = AIVision.objects[0].centerX;

      if (id != targetID) { wait(20, msec); continue; }

      if (cx < 140) {
        LeftFront.spin(vex::directionType::fwd, -9, volt);
        LeftBack.spin(vex::directionType::fwd, -9, volt);
        RightFront.spin(vex::directionType::fwd, 9, volt);
        RightBack.spin(vex::directionType::fwd, 9, volt);
      } else if (cx > 180) {
        LeftFront.spin(vex::directionType::fwd, 9, volt);
        LeftBack.spin(vex::directionType::fwd, 9, volt);
        RightFront.spin(vex::directionType::fwd, -9, volt);
        RightBack.spin(vex::directionType::fwd, -9, volt);
      } else {
        LeftFront.stop();
        LeftBack.stop();
        RightFront.stop();
        RightBack.stop();
        break;
      }
    }
    wait(10, msec);
  }
}