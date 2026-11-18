HSD_finish_res heatshrink_decoder_finish(heatshrink_decoder *hsd) {
    if (hsd == NULL) { return HSDR_FINISH_ERROR_NULL; }
    switch (hsd->state) {
    case HSDS_TAG_BIT:
        return hsd->input_size == 0 ? HSDR_FINISH_DONE : HSDR_FINISH_MORE;

    /* If we want to finish with no input, but are in these states, it's
     * because the 0-bit padding to the last byte looks like a backref
     * marker bit followed by all 0s for index and count bits. */
    case HSDS_BACKREF_INDEX_LSB:
    case HSDS_BACKREF_INDEX_MSB:
    case HSDS_BACKREF_COUNT_LSB:
    case HSDS_BACKREF_COUNT_MSB:
        return hsd->input_size == 0 ? HSDR_FINISH_DONE : HSDR_FINISH_MORE;

    /* If the output stream is padded with 0xFFs (possibly due to being in
     * flash memory), also explicitly check the input size rather than
     * uselessly returning MORE but yielding 0 bytes when polling. */
    case HSDS_YIELD_LITERAL:
        return hsd->input_size == 0 ? HSDR_FINISH_DONE : HSDR_FINISH_MORE;

    default:
        return HSDR_FINISH_MORE;
    }
}