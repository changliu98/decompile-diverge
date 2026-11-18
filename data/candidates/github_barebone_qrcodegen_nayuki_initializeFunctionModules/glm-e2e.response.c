void initializeFunctionModules(int version, uint8_t *qrcode) {
    int size = version * 4 + 17;
    int temp = (size * size + 7) / 8 + 1;
    
    // Call 1
    drawLightFunctionModules(qrcode, 0, temp, 0, 0, 0);
    
    // Set the first byte of qrcode
    qrcode[0] = (uint8_t)size;
    
    // Call 2
    drawLightFunctionModules(qrcode, 0, 1, 6, size, 0);
    
    // Call 3
    drawLightFunctionModules(qrcode, 0, 1, 0, 6, size);
    
    // Call 4
    drawLightFunctionModules(qrcode, 0, 9, 0, 0, 0);
    
    // Call 5
    drawLightFunctionModules(qrcode, 0, 9, size - 8, 8, 0);
    
    // Call 6
    drawLightFunctionModules(qrcode, 0, 8, 0, 9, size - 8);
    
    char buffer[11];
    int numRawDataModules = getNumRawDataModules(version, buffer);
    
    for (int i = 0; i < numRawDataModules; i++) {
        for (int j = 0; j < numRawDataModules; j++) {
            if ((i == 0 && j == 0) || 
                (i == 0 && j == numRawDataModules - 1) || 
                (i == numRawDataModules - 1 && j == 0)) {
                continue;
            }
            drawCodewords(qrcode, buffer[i] - 2, buffer[j] - 2, 5, 5, size, 0);
        }
    }
    
    if (version >= 7) {
        // Call 7
        drawLightFunctionModules(qrcode, 0, 3, size - 11, 6, 0);
        
        // Call 8
        drawLightFunctionModules(qrcode, 0, 6, 0, 3, size - 11);
    }
}