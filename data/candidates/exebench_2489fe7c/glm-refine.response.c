void crc16_b(uint32_t *crc, uint8_t db) {
    for (int i = 0; i < 8; ++i) {
        *crc <<= 1;
        
        // Extract the 3rd byte (bits 16-23) of the CRC and XOR with the data byte
        uint8_t crc_byte2 = (*crc >> 16) & 0xFF;
        
        // If the LSB of the XOR result is 1, apply the polynomial
        if ((crc_byte2 ^ db) & 1) {
            *crc ^= 0x8005u;
        }
        
        // Unsigned right shift of the data byte
        db >>= 1;
    }
    
    // Truncate the CRC to 16 bits
    *crc = (uint16_t)(*crc);
}