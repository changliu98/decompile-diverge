void stack4_push(stack4 *s, u8 e)
{
    s->data = (s->data << 4) | e;
}