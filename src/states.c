#include "states.h"

static const game_state_t *current_state = NULL;
static const game_state_t *next_state = NULL;

static void process_state_transition(void)
{
    if (next_state == current_state)
        return;

    if (current_state != NULL && current_state->quit != NULL)
        current_state->quit();
    current_state = next_state;
    if (current_state != NULL && current_state->init != NULL)
        current_state->init();
}

void states_EnterState(const game_state_t *new_state)
{
    next_state = new_state;
}

void states_Init(const game_state_t *initial_state)
{
    states_EnterState(initial_state);
    process_state_transition();
}

void states_Step(void)
{
    if (current_state == NULL)
        return;

    if (current_state->step != NULL)
        current_state->step();
    process_state_transition();
    if (current_state != NULL && current_state->draw != NULL)
        current_state->draw();
}

bool states_ShouldClose(void)
{
    return current_state == NULL;
}