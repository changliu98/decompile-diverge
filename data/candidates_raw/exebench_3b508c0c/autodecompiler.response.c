void add_entry(struct STATE_DATA*sd, int entry)
{
 sd->entries = ((sd->entries) & 1) | ((entry + 1) << 1);
}