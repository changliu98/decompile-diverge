void func0(char *str, char *buf) {
    int i = 0, j = 0, k = 0, l = 0;
    while (1) {
        if (str[i]!= '\0') {
            if (str[i]!='') {
                j++;
            } else {
                if (k >= 2) {
                    bool flag = true;
                    k = 2;
                    while (k <= j * j) {
                        if (j % k == 0) {
                            flag = false;
                            break;
                        }
                        k++;
                    }
                    if (flag) {
                        buf[k++] ='';
                        memcpy(buf + k, str + i - j, j);
                        k += j;
                        j = 0;
                    } else {
                        j++;
                    }
                } else {
                    j++;
                }
            }
        } else {
            if (k >= 2) {
                bool flag = true;
                k = 2;
                while (k <= j * j) {
                    if (j % k == 0) {
                        flag = false;
                        break;
                    }
                    k++;
                }
                if (flag) {
                    buf[k++] ='';
                    memcpy(buf + k, str + i - j, j);
                    k += j;
                    j = 0;
                } else {
                    j++;
                }
            } else {
                j++;
            }
            buf[k] = '\0';
            break;
        }
        i++;
    }
}