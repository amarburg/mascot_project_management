#pragma once

#include <stdbool.h>

struct StateMachine;

struct State {
	int id;
	int duration;
	void (*entryFunc)( struct StateMachine * );
	void (*inFunc)( struct StateMachine * );
	void (*exitFunc)( struct StateMachine * );
};


struct StateMachine {
	struct State *states;
	unsigned int numStates;
	unsigned int curIdx, nextIdx;
	int count;
	bool once;
};

void initialize_state_machine( struct StateMachine *, struct State *, int numStates );

void state_machine_step( struct StateMachine * );

bool state_machine_next_idx( struct StateMachine *, int idx );
bool state_machine_next_id( struct StateMachine *, int id );
