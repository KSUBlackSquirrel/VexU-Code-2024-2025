#include "clamp.h"

namespace clamp{

pros::adi::DigitalOut pneumatic(globalClamp::pneumaticsID);

void init() {

}

void toggle() {
    globalClamp::pneumaticsState =! globalClamp::pneumaticsState;
    pneumatic.set_value(globalClamp::pneumaticsState);
}

void opcontrol(pros::Controller& controller) {
    if(controller.get_digital_new_press(globalClamp::pneumaticsButton)){
        toggle();
    }
}


} //namespace drive