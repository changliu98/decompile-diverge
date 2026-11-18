void entry_clr_protected(ZBuffer * zb)
{
    zb->flags &= ~(1 << 9);
    zb->flags |= (0 << 9);
}