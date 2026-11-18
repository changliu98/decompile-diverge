int get_parameter_rate(struct Parameter *param) {
    int rate;
    unsigned char mode;

    if ((param->byte_1 & 1) != 0 || param->byte_34 != 0) {
        mode = param->byte_2f;
        if (mode <= 4) {
            switch (mode) {
                case 0:
                    rate = param->ptr_8->dword_10;
                    break;
                case 1:
                    rate = param->ptr_8->dword_14;
                    break;
                case 2:
                    if (param->ptr_8->dword_8 != 0) {
                        rate = 0;
                    } else {
                        rate = param->ptr_8->dword_1c;
                    }
                    break;
                case 3:
                    if (param->byte_35 != 0) {
                        rate = 5;
                    } else if (param->ptr_8->dword_8 != 0) {
                        rate = param->ptr_8->dword_1c;
                    } else {
                        rate = 7;
                    }
                    break;
                case 4:
                    rate = 12;
                    break;
            }
        } else {
            rate = 0;
        }
    } else {
        rate = 0;
    }

    return rate;
}