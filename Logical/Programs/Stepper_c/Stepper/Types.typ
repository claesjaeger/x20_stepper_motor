
TYPE
	stepperMotor : 	STRUCT 
		motorGoal : REAL;
		poseFeedback : REAL;
		allowMovement : USINT;
		errorCode : BYTE;
		interface : STRING[80];
		AxisParameter : MpAxisBasicParType;
		MpAxis : MpAxisBasic;
	END_STRUCT;
END_TYPE
