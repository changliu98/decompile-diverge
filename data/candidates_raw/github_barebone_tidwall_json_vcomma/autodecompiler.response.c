long
json_token_next(char *data, long size, long start, char delim)
{
  long i;
  long end;

  if (start == size) {
    end = -start - 1;
  } else if (*(data + start) == ',') {
    end = start;
  } else {
    for (i = start; i < size; i++) {
      switch (*(data + i)) {
        case '\r':
        case '\n':
        case '\t':
        case ' ':
          end = i;
          goto done;
        case ',':
          end = i;
          goto done;
        default:
          break;
      }
    }

    end = -i - 1;
  }

done:
  return end;
}