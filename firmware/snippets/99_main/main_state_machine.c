
#include "main_state_machine.h"

#include "power_reset.h"
#include "led.h"

#include <stdlib.h>

struct StateMachine sm;

enum States { ON_STARTUP,
								START_JETSON,
								JETSON_STARTUP,
								JETSON_IDLE };

static void pressJetsonPower( struct StateMachine *sm )
{
	do_power_jetson( true );
}

static void releaseJetsonPower( struct StateMachine *sm )
{
	do_power_jetson( false );
}

static void onIdle( struct StateMachine *sm )
{
	if( sm->count % 32 == 0 ) led_toggle(LED2);
}


struct State states[] = { {ON_STARTUP, ON_STARTUP_CYCLES, NULL, NULL, NULL },
													{START_JETSON, START_JETSON_CYCLES, pressJetsonPower, NULL, releaseJetsonPower },
													{JETSON_STARTUP, JETSON_STARTUP_CYCLES, NULL, NULL, NULL },
													{JETSON_IDLE, 0, NULL, onIdle, NULL }};


void init_state_machine( void )
{
	initialize_state_machine( &sm, states, sizeof( states )/sizeof( struct State ) );
}

void service_state_machine( void )
{
	state_machine_step( &sm );
}
