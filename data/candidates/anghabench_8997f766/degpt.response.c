// Calculates the next disk index in a RAID array, wrapping around to 0 if the end is reached.
int raid6_next_disk(int current_disk, int total_disks)
{
    // Compute the next disk index
    int next_disk_index = current_disk + 1;
    // Wrap around to the first disk if the next index exceeds the total number of disks
    if (total_disks <= next_disk_index) {
        next_disk_index = 0;
    }
    // Return the calculated next disk index
    return next_disk_index;
}