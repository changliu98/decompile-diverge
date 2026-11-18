uint32_t compute_argb_value(par_byte *pixel_data, int bytes_per_pixel)
{
    uint32_t result_value = 0;
    if (bytes_per_pixel == 4) {
        // Construct a 32-bit value from 4 bytes using nested CONCAT macros
        result_value = CONCAT13(pixel_data[3], CONCAT12(*pixel_data, CONCAT11(pixel_data[1], pixel_data[2])));
    } else {
        // Construct a 32-bit value by shifting and OR-ing each byte
        for (int byte_index = 0; byte_index < bytes_per_pixel; byte_index++) {
            result_value = (result_value << 8) | pixel_data[byte_index];
        }
    }
    return result_value;
}