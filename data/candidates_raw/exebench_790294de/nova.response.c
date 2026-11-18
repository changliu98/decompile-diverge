static void func0(struct task_struct *task, unsigned long mask)
{
	unsigned long *p = &task->signal->flags;
	unsigned long old, new;

	do {
		old = *p;
		new = old | mask;
	} while (cmpxchg(p, old, new)!= old);
}