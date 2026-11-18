void entry_clr_protected(struct _rt_entry *entry)
{
  entry->flags &= ~0x00000200;
  entry->flags = entry->flags;
  return;
}