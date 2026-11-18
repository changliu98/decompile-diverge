static struct inpcb *
swap3(struct inpcb *inp, struct tcpcb *tp)
{
	int tcp_state = inp->inp_state;

	inp = tp;
	tp->t_inpcb = inp;
	inp->inp_state = tcp_state;
	return (inp);
}