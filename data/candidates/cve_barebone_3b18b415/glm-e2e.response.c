void merged_2v_upsample(
    decompress_master *master,
    void *arg2,                // %rsi (unused in this snippet)
    void ***input_data,        // %rdx
    int *out_row_ctr,          // %rcx
    void **output_buf,         // %r8
    int *out_row_avail         // %r9
) {
    my_upsample_struct *upsample = (my_upsample_struct *)master->field_0;
    int rows_to_process;

    if (upsample->has_spare_row) {
        // We have a spare row from the previous call, so we need to process it
        rows_to_process = upsample->spare_height;
        
        // If the component precision is 16-bit, double the height to process
        if (master->field_8 == 16) {
            rows_to_process = master->field_c * 2;
        }

        // Copy the spare row to the output buffer
        jcopy_sample_rows(
            upsample->spare_row, 
            0, 
            output_buf, 
            *out_row_avail, 
            1, 
            rows_to_process
        );
        
        rows_to_process = 1;
        upsample->has_spare_row = 0;
    } else {
        // No spare row, process fresh rows
        rows_to_process = 2;
        if (rows_to_process > upsample->rows_remaining) {
            rows_to_process = upsample->rows_remaining;
        }
        
        // Adjust remaining available output rows
        *out_row_avail -= *out_row_ctr;
        if (rows_to_process > *out_row_avail) {
            rows_to_process = *out_row_avail;
        }
        
        // Fetch the current input row pointers
        void *in_row_0 = (*input_data)[*out_row_ctr];
        void *in_row_1;
        
        if (rows_to_process > 1) {
            in_row_1 = (*input_data)[*out_row_ctr + 1];
        } else {
            // If only 1 row is left to process, save it as a spare for the next call
            in_row_1 = upsample->spare_row;
            upsample->has_spare_row = 1;
        }
        
        // Call the specific upsample method with the gathered rows
        // Signature inferred: upsample_func(master, arg2, &in_row_0, out_row_ctr, output_buf, out_row_avail)
        ((void (*)(decompress_master *, void *, void **, int *, void **, int *))upsample->upsample_func)(
            master, 
            arg2, 
            &in_row_0, 
            out_row_ctr, 
            output_buf, 
            out_row_avail
        );
    }

    // Update the current output row index
    *out_row_ctr += rows_to_process;
    
    // Decrement the count of total remaining rows to process
    upsample->rows_remaining -= rows_to_process;
    
    // If we didn't generate a new spare row in this pass, advance the input row index
    if (!upsample->has_spare_row) {
        (*input_data)++;
    }
}