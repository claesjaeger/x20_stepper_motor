
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#include <general.h>
#include <stepper.h>

void _CYCLIC ProgramCyclic(void)
{
	switch(stepperProgramState.state){
		case INIT:
			brsstrcpy(stepperProgramState.stateInfo,"Initialize stepper motor");
			stepperMotor_x.MpAxis.MpLink = &stepper_x;
			stepperMotor_x.MpAxis.Enable = 1;
			stepperMotor_x.AxisParameter.Velocity = 3.0;
			stepperMotor_x.AxisParameter.Acceleration = 8.0;
			stepperMotor_x.AxisParameter.Deceleration = 8.0;
			stepperMotor_x.MpAxis.Parameters = &stepperMotor_x.AxisParameter;
						
			stepperMotor_y.MpAxis.MpLink = &stepper_y;
			stepperMotor_y.MpAxis.Enable = 1;
			stepperMotor_y.AxisParameter.Velocity = 3.0;
			stepperMotor_y.AxisParameter.Acceleration = 8.0;
			stepperMotor_y.AxisParameter.Deceleration = 8.0;
			stepperMotor_y.MpAxis.Parameters = &stepperMotor_y.AxisParameter;
			
			stepperProgramState.state = POWERON;
			break;
		case POWERON:
			brsstrcpy(stepperProgramState.stateInfo,"Power on stepper motor");
			
			if(stepperMotor_x.MpAxis.Info.ReadyToPowerOn && stepperMotor_y.MpAxis.Info.ReadyToPowerOn){
				stepperMotor_x.MpAxis.Power = TRUE;
				stepperMotor_y.MpAxis.Power = TRUE;
				
				stepperProgramState.state = HOME;
			}
			break;
		case HOME:
			brsstrcpy(stepperProgramState.stateInfo,"Moving Gantry to home position");
			//move motor x until limit switch is reached
			//move motor y until limit switch is reached
			
			if(stepperMotor_x.MpAxis.PowerOn && stepperMotor_y.MpAxis.PowerOn){
				//TODO: Move axis to home switch then:
				stepperMotor_x.MpAxis.Home = TRUE; 
				stepperMotor_y.MpAxis.Home = TRUE; 
				homeReached = TRUE;
				stepperProgramState.state = OPERATION;
			}
			break;
		
		case OPERATION:
			brsstrcpy(stepperProgramState.stateInfo,"Normal operation ready");
			//send position feedback via OPC UA to ROS
			// TODO: add a recalculation function to return valuea in world coordinate
			stepperMotor_x.poseFeedback = stepperMotor_x.MpAxis.Position;
			stepperMotor_y.poseFeedback = stepperMotor_y.MpAxis.Position;
			
			if(stepperMotor_x.MpAxis.Position != 0 || stepperMotor_y.MpAxis.Position != 0){
				homeReached = FALSE;
			}
			
			if(goHomeGoal) {
				stepperMotor_x.AxisParameter.Position = 0;
				stepperMotor_y.AxisParameter.Position = 0;
				stepperMotor_x.motorGoal = 0;
				stepperMotor_y.motorGoal = 0;
			}
			else {
				//TODO: add recalculation function from world coordinate to gantry coordinate
				stepperMotor_x.AxisParameter.Position = stepperMotor_x.motorGoal;
				stepperMotor_y.AxisParameter.Position = stepperMotor_y.motorGoal;
			}
			
			//Navigation stack lets robot move
			stepperMotor_x.MpAxis.MoveAbsolute = stepperMotor_x.allowMovement;
			stepperMotor_y.MpAxis.MoveAbsolute = stepperMotor_y.allowMovement;
			
			if(goHomeGoal && stepperMotor_x.MpAxis.Position == 0 && stepperMotor_y.MpAxis.Position == 0) {
				homeReached = TRUE;
			}
			
			break;
		case ERROR:
			brsstrcpy(stepperProgramState.stateInfo,"Error");
			break;
		case STOP:
			brsstrcpy(stepperProgramState.stateInfo,"Stopping");
			break;
	}
	MpAxisBasic(&stepperMotor_x.MpAxis);
	MpAxisBasic(&stepperMotor_y.MpAxis);
	
}
