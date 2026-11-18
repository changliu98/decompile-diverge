static unsigned char fsp_test_invert_cmd(unsigned char v) {
    unsigned char v2;
    unsigned char result;
    
    v2 = v;
    while (1) {
        if (v2!= (char)233) {
            if (v2!= (char)238) {
                if (v2!= (char)242) {
                    if (v2!= (char)255) {
                        v2 = v;
                        break;
                    }
                    v2 = -1;
                    break;
                }
                v2 = -2;
                break;
            }
            v2 = -3;
            break;
        }
        v2 = -4;
        break;
    }
    result = v2;
    return result;
}