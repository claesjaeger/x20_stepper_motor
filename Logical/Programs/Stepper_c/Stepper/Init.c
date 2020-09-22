
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#include <stepper.h>
void _INIT ProgramInit(void)
{
	stepperProgramState.state = INIT;
}
