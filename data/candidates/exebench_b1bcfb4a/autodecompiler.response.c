static void dpaa_set_bits(unsigned long flag, struct thread_state *state)
{
 state->flags |= flag;
}