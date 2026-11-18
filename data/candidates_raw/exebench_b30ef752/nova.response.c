static void func0(struct sock *sk, unsigned short nr,
				  unsigned short mr)
{
	if (sk->sk_ack_backoff < nr)
		sk->sk_ack_backoff = nr;
	else if (sk->sk_ack_backoff > mr)
		sk->sk_ack_backoff = mr;
}