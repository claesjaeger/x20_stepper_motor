
TYPE
	programState : 	STRUCT 
		state : USINT;
		stateInfo : STRING[80];
	END_STRUCT;
	stepperMotor : 	STRUCT 
		motorGoal : LREAL; (*Position to move to*)
		poseFeedback : LREAL; (*Current position of the stepper*)
		allowMovement : USINT;
		errorCode : BYTE;
		interface : STRING[80];
		AxisParameter : MpAxisBasicParType;
		MpAxis : MpAxisBasic;
	END_STRUCT;
END_TYPE
