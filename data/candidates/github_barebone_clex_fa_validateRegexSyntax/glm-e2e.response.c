bool validateRegexSyntax(const char *regex) {
    int paren_depth = 0;
    bool in_brackets = false;
    bool escape = false;
    bool has_char = false;
    bool after_or = false;
    bool after_op = false;
    long long i = 0;

    while (regex[i] != '\0') {
        char c = regex[i];

        if (escape) {
            escape = false;
            has_char = true;
            after_or = false;
            after_op = false;
        } else if (c == '\\') {
            escape = true;
        } else if (in_brackets) {
            if (c == ']') {
                if (!has_char) {
                    return false;
                }
                in_brackets = false;
                has_char = true;
                after_or = false;
                after_op = false;
            } else {
                has_char = true;
            }
        } else if (c == '[') {
            in_brackets = true;
            has_char = false;
        } else if (c == ']') {
            return false;
        } else if (c == '(') {
            paren_depth++;
            has_char = false;
            after_or = false;
            after_op = false;
        } else if (c == ')') {
            if (paren_depth == 0 || !has_char) {
                return false;
            }
            paren_depth--;
            has_char = true;
            after_or = false;
            after_op = false;
        } else if (c == '|') {
            if (!has_char) {
                return false;
            }
            has_char = false;
            after_or = true;
            after_op = false;
        } else if (c == '*' || c == '+' || c == '?') {
            if (!has_char || after_op) {
                return false;
            }
            after_or = false;
            after_op = true;
        } else {
            has_char = true;
            after_or = false;
            after_op = false;
        }
        i++;
    }

    if (escape || in_brackets || paren_depth != 0 || after_or) {
        return false;
    }
    return true;
}