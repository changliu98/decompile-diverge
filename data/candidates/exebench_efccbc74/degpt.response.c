int meat_time_which_month(uchar *input_bytes, size_t input_length)
{
    // Validate that the input length is exactly 3 bytes
    if (input_length != 3) {
        return -1;
    }
    // Iterate through the reference month table (12 entries)
    for (int month_index = 0; month_index < 0xc; month_index++) {
        // Check if the input bytes match the current reference month entry
        if (input_bytes[0] == meat_time_which_month::reference_months[month_index][0] &&
            input_bytes[1] == meat_time_which_month::reference_months[month_index][1] &&
            input_bytes[2] == meat_time_which_month::reference_months[month_index][2]) {
            // Return the index of the matching month
            return month_index;
        }
    }
    // Return -1 if no match is found
    return -1;
}