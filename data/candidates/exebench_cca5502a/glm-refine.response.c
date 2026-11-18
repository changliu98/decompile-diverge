int __cdecl modpars_to_struct(float *out_val, int *var_index, int *max_index, float *default_val, float *link_array)
{
    int current_index = *var_index;

    // Case 1: Index is 1. Initialize the value and return 1.
    if (current_index == 1)
    {
        *out_val = *default_val;
        return 1;
    }

    // Case 2: Index is within the valid range [2, max_index]. Fetch the linked value and return 0.
    if (current_index <= *max_index)
    {
        // current_index > 1 is implicitly true here because of the prior check.
        *out_val = link_array[current_index - 2];
        return 0;
    }

    // Case 3: Index is greater than max_index. Update the max_index, store the new value, and return 1.
    *out_val = *default_val;
    *max_index = current_index;
    link_array[current_index - 2] = *default_val;
    
    return 1;
}