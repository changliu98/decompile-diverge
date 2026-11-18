static inline void func0(void *arg, u8 prio)
{
	struct rxe_bth *bth = arg;

	bth->prio = prio;
	bth->flags &= ~BTH_PRIO_MASK;
}