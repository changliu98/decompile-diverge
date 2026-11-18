__attribute__((used)) static void add_byte(struct sbuf *b, u_char c)
{
	b->ptr = (b->ptr << 4) | c;
}