static char *smb_fdata(struct smb *conn, char *data, char *format,
         char *end, int unicode)
{
 char *ret;

 while (1) {
  if (*format == '\0') {
   if (smb_fdata_depth == 0 && data < end) {
    size_t len = end - data;
    conn->print(conn, "Data: (%lu bytes)\n",
         (unsigned long)len);
    smb_print_data(conn, data, len);
    ret = data + len;
   } else
    ret = data;
   break;
  }
  switch (*format) {
  case '*':
   format++;
   do {
    char *newdata;

    if (data >= end) {
     ret = data;
     goto out;
    }

    smb_fdata_depth++;
    newdata = smb_fdata(conn, data, format,
          end, unicode);
    smb_fdata_depth--;

    if (!newdata) {
     ret = NULL;
     goto out;
    } else if (newdata == data) {
     ret = data;
     goto out;
    }
    data = newdata;
   } while (1);

  case '|':
   format++;
   if (data >= end) {
    ret = data;
    goto out;
   }
   break;

  case '%':
   format++;
   data = end;
   break;

  case '#':
   format++;
   ret = data;
   goto out;

  case '[':
   {
    char format2[128], *end2;

    format++;
    if (data >= end) {
     ret = data;
     goto out;
    }

    memset(format2, 0, sizeof(format2));
    end2 = strchr(format, ']');
    if (end2 - format + 1 > sizeof(format2)) {
     ret = data;
     goto out;
    }
    strncpy(format2, format, end2 - format);
    format2[end2 - format] = '\0';
    format = end2 + 1;

    data = smb_fdata1(conn, data, format2,
         end, unicode);
    if (!data) {
     ret = NULL;
     goto out;
    }
    break;
   }

  default:
   conn->print(conn, "%c", *format);
   format++;
  }
 }
out:
 return ret;
}