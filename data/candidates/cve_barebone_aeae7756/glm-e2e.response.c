void ex_history(char **argp) {
    int type = 0;
    int end_type = 0;
    int start_num = 1;
    int end_num = -1;
    char *arg;
    char *p;
    char save_char;
    int hisidx_local;
    struct hist_entry *hist_array;
    int i;
    int print_num;
    char *str_end;
    int col_limit;

    arg = *argp;

    if (hislen == 0) {
        msg("'history' option is zero");
        return;
    }

    if (*arg >= '0' && *arg <= '9' || *arg == '-' || *arg == ',') {
        p = arg;
    } else {
        p = arg;
        while (1) {
            char c = *p;
            int is_alpha = 0;
            if (c >= 'A' && c <= 'Z') {
                is_alpha = 1;
            } else if (c >= 'a' && c <= 'z') {
                is_alpha = 1;
            } else if (vim_strchr(":=@>?/", c) != NULL) {
                is_alpha = 1;
            }
            if (!is_alpha) {
                break;
            }
            p++;
        }
        save_char = *p;
        *p = '\0';
        type = get_histtype(arg);
        if (type == -1) {
            if (strncasecmp(arg, "all", strlen(arg)) == 0) {
                type = 0;
                end_type = 4;
            } else {
                *p = save_char;
                semsg(e_trailing_characters_str, arg);
                return;
            }
        } else {
            end_type = type;
        }
        *p = save_char;
    }

    if (get_list_range(&p, &start_num, &end_num) == 0 || *p != '\0') {
        semsg(e_trailing_characters_str, p);
        return;
    }

    while (!got_int && type <= end_type) {
        strcpy(IObuff, "\n      #  ");
        strcat(IObuff, history_names[type]);
        strcat(IObuff, " history");
        msg_puts_title(IObuff);

        hisidx_local = hisidx[type];
        hist_array = (struct hist_entry *)history[type];

        if (start_num < 0) {
            if (-start_num > hislen) {
                start_num = 0;
            } else {
                start_num = hist_array[(hislen + start_num + hisidx_local + 1) % hislen].hisnum;
            }
        }
        if (end_num < 0) {
            if (-end_num > hislen) {
                end_num = 0;
            } else {
                end_num = hist_array[(hislen + end_num + hisidx_local + 1) % hislen].hisnum;
            }
        }

        if (hisidx_local >= 0 && start_num <= end_num) {
            print_num = hisidx_local + 1;
            while (!got_int) {
                if (print_num == hislen) {
                    print_num = 0;
                }
                if (hist_array[print_num].string != NULL &&
                    hist_array[print_num].hisnum >= start_num &&
                    hist_array[print_num].hisnum <= end_num) {
                    
                    msg_putchar('\n');
                    sprintf(IObuff, "%c%3d  ", (print_num == hisidx_local) ? '>' : ' ', hist_array[print_num].hisnum);
                    
                    if (vim_strsize(hist_array[print_num].string) > Columns - 10) {
                        str_end = IObuff + strlen(IObuff);
                        col_limit = Columns - 10;
                        trunc_string(hist_array[print_num].string, str_end, col_limit, 1025 - strlen(IObuff));
                    } else {
                        strcat(IObuff, hist_array[print_num].string);
                    }
                    msg_outtrans(IObuff);
                    out_flush();
                }
                if (print_num == hisidx_local) {
                    break;
                }
                print_num++;
            }
        }
        type++;
    }
}