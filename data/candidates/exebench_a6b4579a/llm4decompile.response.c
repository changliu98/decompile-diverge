int lockoff(struct block *block)
{
 block->lock = 0;
 return 0;
}