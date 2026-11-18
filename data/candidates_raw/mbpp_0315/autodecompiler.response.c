char* func0(char* arg0) {
    int arg0_len = strlen(arg0);
    int i = 0;
    int currLen = 0;
    int maxLen = 0;
    int startInd = -1;

    while(1) {
        if (i >= arg0_len) break;

        switch((int)arg0[i]) {
            case 32:
                if (currLen % 2 == 0) {
                    if (maxLen < currLen) {
                        maxLen = currLen;
                        startInd = i - currLen;
                    }
                } else {
                    currLen = 0;
                }
                break;
            default:
                currLen++;
        }

        i++;
    }

    if (currLen % 2 == 0) {
        if (maxLen < currLen) {
            maxLen = currLen;
            startInd = i - currLen;
        }
    }

    char* result;
    if (-1 == startInd) {
        result = "-1";
    } else {
        strncpy(func0_result, arg0 + startInd, maxLen);
        func0_result[maxLen] = '\0';
        result = func0_result;
    }

    return result;
}