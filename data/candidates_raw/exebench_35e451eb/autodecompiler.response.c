void validate_and_set_disk_space(DiskSpace *disk)
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