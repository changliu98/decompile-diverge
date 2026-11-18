int imagetopnm(opj_image_t *image, const char *filename, int split) {
    FILE *fdest = NULL;
    char *name = NULL;
    const char *tmp = filename;
    int *red = NULL, *green = NULL, *blue = NULL, *alpha = NULL;
    int wrt = 0, fail = 0;
    int nr_comp = image->numcomps;
    int prec = image->comps[0].prec;
    
    if (prec > 16) {
        fprintf(stderr, "%s:%d:imagetopnm\n\t: can not create %s because the precision is too high (%d)\n", __FILE__, __LINE__, filename, prec);
        return 1;
    }

    int has_alpha = 0;
    int is_16bit = 0;
    int comp_shift = 0;
    int mask = (1 << prec) - 1;
    int is_pnm = (nr_comp == 2 || nr_comp == 4) ? 0 : 1;
    int adjust = image->comps[0].sgnd ? 1 << (prec - 1) : 0;
    
    // Check if filename ends with 'g' or 'G' (e.g. .pgm, .ppm)
    while (*tmp) tmp++;
    tmp--;
    if (*tmp == 'g' || *tmp == 'G') {
        is_pnm = 1;
    }
    
    if (is_pnm) {
        nr_comp = 1;
    }
    
    if (split == 0 && nr_comp == 2) {
        goto single_file;
    }
    
    if (split == 0 && nr_comp > 2) {
        // Check if components have matching parameters
        if (image->comps[0].dx == image->comps[1].dx &&
            image->comps[0].dx == image->comps[2].dx &&
            image->comps[0].dy == image->comps[1].dy &&
            image->comps[0].dy == image->comps[2].dy &&
            image->comps[0].prec == image->comps[1].prec &&
            image->comps[0].prec == image->comps[2].prec) {
            goto single_file;
        }
    }
    
    // Split file output
    if (image->numcomps > nr_comp) {
        fprintf(stderr, "%s:%d:imagetopnm\n", __FILE__, __LINE__);
        fprintf(stderr, "\t: all components must have the same subsampling\n");
    }
    
    name = (char*)malloc(strlen(filename) + 8);
    if (!name) {
        fprintf(stderr, "%s:%d:imagetopnm\n\t: could not allocate memory\n", __FILE__, __LINE__);
        return 1;
    }
    
    for (int compno = 0; compno < nr_comp; compno++) {
        if (nr_comp > 1) {
            size_t filename_len = strlen(filename);
            size_t name_len = filename_len - 4;
            strncpy(name, filename, name_len);
            sprintf(name + name_len, "_%d", compno);
        } else {
            sprintf(name, "%s", filename);
        }
        
        fdest = fopen(name, "wb");
        if (!fdest) {
            fprintf(stderr, "%s:%d:imagetopnm\n\t: can not open %s for writing\n", __FILE__, __LINE__, name);
            free(name);
            return 1;
        }
        
        int w = image->comps[compno].w;
        int h = image->comps[compno].h;
        int prec = image->comps[compno].prec;
        int mask = (1 << prec) - 1;
        
        fprintf(fdest, "P5\n%d %d\n%d\n", w, h, mask);
        
        int *ptr = image->comps[compno].data;
        int adjust = image->comps[compno].sgnd ? 1 << (prec - 1) : 0;
        
        if (prec > 8) {
            for (int i = 0; i < w * h; i++) {
                int v = *ptr + adjust;
                ptr++;
                if (v > 65535) v = 65535;
                else if (v < 0) v = 0;
                fprintf(fdest, "%c%c", (v >> 8) & 0xFF, v & 0xFF);
            }
        } else {
            for (int i = 0; i < w * h; i++) {
                int v = *ptr + adjust;
                ptr++;
                if (v > 255) v = 255;
                else if (v < 0) v = 0;
                fprintf(fdest, "%c", v & 0xFF);
            }
        }
        
        fclose(fdest);
    }
    
    free(name);
    return 0;

single_file:
    fdest = fopen(filename, "wb");
    if (!fdest) {
        fprintf(stderr, "%s:%d:imagetopnm\n\t: can not open %s for writing\n", __FILE__, __LINE__, filename);
        return 1;
    }
    
    is_16bit = (prec > 8);
    wrt = (nr_comp > 2);
    
    int w = image->comps[0].w;
    int h = image->comps[0].h;
    int mask = (1 << prec) - 1;
    int is_pnm_final = (nr_comp == 4 || nr_comp == 2) ? 0 : 1;
    
    red = image->comps[0].data;
    if (wrt) {
        green = image->comps[1].data;
        blue = image->comps[2].data;
    }
    
    if (is_pnm_final) {
        const char *format = wrt ? "P6\n" : "P5\n";
        fprintf(fdest, "%s%d %d\n%d\n", format, w, h, mask, opj_version());
        
        alpha = image->comps[nr_comp - 1].data;
        adjust = image->comps[nr_comp - 1].sgnd ? 1 << (prec - 1) : 0;
    } else {
        fprintf(fdest, "P7\nWIDTH %d\nHEIGHT %d\nDEPTH %d\nMAXVAL %d\nTUPLTYPE RGB_ALPHA\nENDHDR\n", w, h, nr_comp, mask, opj_version());
        adjust = 0;
    }
    
    adjust = image->comps[0].sgnd ? 1 << (prec - 1) : 0;
    int adjust_g = wrt && image->comps[1].sgnd ? 1 << (prec - 1) : 0;
    int adjust_b = wrt && image->comps[2].sgnd ? 1 << (prec - 1) : 0;
    
    for (int i = 0; i < w * h; i++) {
        if (is_16bit) {
            int v = *red + adjust;
            red++;
            if (v > 65535) v = 65535;
            else if (v < 0) v = 0;
            fprintf(fdest, "%c%c", (v >> 8) & 0xFF, v & 0xFF);
            
            if (wrt) {
                v = *green + adjust_g;
                green++;
                if (v > 65535) v = 65535;
                else if (v < 0) v = 0;
                fprintf(fdest, "%c%c", (v >> 8) & 0xFF, v & 0xFF);
                
                v = *blue + adjust_b;
                blue++;
                if (v > 65535) v = 65535;
                else if (v < 0) v = 0;
                fprintf(fdest, "%c%c", (v >> 8) & 0xFF, v & 0xFF);
            }
            
            if (is_pnm_final) {
                v = *alpha + adjust;
                alpha++;
                if (v > 65535) v = 65535;
                else if (v < 0) v = 0;
                fprintf(fdest, "%c%c", (v >> 8) & 0xFF, v & 0xFF);
            }
        } else {
            int v = *red + adjust;
            red++;
            if (v > 255) v = 255;
            else if (v < 0) v = 0;
            fprintf(fdest, "%c", v & 0xFF);
            
            if (wrt) {
                v = *green + adjust_g;
                green++;
                if (v > 255) v = 255;
                else if (v < 0) v = 0;
                fprintf(fdest, "%c", v & 0xFF);
                
                v = *blue + adjust_b;
                blue++;
                if (v > 255) v = 255;
                else if (v < 0) v = 0;
                fprintf(fdest, "%c", v & 0xFF);
            }
            
            if (is_pnm_final) {
                v = *alpha + adjust;
                alpha++;
                if (v > 255) v = 255;
                else if (v < 0) v = 0;
                fprintf(fdest, "%c", v & 0xFF);
            }
        }
    }
    
    fclose(fdest);
    return 0;
}