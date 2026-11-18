static void _set_flag(unsigned long flag, struct thread_state *state)
{
 state->flags |= flag;
}