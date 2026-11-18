void LZ4_renormDictT (void* LZ4_Data, unsigned int currentBlockSize)
{
    LZ4_stream_t_internal* lz4cs = (LZ4_stream_t_internal*)LZ4_Data;
    size_t delta = (size_t)(lz4cs->dictionary) + (size_t)(lz4cs->dictCtx.dictSize) - (size_t)(lz4cs->dictionary) - (size_t)(currentBlockSize);

    if ((size_t)(lz4cs->dictionary) + (size_t)(currentBlockSize) > (size_t)(lz4cs->dictionary) + (size_t)(lz4cs->dictCtx.dictSize))
    {
        size_t delta = (size_t)(lz4cs->dictionary) + (size_t)(lz4cs->dictCtx.dictSize) - (size_t)(lz4cs->dictionary) - (size_t)(currentBlockSize);
        LZ4_slideDictionary(lz4cs, delta);
    }

    if ((unsigned int)(lz4cs->dictionarySize + currentBlockSize) > 0x80000000U)
    {
        size_t delta = lz4cs->dictionarySize - 64 *(1U<<10);
        char* newDictStart = (char*)(lz4cs->dictionary) + lz4cs->dictCtx.dictSize;
        int nH;

        for (nH=0; nH < (1 << (14 -2)); nH++)
        {
            if ((unsigned int)(lz4cs->hashTable[nH]) < (unsigned int)delta) lz4cs->hashTable[nH] = 0;
            else lz4cs->hashTable[nH] -= (U32)delta;
        }

        lz4cs->dictionarySize = 64 *(1U<<10);
        if (lz4cs->dictCtx.dictSize > 64 *(1U<<10)) lz4cs->dictCtx.dictSize = 64 *(1U<<10);
        memmove__bench(newDictStart - lz4cs->dictCtx.dictSize, lz4cs->dictionary, lz4cs->dictCtx.dictSize);
        lz4cs->dictionary = (U8*)newDictStart - lz4cs->dictCtx.dictSize;
    }
}