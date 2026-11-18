unsigned int crc8_0x104C11DB(unsigned int data, unsigned int crc, unsigned int poly)
{
    unsigned int crc_table[2] = {0x104C11DB, 0};
    unsigned int data_table[2] = {crc, 0};
    unsigned int result = 0;

    result ^= data_table[data & 1]; data >>= 1;
    crc = (data_table[crc >> 7] ^ (crc << 1));
    result ^= data_table[data & 1]; data >>= 1;
    crc = (data_table[crc >> 7] ^ (crc << 1));
    result ^= data_table[data & 1]; data >>= 1;
    crc = (data_table[crc >> 7] ^ (crc << 1));
    result ^= data_table[data & 1]; data >>= 1;
    crc = (data_table[crc >> 7] ^ (crc << 1));
    result ^= data_table[data & 1]; data >>= 1;
    crc = (data_table[crc >> 7] ^ (crc << 1));
    result ^= data_table[data & 1]; data >>= 1;
    crc = (data_table[crc >> 7] ^ (crc << 1));
    result ^= data_table[data & 1];

    return result;
}