uint8_t BS_ReadByte(BS_Struct *bs) {
    uint8_t read_byte = 0;
    int load_status = 0;
    uint8_t loaded_byte = 0;
    uint8_t next_byte = 0;

    // If it's a memory stream, read directly from the buffer
    if (bs->is_memory_stream == 0) {
        if (bs->position >= bs->size) {
            if (bs->on_drain != NULL) {
                bs->on_drain(bs->on_drain_ctx);
            }
            if (bs->error == 0) {
                bs->error = 1;
            }
            return 0;
        }

        loaded_byte = bs->buffer[bs->position];
        bs->position++;

        if (bs->sc_emulation != 0) {
            if (bs->zero_run == 2 && loaded_byte == 3) {
                if (bs->position < bs->size) {
                    next_byte = bs->buffer[bs->position];
                    if ((int8_t)next_byte < 4) {
                        bs->zero_run = 0;
                        loaded_byte = next_byte;
                        bs->position++;
                    }
                }
            }
            if (loaded_byte == 0) {
                bs->zero_run++;
            } else {
                bs->zero_run = 0;
            }
        }
        read_byte = loaded_byte;
    } 
    // Otherwise, read from a file stream
    else {
        if (bs->has_write_cache != 0) {
            bs_flush_write_cache(bs);
        }

        int is_eof = gf_feof(bs->file);

        if (is_eof == 0 || bs->eof_hit != 0) {
            assert(bs->position <= bs->size && "Position out of bounds");
            
            bs->position++;
            loaded_byte = gf_bs_load_byte(bs, &load_status);

            if (load_status == 0) {
                if (bs->sc_emulation != 0) {
                    if (bs->zero_run == 2 && loaded_byte == 3) {
                        if (bs->position < bs->size) {
                            next_byte = gf_bs_load_byte(bs, &load_status);
                            if (next_byte < 4) {
                                bs->zero_run = 0;
                                loaded_byte = next_byte;
                                bs->position++;
                            } else {
                                gf_bs_seek(bs, bs->position);
                            }
                        }
                    }
                    if (loaded_byte == 0) {
                        bs->zero_run++;
                    } else {
                        bs->zero_run = 0;
                    }
                }
                read_byte = loaded_byte;
            } else {
                // EOF or error hit during load
                if (bs->on_drain != NULL) {
                    bs->on_drain(bs->on_drain_ctx);
                }
                if (bs->error == 0) {
                    bs->error = 1;
                }
                assert(bs->position <= bs->size + 1 && "Position out of bounds after EOF");
                return 0;
            }
        } else {
            // EOF hit initially
            if (bs->on_drain != NULL) {
                bs->on_drain(bs->on_drain_ctx);
            }
            if (bs->error == 0) {
                bs->error = 1;
            }
            assert(bs->position <= bs->size + 1 && "Position out of bounds on initial EOF");
            return 0;
        }
    }

    return read_byte;
}