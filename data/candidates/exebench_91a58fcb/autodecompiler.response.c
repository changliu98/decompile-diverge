static void
StrBracketMatch(char *func_call, int *comma_poses, int *nargs,
                  int *closing_bracket_pos, int max_comma_poses)
{
    int bracket_level = 0;
    int inpos = 0;
    int commapos = 0;
    char quote_type = 0;

    while (1) {
        if (func_call[inpos] == '\0') {
            break;
        }
        if (quote_type != 0) {
            if ((func_call[inpos] == quote_type) &&
                (func_call[inpos-1] != '\\')) {
                quote_type = 0;
            }
        } else if ((func_call[inpos] == '\'') ||
                   (func_call[inpos] == '"')) {
            quote_type = func_call[inpos];
        } else if (func_call[inpos] == '(') {
            bracket_level++;
            if (bracket_level == 1) {
                if ((comma_poses != NULL) &&
                    ((max_comma_poses < 0) || (commapos < max_comma_poses))) {
                    comma_poses[commapos++] = inpos;
                }
            }
        } else if (func_call[inpos] == ')') {
            bracket_level--;
            if (bracket_level == 0) {
                break;
            }
        } else if ((func_call[inpos] == ',') && (bracket_level == 1)) {
            if ((comma_poses != NULL) &&
                ((max_comma_poses < 0) || (commapos < max_comma_poses))) {
                comma_poses[commapos++] = inpos;
            }
        }
        inpos++;
    }

    if (func_call[inpos] == '\0') {

        if (nargs != NULL) {
            *nargs = -1;
        }
        if (closing_bracket_pos != NULL) {
            *closing_bracket_pos = -1;
        }
        return;
    }


    if ((comma_poses != NULL) &&
        ((max_comma_poses < 0) || (commapos < max_comma_poses))) {
        comma_poses[commapos++] = inpos;
    }
    if (nargs != NULL) {
        *nargs = commapos - 1;
    }
    if (closing_bracket_pos != NULL) {
        *closing_bracket_pos = inpos;
    }
}