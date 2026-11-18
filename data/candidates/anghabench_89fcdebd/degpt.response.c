/*
 * Calculate the number of Command Status (CT) IOCBs required for a given
 * Data Segment Descriptor Count (dsds).
 *
 * Parameters:
 *   dsds - The number of data segment descriptors.
 *
 * Returns:
 *   The number of CT IOCBs needed to handle the specified number of segments.
 *   For dsds <= 2, a single IOCB is sufficient.
 *   For dsds > 2, the calculation accounts for the first 2 segments plus
 *   additional segments grouped in batches of 5, with an offset adjustment.
 */
uint16_t qla24xx_calc_ct_iocbs(uint16_t num_data_segments)
{
    /* If the number of data segments is 2 or fewer, only one IOCB is needed. */
    if (num_data_segments <= 2) {
        return 1;
    }
    /*
     * For more than 2 segments, calculate the required IOCBs.
     * The formula (dsds - 2 + 4) / 5 + 1 effectively groups the remaining
     * segments (after the first 2) into chunks of 5, adding 1 for the initial
     * IOCB and adjusting for integer division rounding.
     */
    return (num_data_segments - 2 + 4) / 5 + 1;
}