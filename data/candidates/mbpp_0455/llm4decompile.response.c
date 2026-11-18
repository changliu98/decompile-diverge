unsigned char func0(unsigned char monthnum2) {
    unsigned char result;
    if (monthnum2 == 1) {
        result = 1;
    } else {
        if (monthnum2 == 3) {
            result = 1;
        } else {
            if (monthnum2 == 5) {
                result = 1;
            } else {
                if (monthnum2 == 7) {
                    result = 1;
                } else {
                    if (monthnum2 == 8) {
                        result = 1;
                    } else {
                        if (monthnum2 == 10) {
                            result = 1;
                        } else {
                            if (monthnum2 == 12) {
                                result = 1;
                            } else {
                                result = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}