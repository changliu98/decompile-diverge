/**
 * Converts a float from host byte order to network byte order.
 *
 * @param x Pointer to the float value to be converted.
 */
void htonf(float *value)
{
    // Cast the float to uint32_t, convert to network byte order, then cast back to float
    *value = (float)htonl((uint32_t)*value);
}