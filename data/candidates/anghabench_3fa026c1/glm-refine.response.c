int __cdecl rdbEncodeInteger(__int64 value, unsigned __int8 *enc)
{
    // 8-bit integer encoding
    if (value >= -128 && value <= 127)
    {
        *enc = RDB_ENC_INT8 | ((_BYTE)RDB_ENCVAL << 6);
        enc[1] = (unsigned __int8)value;
        return 2;
    }

    // 16-bit integer encoding
    if (value >= -32768 && value <= 0x7FFF)
    {
        *enc = RDB_ENC_INT16 | ((_BYTE)RDB_ENCVAL << 6);
        *(_WORD *)(enc + 1) = (unsigned __int16)value;
        return 3;
    }

    // 32-bit integer encoding
    if (value >= (__int64)0xFFFFFFFF80000000LL && value <= 0x7FFFFFFF)
    {
        *enc = RDB_ENC_INT32 | ((_BYTE)RDB_ENCVAL << 6);
        
        // IDA often decompiles unaligned 32-bit stores (e.g., memcpy or direct assignment) 
        // into split WORD and BYTE assignments. This is equivalent to:
        // *(_DWORD *)(enc + 1) = (unsigned __int32)value;
        *(_WORD *)(enc + 1) = (unsigned __int16)value;
        enc[3] = BYTE2(value);
        enc[4] = BYTE3(value);
        return 5;
    }

    // Value out of bounds for RDB integer encoding
    return 0;
}