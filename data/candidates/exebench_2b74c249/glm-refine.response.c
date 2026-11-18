int __cdecl setsize(unsigned __int64 capacity, unsigned int *cyls, unsigned int *hds, unsigned int *secs)
{
    unsigned __int64 cylinders = 1024;
    unsigned __int64 sectors   = 62;
    unsigned __int64 heads;
    int rv = 0;

    // Start by calculating the required number of heads 
    // assuming a fixed geometry of 1024 cylinders and 62 sectors.
    heads = capacity / (1024 * 62);

    // If there is a remainder, we need to adjust the geometry
    if (capacity % (1024 * 62))
    {
        // Recalculate sectors based on the new head count (heads * 1024)
        sectors = capacity / (heads * 1024);
        
        // If there is still a remainder, adjust the cylinder count
        if (capacity % (heads * 1024))
        {
            cylinders = capacity / (++sectors * heads);
        }
    }

    // If the calculated cylinder count dropped to 0, the capacity is too small/invalid
    if (!cylinders)
        rv = -1;

    *cyls = cylinders;
    *secs = sectors;
    *hds  = heads;

    return rv;
}