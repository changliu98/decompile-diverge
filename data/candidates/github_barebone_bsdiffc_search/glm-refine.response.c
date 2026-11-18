int64_t __cdecl search(
        const int64_t *suffix_array,
        const uint8_t *old_data,
        int64_t old_size,
        const uint8_t *new_data,
        int64_t new_size,
        int64_t start_idx,
        int64_t end_idx,
        int64_t *out_pos)
{
    // Base case: if the search range is small enough, check both boundaries directly
    if (end_idx - start_idx < 2)
    {
        int64_t len_start = matchlen(&old_data[suffix_array[start_idx]], old_size - suffix_array[start_idx], new_data, new_size);
        int64_t len_end   = matchlen(&old_data[suffix_array[end_idx]],   old_size - suffix_array[end_idx],   new_data, new_size);

        if (len_start > len_end)
        {
            *out_pos = suffix_array[start_idx];
            return len_start;
        }
        else
        {
            *out_pos = suffix_array[end_idx];
            return len_end;
        }
    }

    // Recursive case: binary search
    int64_t mid_idx = start_idx + (end_idx - start_idx) / 2;
    const uint8_t *suffix_mid = &old_data[suffix_array[mid_idx]];
    
    // Compare the middle suffix with the new data
    int cmp_result;
    int64_t available_len = old_size - suffix_array[mid_idx];
    if (available_len >= new_size)
    {
        cmp_result = memcmp(suffix_mid, new_data, new_size);
    }
    else
    {
        cmp_result = memcmp(suffix_mid, new_data, available_len);
    }

    // Narrow the search range based on the comparison
    if (cmp_result >= 0)
    {
        return search(suffix_array, old_data, old_size, new_data, new_size, start_idx, mid_idx, out_pos);
    }
    else
    {
        return search(suffix_array, old_data, old_size, new_data, new_size, mid_idx, end_idx, out_pos);
    }
}