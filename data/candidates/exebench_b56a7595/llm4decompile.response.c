void rotr(uint32_t *a, uint32_t *b, uint32_t *c)
{
 uint32_t tmp;
 tmp = *c; *c = *b; *b = *a; *a = tmp;
}