PROGRAM _INIT
    
	MpAxisBasic_0.MpLink := ADR("stepper_x");
	MpAxisBasic_0.Enable := TRUE;
	MpAxisBasic_0.Parameters := ADR(AxisParameters);
    
	AxisParameters.Position := 100.0;
	AxisParameters.Velocity := 7.0;
	AxisParameters.Acceleration := 50.0;
	AxisParameters.Deceleration := 50.0;
	
	//MpAxisBasic_1.MpLink := ADR(gAxis_2);
	//MpAxisBasic_1.Enable := TRUE;
	//MpAxisBasic_1.Parameters := ADR(AxisParameters1);
    
	//AxisParameters1.Position := 100.0;
	//AxisParameters1.Velocity := 7.0;
	//AxisParameters1.Acceleration := 50.0;
	//AxisParameters1.Deceleration := 50.0;
	
	limitswitch_X;
	limitswitch_Y;
	encoder_x := 0;
	
	encoder_y := 0;
     
END_PROGRAM

PROGRAM _CYCLIC
    
	MpAxisBasic_0();
     
END_PROGRAM

PROGRAM _EXIT

	MpAxisBasic_0.Power  := FALSE;
	MpAxisBasic_0.Home   := FALSE;
	MpAxisBasic_0.MoveAbsolute := FALSE;
	MpAxisBasic_0.MoveAdditive := FALSE;
	MpAxisBasic_0.MoveVelocity := FALSE;
	MpAxisBasic_0.Stop         := FALSE;
	MpAxisBasic_0.ErrorReset   := FALSE;
	MpAxisBasic_0();

	MpAxisBasic_0.Enable := FALSE;
	MpAxisBasic_0();
     
END_PROGRAM