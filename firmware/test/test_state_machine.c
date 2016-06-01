#include "unity.h"
#include "state_machine.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_single_state( void )
{
	struct StateMachine sm;

	struct State states[] = { {0, 2, NULL, NULL, NULL } };

	initialize_state_machine( &sm, states, 1 );

	TEST_ASSERT( sm.numStates == 1 );
	TEST_ASSERT( sm.count == 0 );
	TEST_ASSERT( sm.curIdx == 0 );

	for( int i = 1; i < 4; ++i ) {
		state_machine_step( &sm );
		TEST_ASSERT( sm.count == i );
		TEST_ASSERT( sm.curIdx == 0 );
	}

}


int status;
void onEntry( struct StateMachine *sm )
{
	status = 0;
}

void onIdle( struct StateMachine *sm )
{
	++status;
}

void onExit( struct StateMachine *sm )
{
	status = 99;
}

void test_multiple_states( void )
{
	struct StateMachine sm;
	struct State states[] = { {0, 2, onEntry, onIdle, onExit },
 														{1, 0, NULL, onIdle, NULL }};

	int expect[] = { 1, 100, 101, 102, 103 };

	initialize_state_machine( &sm, states, 2 );

	TEST_ASSERT( sm.numStates == 2 );
	TEST_ASSERT( sm.curIdx == 0 );

	for( int i = 0; i < 5; ++i ) {
		state_machine_step( &sm );
		TEST_ASSERT( status == expect[i] );

		if( i > 2 ) {
			TEST_ASSERT( sm.curIdx == 1 );
		}
	}

}
