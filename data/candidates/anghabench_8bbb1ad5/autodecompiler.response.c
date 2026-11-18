static void RewindBitPosition(unsigned long storage_ix,
                            unsigned long *last_ix,
                            char *storage)
{
    unsigned long bitpos = storage_ix % 8;
    unsigned long mask = ((unsigned long)1 << bitpos) - 1;

    storage[storage_ix / 8] &= (char)(mask & 0xff);
    *last_ix = storage_ix;
}