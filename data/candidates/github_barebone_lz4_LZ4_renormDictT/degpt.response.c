void LZ4_renormDictT(LZ4_stream_t_internal *dictState, int newSize)
{
    // Check if the current offset plus the next size exceeds the maximum representable offset
    if (0x80000000 < dictState->currentOffset + newSize) {
        // Calculate the delta to shift offsets, keeping a 64KB window
        U32 shiftAmount = dictState->currentOffset - 0x10000;
        // Get pointer to the end of the current dictionary
        BYTE *dictionaryEnd = dictState->dictionary + dictState->dictSize;
        int index;
        // Iterate through the hash table to adjust offsets
        for (index = 0; index < 0x1000; index++) {
            // If the hash table entry is less than the delta, set it to 0
            if (dictState->hashTable[index] < shiftAmount) {
                dictState->hashTable[index] = 0;
            } else {
                // Otherwise, subtract the delta to normalize the offset
                dictState->hashTable[index] -= shiftAmount;
            }
        }
        // Reset the current offset to the start of the new window
        dictState->currentOffset = 0x10000;
        // If the dictionary size exceeds the window size, truncate it
        if (0x10000 < dictState->dictSize) {
            dictState->dictSize = 0x10000;
        }
        // Update the dictionary pointer to point to the start of the truncated dictionary
        dictState->dictionary = dictionaryEnd - dictState->dictSize;
    }
}