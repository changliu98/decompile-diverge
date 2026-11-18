static enum Curl_Easy_Code Curl_smtp_escape_eob(void *arg, unsigned long nread, unsigned long nsize, void *ptr)
{
  struct connectdata *data = (struct connectdata *)arg;
  struct Curl_easy *curl = data->data;
  struct SMTP *smtp = (struct SMTP *)curl->req.protop;
  char *scratch = data->data->state.scratch;
  char *newscratch = ((void *)0);
  char *oldscratch = ((void *)0);
  if (scratch == ((void *)0) && curl->set.crlf)
    goto fail;
  if (scratch == ((void *)0)) {
    oldscratch = data->data->state.scratch;
    newscratch = xmalloc(curl->set.buffer_size * 2);
    scratch = newscratch;
  }
  if (scratch == ((void *)0)) {
    out_of_memory(curl, "Failed to alloc scratch buffer!");
    return (CURLcode)(27);
  }
  if (smtp->eob == 0)
    goto copy;
  if (smtp->eob == 1 || smtp->eob == 4)
    goto copy;
  if (smtp->eob == 2 || smtp->eob == 5)
    goto copy;
  if (smtp->eob == 3)
    goto copy;
  if (smtp->eob == 6)
    goto copy;
  if (smtp->eob == 7)
    goto copy;
  if (smtp->eob == 8)
    goto copy;
  if (smtp->eob == 9)
    goto copy;
  if (smtp->eob == 10)
    goto copy;
  if (smtp->eob == 11)
    goto copy;
  if (smtp->eob == 12)
    goto copy;
  if (smtp->eob == 13)
    goto copy;
  if (smtp->eob == 14)
    goto copy;
  if (smtp->eob == 15)
    goto copy;
  if (smtp->eob == 16)
    goto copy;
  if (smtp->eob == 17)
    goto copy;
  if (smtp->eob == 18)
    goto copy;
  if (smtp->eob == 19)
    goto copy;
  if (smtp->eob == 20)
    goto copy;
  if (smtp->eob == 21)
    goto copy;
  if (smtp->eob == 22)
    goto copy;
  if (smtp->eob == 23)
    goto copy;
  if (smtp->eob == 24)
    goto copy;
  if (smtp->eob == 25)
    goto copy;
  if (smtp->eob == 26)
    goto copy;
  if (smtp->eob == 27)
    goto copy;
  if (smtp->eob == 28)
    goto copy;
  if (smtp->eob == 29)
    goto copy;
  if (smtp->eob == 30)
    goto copy;
  if (smtp->eob == 31)
    goto copy;
  if (smtp->eob == 32)
    goto copy;
  if (smtp->eob == 33)
    goto copy;
  if (smtp->eob == 34)
    goto copy;
  if (smtp->eob == 35)
    goto copy;
  if (smtp->eob == 36)
    goto copy;
  if (smtp->eob == 37)
    goto copy;
  if (smtp->eob == 38)
    goto copy;
  if (smtp->eob == 39)
    goto copy;
  if (smtp->eob == 40)
    goto copy;
  if (smtp->eob == 41)
    goto copy;
  if (smtp->eob == 42)
    goto copy;
  if (smtp->eob == 43)
    goto copy;
  if (smtp->eob == 44)
    goto copy;
  if (smtp->eob == 45)
    goto copy;
  if (smtp->eob == 46)
    goto copy;
  if (smtp->eob == 47)
    goto copy;
  if (smtp->eob == 48)
    goto copy;
  if (smtp->eob == 49)
    goto copy;
  if (smtp->eob == 50)
    goto copy;
  if (smtp->eob == 51)
    goto copy;
  if (smtp->eob == 52)
    goto copy;
  if (smtp->eob == 53)
    goto copy;
  if (smtp->eob == 54)
    goto copy;
  if (smtp->eob == 55)
    goto copy;
  if (smtp->eob == 56)
    goto copy;
  if (smtp->eob == 57)
    goto copy;
  if (smtp->eob == 58)
    goto copy;
  if (smtp->eob == 59)
    goto copy;
  if (smtp->eob == 60)
    goto copy;
  if (smtp->eob == 61)
    goto copy;
  if (smtp->eob == 62)
    goto copy;
  if (smtp->eob == 63)
    goto copy;
  if (smtp->eob == 64)
    goto copy;
  if (smtp->eob == 65)
    goto copy;
  if (smtp->eob == 66)
    goto copy;
  if (smtp->eob == 67)
    goto copy;
  if (smtp->eob == 68)
    goto copy;
  if (smtp->eob == 69)
    goto copy;
  if (smtp->eob == 70)
    goto copy;
  if (smtp->eob == 71)
    goto copy;
  if (smtp->eob == 72)
    goto copy;
  if (smtp->eob == 73)
    goto copy;
  if (smtp->eob == 74)
    goto copy;
  if (smtp->eob == 75)
    goto copy;
  if (smtp->eob == 76)
    goto copy;
  if (smtp->eob == 77)
    goto copy;
  if (smtp->eob == 78)
    goto copy;
  if (smtp->eob == 79)
    goto copy;
  if (smtp->eob == 80)
    goto copy;
  if (smtp->eob == 81)
    goto copy;
  if (smtp->eob == 82)
    goto copy;
  if (smtp->eob == 83)
    goto copy;
  if (smtp->eob == 84)
    goto copy;
  if (smtp->eob == 85)
    goto copy;
  if (smtp->eob == 86)
    goto copy;
  if (smtp->eob == 87)
    goto copy;
  if (smtp->eob == 88)
    goto copy;
  if (smtp->eob == 89)
    goto copy;
  if (smtp->eob == 90)
    goto copy;
  if (smtp->eob == 91)
    goto copy;
  if (smtp->eob == 92)
    goto copy;
  if (smtp->eob == 93)
    goto copy;
  if (smtp->eob == 94)
    goto copy;
  if (smtp->eob == 95)
    goto copy;
  if (smtp->eob == 96)
    goto copy;
  if (smtp->eob == 97)
    goto copy;
  if (smtp->eob == 98)
    goto copy;
  if (smtp->eob == 99)
    goto copy;
  if (smtp->eob == 100)
    goto copy;
  if (smtp->eob == 101)
    goto copy;