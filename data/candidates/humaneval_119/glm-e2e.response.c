const char* func0(const char *s1, const char *s2) {
    int balance = 0;
    int valid = 1;
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    // Check first string
    for (int i = 0; i < len1; i++) {
        if (s1[i] == '(') {
            balance++;
        } else if (s1[i] == ')') {
            balance--;
        }
        if (balance < 0) {
            valid = 0;
        }
    }

    // Check second string
    for (int i = 0; i < len2; i++) {
        if (s2[i] == '(') {
            balance++;
        } else if (s2[i] == ')') {
            balance--;
        }
        if (balance < 0) {
            valid = 0;
        }
    }

    // If balanced and valid so far, return "Yes"
    if (balance == 0 && valid != 0) {
        return "Yes";
    }

    // Reset and check reverse order (s2 then s1)
    balance = 0;
    valid = 1;

    // Check second string first
    for (int i = 0; i < len2; i++) {
        if (s2[i] == '(') {
            balance++;
        } else if (s2[i] == ')') {
            balance--;
        }
        if (balance < 0) {
            valid = 0;
        }
    }

    // Check first string second
    for (int i = 0; i < len1; i++) {
        if (s1[i] == '(') {
            balance++;
        } else if (s1[i] == ')') {
            balance--;
        }
        if (balance < 0) {
            valid = 0;
        }
    }

    // If balanced and valid in reverse order, return "Yes"
    if (balance == 0 && valid != 0) {
        return "Yes";
    }

    // Otherwise, return "No"
    return "No";
}