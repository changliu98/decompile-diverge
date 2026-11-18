void advance_m2pos(struct m2pos *p)
{
 p->i = (p->i + 1) % 37;
}