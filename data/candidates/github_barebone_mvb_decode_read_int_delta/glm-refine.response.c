int __cdecl read_int_delta(const uint8_t *in, uint32_t *out, uint32_t *prev)
{
    uint32_t delta = 0;
    int bytes_read = 1;

    // Extract up to 5 bytes (Variable-Length Quantity / VLQ decoding)
    delta |= in[0] & 0x7F;
    
    if (in[0] & 0x80) {
        bytes_read = 2;
        delta |= (in[1] & 0x7F) << 7;
        
        if (in[1] & 0x80) {
            bytes_read = 3;
            delta |= (in[2] & 0x7F) << 14;
            
            if (in[2] & 0x80) {
                bytes_read = 4;
                delta |= (in[3] & 0x7F) << 21;
                
                if (in[3] & 0x80) {
                    bytes_read = 5;
                    delta |= (in[4] & 0x7F) << 28;
                }
            }
        }
    }

    // Apply the delta to the previous value
    *prev += delta;
    *out = *prev;
    
    return bytes_read;
}