int
int_range_lookup(unsigned n_ranges,
                 const ProtobufCIntRange *ranges,
                 int value)
{
    unsigned start = 0;
    unsigned n = n_ranges;

    if (n == 0)
        return -1;

    while (n > 1)
    {
        unsigned mid = start + (n >> 1);
        if (value < ranges[mid].start_value)
            n = mid - start;
        else
        {
            unsigned next_start = ranges[mid].start_value +
                (ranges[mid + 1].orig_index - ranges[mid].orig_index);
            if (value < next_start)
                return ranges[mid].orig_index + (value - ranges[mid].start_value);
            n -= mid + 1;
            start = mid + 1;
        }
    }

    if (n == 0)
        return -1;

    if (value < ranges[start].start_value)
        return -1;

    unsigned next_start = ranges[start].start_value +
        (ranges[start + 1].orig_index - ranges[start].orig_index);
    if (value >= next_start)
        return -1;

    return ranges[start].orig_index + (value - ranges[start].start_value);
}