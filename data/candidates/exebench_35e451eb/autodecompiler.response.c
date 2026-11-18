void adjust_point(DiskSpace *disk)
{
    if (disk->free_space_percent < 0) {
        disk->free_space_percent = 0;
        return;
    }
    if (disk->free_space_percent > 100) {
        disk->free_space_percent = 100;
        return;
    }
}