/**
 * @brief Calculates grid addresses based on double precision addresses and pixel size.
 *
 * @param address       Pointer to the array where the resulting grid addresses will be stored.
 * @param address_double Pointer to the array containing the double precision addresses.
 * @param PS            Pointer to the array containing the pixel size values.
 */
void get_grid_address(long *grid_addresses, long *double_precision_addresses, long *pixel_sizes)
{
    // Iterate through the first three elements of the arrays
    for (int i = 0; i < 3; i++) {
        // Calculate the grid address by subtracting the pixel size from the double address
        // and dividing by 2, then store the result in the address array
        grid_addresses[i] = (double_precision_addresses[i] - pixel_sizes[i]) / 2;
    }
}