__attribute__((used)) static void stack4_push(struct sbuf *b, u_char c)
{
	b->ptr = (b->ptr << 4) | c;
}