int __cdecl bgzf_index_load_hfile(BGZF *fp, hFILE *idx, const char *name)
{
    uint64_t x;
    int i;

    // Allocate the BGZF index structure (size 0x18 = 24 bytes)
    fp->idx = (bgzidx_t *)calloc(1uLL, 0x18uLL);
    
    // Check if allocation succeeded and read the first uint64 (number of offsets - 1)
    if (fp->idx && hread_uint64(&x, idx) >= 0)
    {
        fp->idx->moffs = x + 1;
        fp->idx->noffs = x + 1;
        
        // Allocate array of offsets (each bgzidx1_t is 16 bytes)
        fp->idx->offs = (bgzidx1_t *)malloc(16LL * fp->idx->moffs);
        
        if (fp->idx->offs)
        {
            // Initialize the first offset entry to zero
            fp->idx->offs[0].uaddr = 0LL;
            fp->idx->offs[0].caddr = 0LL;
            
            // Read the remaining offset entries from the index file
            for (i = 1; i < fp->idx->noffs; ++i)
            {
                if (hread_uint64(&fp->idx->offs[i].caddr, idx) < 0 || 
                    hread_uint64(&fp->idx->offs[i].uaddr, idx) < 0)
                {
                    goto fail;
                }
            }
            return 0; // Success
        }
    }

fail:
    {
        const char *log_name = name ? name : "index";
        int err_num = *__errno_location();
        char *err_str = strerror(err_num);
        
        hts_log_error("Error reading %s : %s", log_name, err_str);
        
        if (fp->idx)
        {
            free(fp->idx->offs);
            free(fp->idx);
            fp->idx = NULL;
        }
        return -1; // Failure
    }
}