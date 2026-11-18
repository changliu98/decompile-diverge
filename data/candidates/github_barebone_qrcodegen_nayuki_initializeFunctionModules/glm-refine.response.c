void __cdecl initializeFunctionModules(int version, uint8_t *qrcode)
{
    int qrsize = 4 * version + 17;
    uint8_t alignPatPos[7];
    int numAlign;
    int i, j;

    // Clear the QR code buffer and write the size to the first byte
    memset(qrcode, 0, (qrsize * qrsize + 7) / 8 + 1);
    *qrcode = qrsize;

    // Draw timing patterns
    fillRectangle(6, 0, 1, qrsize, qrcode);
    fillRectangle(0, 6, qrsize, 1, qrcode);

    // Draw finder patterns (and their separators)
    fillRectangle(0, 0, 9, 9, qrcode);
    fillRectangle(qrsize - 8, 0, 8, 9, qrcode);
    fillRectangle(0, qrsize - 8, 9, 8, qrcode);

    // Draw alignment patterns
    numAlign = getAlignmentPatternPositions(version, alignPatPos);
    for (i = 0; i < numAlign; ++i)
    {
        for (j = 0; j < numAlign; ++j)
        {
            // Skip alignment patterns that would overlap with the finder patterns
            bool isTopLeft = (i == 0 && j == 0);
            bool isTopRight = (i == 0 && j == numAlign - 1);
            bool isBottomLeft = (i == numAlign - 1 && j == 0);

            if (!isTopLeft && !isTopRight && !isBottomLeft)
            {
                fillRectangle(alignPatPos[i] - 2, alignPatPos[j] - 2, 5, 5, qrcode);
            }
        }
    }

    // Draw version information (only for QR codes version 7 and up)
    if (version >= 7)
    {
        fillRectangle(qrsize - 11, 0, 3, 6, qrcode);
        fillRectangle(0, qrsize - 11, 6, 3, qrcode);
    }
}