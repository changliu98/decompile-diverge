void ZB_reset(ZBuffer * zb)
{
    zb->flags &= ~(1 << 9);
    zb->flags |= (0 << 9);
}