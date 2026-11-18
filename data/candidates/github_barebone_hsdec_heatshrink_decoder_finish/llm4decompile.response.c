HSD_finish_res heatshrink_decoder_finish(heatshrink_decoder *hsd) {
    if (hsd == NULL) { return HSDR_FINISH_ERROR_NULL; }
    switch (hsd->state) {
        case 0:

            if (hsd->input_size != 0) { return HSDR_FINISH_MORE; }
            return HSDR_FINISH_DONE;
        case 1:

            if (hsd->input_size != 0) { return HSDR_FINISH_MORE; }
            return HSDR_FINISH_DONE;
        case 2:

            if (hsd->input_size != 0) { return HSDR_FINISH_MORE; }
            return HSDR_FINISH_DONE;
        case 3:

            if (hsd->input_size != 0) { return HSDR_FINISH_MORE; }
            return HSDR_FINISH_DONE;
        case 4:

            if (hsd->input_size != 0) { return HSDR_FINISH_MORE; }
            return HSDR_FINISH_DONE;
        case 5:

            if (hsd->input_size != 0) { return HSDR_FINISH_MORE; }
            return HSDR_FINISH_DONE;
        default:
            return HSDR_FINISH_MORE;
    }
}