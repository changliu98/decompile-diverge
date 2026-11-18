/*
 * Determines the smallest C integer type that can hold the range [lwr, upr].
 *
 * Parameters:
 *   lwr  - Lower bound of the required range (inclusive)
 *   upr  - Upper bound of the required range (inclusive)
 *   pnByte - Pointer to store the size in bytes of the selected type.
 *            Can be NULL if the size is not needed.
 *
 * Returns:
 *   A string literal representing the name of the smallest suitable type.
 *   Possible return values: "signed char", "short", "int",
 *                           "unsigned char", "unsigned short int", "unsigned int"
 */
char * minimum_size_type(int lower_bound, int upper_bound, int *out_byte_size)
{
    /* Default to int (4 bytes) if no smaller type fits */
    int byte_size = 4;
    char *type_name = "int";

    /* Check if the range includes negative numbers */
    if (lower_bound < 0) {
        /*
         * If the lower bound is less than -127 or the upper bound is greater than 127,
         * a signed char (-128 to 127) cannot hold the range.
         */
        if (lower_bound < -0x7f || 0x7f < upper_bound) {
            /*
             * Check if the range fits within a signed short (-32768 to 32767).
             * Note: -0x8000 is -32768 and 0x7fff is 32767.
             */
            if (-0x8000 < lower_bound && upper_bound < 0x7fff) {
                type_name = "short";
                byte_size = 2;
            }
        } else {
            /*
             * The range fits within a signed char (-128 to 127).
             * Since lwr < 0 and upr <= 127, and lwr >= -128 (implied by not falling into the above),
             * signed char is sufficient.
             */
            type_name = "signed char";
            byte_size = 1;
        }
    } else {
        /* The range is entirely non-negative (lwr >= 0) */

        /* Check if the range fits within an unsigned char (0 to 255) */
        if (upper_bound < 0x100) {
            type_name = "unsigned char";
            byte_size = 1;
        }
        /* Check if the range fits within an unsigned short (0 to 65535) */
        else if (upper_bound < 0xffff) {
            type_name = "unsigned short int";
            byte_size = 2;
        }
        /* Otherwise, use unsigned int */
        else {
            type_name = "unsigned int";
            byte_size = 4;
        }
    }

    /* Output the size in bytes if the caller requested it */
    if (out_byte_size != NULL) {
        *out_byte_size = byte_size;
    }

    return type_name;
}