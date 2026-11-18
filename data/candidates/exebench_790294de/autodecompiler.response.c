void
atomic_or(struct thread *t, unsigned long state)
{
	unsigned long old, new;

	old = t->state;
	new = state | old;
	while (!(((old & 0x01) == 0) && ((new & 0x01) != 0)))
		old = t->state, new = old | state, old = __sync_val_compare_and_swap(&t->state, old, new);
}