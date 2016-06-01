
#include <stdlib.h>

#include <stdio.h>

#include "state_machine.h"

void initialize_state_machine( struct StateMachine *sm, struct State *states, int numStates )
{
	sm->states = states;
	sm->numStates = numStates;
	sm->curIdx = sm->nextIdx = 0;
	sm->count = 0;
	sm->once = true;
}

void state_machine_step( struct StateMachine *sm )
{
	++sm->count;

	if( (sm->numStates > 1 &&
		sm->states[sm->curIdx].duration > 0  &&
			sm->count > sm->states[sm->curIdx].duration &&
			sm->curIdx < sm->numStates-1 ) ||
			sm->nextIdx != sm->curIdx ) {

		if( sm->nextIdx == sm->curIdx ) sm->nextIdx++;

		if(sm->states[sm->curIdx].exitFunc != NULL) sm->states[sm->curIdx].exitFunc( sm );

		sm->curIdx = sm->nextIdx;
		sm->count = 0;

		if( sm->states[sm->curIdx].entryFunc != NULL ) sm->states[sm->curIdx].entryFunc( sm );

	} else if( sm->once == true && sm->states[sm->curIdx].entryFunc != NULL) {
		sm->states[sm->curIdx].entryFunc( sm );
		sm->once = false;
	}

	if( sm->states[sm->curIdx].inFunc != NULL ) sm->states[sm->curIdx].inFunc( sm );
}

bool state_machine_next_idx( struct StateMachine *sm, int idx )
{
	if( idx >= 0 && idx < sm->numStates ) {
		sm->nextIdx = idx;
		return true;
	}

	return false;
}

bool state_machine_next_id( struct StateMachine *sm, int id )
{
	for( int i = 0; i < sm->numStates; ++i ) {
		if( id == sm->states[ i ].id ) return state_machine_next_idx( sm, i );
	}

	return false;
}
