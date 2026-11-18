void initialise_banding(void *ctx, struct banding_state *band, int param) {
    band->cs = output_cs;
    band->format = output_format;

    if (param == 0) {
        if (band->cs == 1) {
            band->cs = 0;
            band->format = 0;
        } else if (band->cs == 2) {
            band->cs = 0;
            if (band->format == 4) {
                band->format = 3;
            } else {
                band->format = 0;
            }
        }
    }

    int ncomp;
    switch (band->cs) {
        case 0:
            ncomp = 1;
            break;
        case 1:
            ncomp = 2;
            break;
        case 2:
        default:
            ncomp = 3;
            break;
    }

    int height = band->y1 - band->y0;
    long bytes_per_line = (long)ncomp * (long)height * (long)min_band_height;
    int num_bands = max_band_memory / bytes_per_line;
    
    if (num_bands < 1) {
        num_bands = 1;
    }

    if (band->band_count > 0) {
        int width = band->x1 - band->x0;
        int min_bands_needed = (width + min_band_height - 1) / min_band_height;
        int aligned_bands = (min_bands_needed + num_bands - 1) / num_bands;
        int total_bands = aligned_bands + band->band_count - 1;
        int aligned_to_count = (total_bands / band->band_count) * band->band_count;
        
        num_bands = (min_bands_needed + aligned_to_count - 1) / aligned_to_count;
    }

    band->band_height = num_bands;
    band->line_count = 0;

    switch (output_format) {
        case 0:
        case 1:
            band->writer = fz_new_pnm_band_writer(ctx, out);
            band->ncomp = (output_format == 0) ? 1 : 3;
            break;
        case 2:
            band->writer = fz_new_pam_band_writer(ctx, out);
            band->ncomp = 4;
            break;
        case 3:
            band->writer = fz_new_pbm_band_writer(ctx, out);
            band->ncomp = 1;
            break;
        case 4:
            band->writer = fz_new_pkm_band_writer(ctx, out);
            band->ncomp = 4;
            break;
    }
}