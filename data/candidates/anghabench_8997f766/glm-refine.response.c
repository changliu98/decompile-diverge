int __cdecl raid6_next_disk(int disk, int raid_disks)
{
    return (disk + 1) % raid_disks;
}