static void chg_write_unlock(struct vio_dring_state *dr)
{
 dr->flags &= ~((1UL << 0));
}