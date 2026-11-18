int __cdecl func0(int *data_list, int n)
{
    int sub_length; // length of the sub-list following a negative marker
    int i;          // current index in the outer scan
    int next_i;     // index immediately after a marker (start of sub-list)
    int total;      // running accumulator

    total = 0;
    for (i = 0; i < n; ++i)
    {
        if (data_list[i] >= 0)
        {
            // Literal value: contribute it directly.
            total += data_list[i];
        }
        else
        {
            // Marker: -data_list[i] == number of following entries to recurse on.
            sub_length = -data_list[i];
            next_i = i + 1;

            // Recursively sum the sub-list and fold it in.
            total += func0(&data_list[next_i], sub_length);

            // Skip past the sub-list. The for-loop's ++i then positions
            // i at the entry immediately following the sub-list.
            i = next_i + sub_length - 1;
        }
    }
    return total;
}