void LZ4_renormDictT(LZ4_stream_t_internal* LZ4_dict, int nextSize)
{
    U32 delta = LZ4_dict->currentOffset - 64 *(1 <<10);
    if (LZ4_dict->currentOffset > 1 *(1 <<29))
    {
        int i;
        BYTE* dictEnd = LZ4_dict->dictionary + LZ4_dict->dictSize;
        for (i = 0; i < (1 <<14); i++)
        {
            if (LZ4_dict->hashTable[i] >= delta)
                LZ4_dict->hashTable[i] -= delta;
            else
                LZ4_dict->hashTable[i] = 0;
        }
        LZ4_dict->currentOffset = 64 *(1 <<10);
        if (LZ4_dict->dictSize > 64 *(1 <<10))
            LZ4_dict->dictSize = 64 *(1 <<10);
        LZ4_dict->dictionary = dictEnd - LZ4_dict->dictSize;
    }
}