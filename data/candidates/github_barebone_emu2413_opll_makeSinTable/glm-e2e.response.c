void makeSinTable() {
    int i;

    // Block 1: Copy the first 256 elements in reverse order to the next 256 elements
    for (i = 0; i < 0x100; i++) {
        sinTable[i + 0x100] = sinTable[0x100 - i - 1];
    }

    // Block 2: Bitwise OR the next 256 elements with 0x8000 and store them in the following 256 elements
    for (i = 0; i < 0x200; i++) {
        sinTable[i + 0x200] = sinTable[i] | 0x8000;
    }

    // Block 3: Copy the 512 elements starting at index 0x200 back to the beginning of the table (index 0)
    for (i = 0; i < 0x200; i++) {
        sinTable[i] = sinTable[i + 0x200];
    }

    // Block 4: Fill the last 512 elements (index 0x200 to 0x3FF) with 0x0FFF
    for (i = 0x200; i < 0x400; i++) {
        sinTable[i] = 0x0FFF;
    }
}