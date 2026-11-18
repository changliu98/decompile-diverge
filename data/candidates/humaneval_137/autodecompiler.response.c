char *func0(char *num1, char *num2) {
    char *num1_ptr;
    char *num2_ptr;
    char *ret_ptr;
    char *str_ptr;
    double num_a;
    double num_b;

    num1_ptr = strdup(num1);
    num2_ptr = strdup(num2);

    int i;
    for (i=0;;i++) {
        if (*(num1_ptr + i) == '\0') {
            break;
        }
        if (*(num1_ptr + i) == ',') {
            *(num1_ptr + i) = '.';
        }
    }

    for (i=0;;i++) {
        if (*(num2_ptr + i) == '\0') {
            break;
        }
        if (*(num2_ptr + i) == ',') {
            *(num2_ptr + i) = '.';
        }
    }

    num_a = strtod(num1_ptr, &str_ptr);
    if (*str_ptr != '\0') {
        free(num1_ptr);
        free(num2_ptr);
        ret_ptr = "Invalid input";
        goto out;
    }

    num_b = strtod(num2_ptr, &str_ptr);
    if (*str_ptr != '\0') {
        free(num1_ptr);
        free(num2_ptr);
        ret_ptr = "Invalid input";
        goto out;
    }

    free(num1_ptr);
    free(num2_ptr);

    if (num_a == num_b) {
        ret_ptr = "None";
    } else if (num_a > num_b) {
        ret_ptr = num1;
    } else {
        ret_ptr = num2;
    }

out:
    return ret_ptr;
}