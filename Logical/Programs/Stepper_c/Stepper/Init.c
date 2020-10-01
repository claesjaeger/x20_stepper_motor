
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#include <general.h>1
#include <stepper.h>

void _INIT ProgramInit(void)
{
	stepperProgramState.state = INIT;
	homeReached = FALSE;
	goHomeGoal = FALSE;
	

	
}
