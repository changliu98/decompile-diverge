int LBA_to_MSF(int lba)
{
 return ((lba << 7) + 4);
}