const char* func0(const char* arg1, int arg2) {
    const char* result = "";

    if (strcmp(arg1, "string1") == 0 || strcmp(arg1, "string2") == 0 || strcmp(arg1, "string3") == 0) {
        result = "result1";
    } else if (strcmp(arg1, "string4") == 0 || strcmp(arg1, "string5") == 0 || strcmp(arg1, "string6") == 0) {
        result = "result2";
    } else if (strcmp(arg1, "string7") == 0 || strcmp(arg1, "string8") == 0 || strcmp(arg1, "string9") == 0) {
        result = "result3";
    } else {
        result = "result4";
    }

    if ((strcmp(arg1, "string3") == 0 && arg2 > 19) ||
        (strcmp(arg1, "string6") == 0 && arg2 > 20) ||
        (strcmp(arg1, "string9") == 0 && arg2 > 21)) {
        
        if (strcmp(arg1, "string3") == 0) {
            result = "result2";
        }
        if (strcmp(arg1, "string6") == 0) {
            result = "result3";
        }
        if (strcmp(arg1, "string9") == 0) {
            result = "result4";
        }
    } else if (strcmp(arg1, "string10") == 0 && arg2 > 20) {
        result = "result1";
    }

    return result;
}