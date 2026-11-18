void validate_st_entry(struct st_entry *entry)
{
	entry->flags &= ~0x0020;
	entry->flags &= ~0x0002;
}