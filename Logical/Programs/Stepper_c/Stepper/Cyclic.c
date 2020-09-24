
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
			stepperMotor_x.MpAxis.Parameters = &stepperMotor_x.AxisParameter;
			
			stepperMotor_y.MpAxis.MpLink = &stepper_y;
			stepperMotor_y.MpAxis.Enable = 1;
			stepperMotor_y.MpAxis.Parameters = &stepperMotor_y.AxisParameter;
			
			stepperProgramState.state = POWERON;
			break;
		case POWERON:
			brsstrcpy(stepperProgramState.stateInfo,"Power on stepper motor");
			//&& stepperMotor_y.MpAxis.Info.ReadyToPowerOn
			if(stepperMotor_x.MpAxis.Info.ReadyToPowerOn ){
				stepperMotor_x.MpAxis.Power = TRUE;
				//stepperMotor_y.MpAxis.Power = TRUE;
				
				stepperProgramState.state = HOME;
			}
			break;
		case HOME:
			brsstrcpy(stepperProgramState.stateInfo,"Moving Gantry to home position");
			//move motor x until limit switch is reached
			//move motor y until limit switch is reached
			//&& stepperMotor_y.MpAxis.PowerOn
			if(stepperMotor_x.MpAxis.PowerOn){
				stepperMotor_x.MpAxis.Home = TRUE; //remember to update this!!!!
				//stepperMotor_y.MpAxis.Home = TRUE; //remember to update this!!!!
				stepperProgramState.state = OPERATION;
			}
			break;
		
		case OPERATION:
			brsstrcpy(stepperProgramState.stateInfo,"Normal operation ready");
			//send position feedback via OPC UA to ROS
			stepperMotor_x.poseFeedback = stepperMotor_x.MpAxis.Position;
			//stepperMotor_y.poseFeedback = stepperMotor_y.MpAxis.Position;
			
			
			if( stepperMotor_x.motorGoal == stepperMotor_x.MpAxis.Position){
				stepperMotor_x.MpAxis.MoveAbsolute = FALSE;
				break;
			}
			/*
			if( stepperMotor_y.motorGoal == stepperMotor_y.MpAxis.Position){
				stepperMotor_y.MpAxis.MoveAbsolute = FALSE;
				break;
			}*/
			
			if(!stepperMotor_x.MpAxis.MoveActive && !stepperMotor_x.MpAxis.MoveAbsolute){	
				stepperMotor_x.AxisParameter.Position = stepperMotor_x.motorGoal;
				stepperMotor_x.MpAxis.MoveAbsolute = TRUE;
				break;
			}
			/*
			if(!stepperMotor_y.MpAxis.MoveActive && !stepperMotor_y.MpAxis.MoveAbsolute){	
				stepperMotor_y.AxisParameter.Position = stepperMotor_y.motorGoal;
				stepperMotor_y.MpAxis.MoveAbsolute = TRUE;
				break;
			}*/
			/*
			if(stepperMotor_x.MpAxis.MoveDone && stepperMotor_x.MpAxis.MoveAbsolute){
				stepperMotor_x.MpAxis.MoveAbsolute = FALSE;
			}
			*/
			break;
		case ERROR:
			brsstrcpy(stepperProgramState.stateInfo,"Error");
			break;
		case STOP:
			brsstrcpy(stepperProgramState.stateInfo,"Stopping");
			break;
	}
	MpAxisBasic(&stepperMotor_x.MpAxis);
	
}
