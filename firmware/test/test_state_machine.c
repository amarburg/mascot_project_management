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

	int expect[] = { 1, 2, 100, 101, 102 };

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

bool canary;

void incrementStatus( struct StateMachine *sm )
{
	printf("increment!\n");
	++status;
}

void jumpToIdx( struct StateMachine *sm )
{
	printf("jump!\n");
	state_machine_next_id( sm, 1001 );
}

void neverCalled( struct StateMachine *sm )
{
	canary = true;
}

void test_state_transitions( void )
{
	struct StateMachine sm;
	struct State states[] = { {1001, 1, incrementStatus, NULL, NULL },
 														{1, 0, NULL, jumpToIdx, NULL },
														{2, 0, neverCalled, NULL, NULL }};

	initialize_state_machine( &sm, states, 3 );
	status = 0;
	canary = false;

	TEST_ASSERT( sm.numStates == 3 );
	TEST_ASSERT( sm.curIdx == 0 );

	for( int i = 0; i < 6; ++i ) {
		state_machine_step( &sm );
		TEST_ASSERT( canary == false );
	}
}
