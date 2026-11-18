void crc8_byte(unsigned int *crc, char db)
{
    int i;
    for(i=0;i<8;i++)
    {
        int bit = (db^(*crc))&1;
        *crc >>= 1;
        db >>= 1;
        if(bit)
            *crc ^= 0x8C;
    }
    *crc &= 0xFF;
}