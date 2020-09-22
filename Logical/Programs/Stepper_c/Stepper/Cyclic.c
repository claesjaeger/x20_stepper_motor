
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
			stepperProgramState.state = POWERON;
			break;
		case POWERON:
			brsstrcpy(stepperProgramState.stateInfo,"Power on stepper motor");
			if(stepperMotor_x.MpAxis.Info.ReadyToPowerOn){
				stepperMotor_x.MpAxis.Power = TRUE;
				
				stepperProgramState.state = HOME;
			}
			break;
		case HOME:
			brsstrcpy(stepperProgramState.stateInfo,"Power on stepper motor");
			if(stepperMotor_x.MpAxis.PowerOn){
				stepperMotor_x.MpAxis.Home = TRUE; //remember to update this!!!!
				stepperProgramState.state = OPERATION;
			}
			break;
		
		case OPERATION:
			brsstrcpy(stepperProgramState.stateInfo,"Normal operation ready");
			stepperMotor_x.poseFeedback = stepperMotor_x.MpAxis.Position;
			if( stepperMotor_x.motorGoal == stepperMotor_x.MpAxis.Position){
				stepperMotor_x.MpAxis.MoveAbsolute = FALSE;
				break;
			}
			
			if(!stepperMotor_x.MpAxis.MoveActive && !stepperMotor_x.MpAxis.MoveAbsolute){	
				stepperMotor_x.AxisParameter.Position = stepperMotor_x.motorGoal;
				stepperMotor_x.MpAxis.MoveAbsolute = TRUE;
				break;
			}
			if(stepperMotor_x.MpAxis.MoveDone && stepperMotor_x.MpAxis.MoveAbsolute){
				stepperMotor_x.MpAxis.MoveAbsolute = FALSE;
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
	
}
