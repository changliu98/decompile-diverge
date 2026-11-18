int __cdecl int_range_lookup(unsigned int n_ranges, const ProtobufCIntRange *ranges, int value)
{
    unsigned int low = 0;
    unsigned int high = n_ranges;

    // Handle empty range list
    if (n_ranges == 0) {
        return -1;
    }

    // Standard binary search to find the correct range block
    while (high - low > 1) {
        unsigned int mid = low + (high - low) / 2;

        if (value >= ranges[mid].start_value) {
            // Check if the value falls within the current range block.
            // The length of the range is determined by the difference in 
            // orig_index between the current block and the next block.
            int range_length = ranges[mid + 1].orig_index - ranges[mid].orig_index;
            int range_end = ranges[mid].start_value + range_length;

            if (value < range_end) {
                // Value found in this range. Map it back to the original index.
                return ranges[mid].orig_index + (value - ranges[mid].start_value);
            }
            // Value is above the current block, search the upper half
            low = mid + 1;
        } else {
            // Value is below the current block, search the lower half
            high = mid;
        }
    }

    // Final check for the last remaining range block (when high - low == 1)
    if (high > low) {
        const ProtobufCIntRange *current_range = &ranges[low];
        int range_length = ranges[low + 1].orig_index - current_range->orig_index;
        int range_end = current_range->start_value + range_length;

        if (value >= current_range->start_value && value < range_end) {
            return current_range->orig_index + (value - current_range->start_value);
        }
    }

    // Value does not fall into any defined range
    return -1;
}