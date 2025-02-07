#include "command/Arm.h"

// Called when the command is initially scheduled.
void ArmCommand::initialize() {}
// Called every time the scheduler runs while the command is scheduled.
void ArmCommand::execute() {}
// Called once the command ends or is interrupted.
void ArmCommand::end(bool interrupted) {}
// Returns true when the command should end.
bool ArmCommand::isFinished() {return false;}