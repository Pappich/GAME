#include "state.h"

int currentstate = 0;
int state::currentstate()
{
	return state;
}

void state::nextstate(int s)
{
	state = s;
}
