void entry_clr_protected(struct cache_entry *ent)
{
	ent->flags &= ~(1 << 9);
	ent->flags &= ~(1 << 10);
}