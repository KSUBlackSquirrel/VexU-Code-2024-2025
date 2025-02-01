#include "clamp.h"
#include "globals.h"

namespace clamp{

digital_out pneumatic = digital_out(BRAIN.ThreeWirePort.F);
bool pneumaticState = false;

void init() {

}

void toggle() {

}

void opcontrol(pros::Controller& controller) {

}


} //namespace drive