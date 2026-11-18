#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/* ---- Real libredwg vocabulary, copied from source_code (real names) ---- */
#define ATTRIBUTE_MALLOC __attribute__ ((malloc))   /* src/common.h:259 */
typedef uint16_t BITCODE_RS;                         /* include/dwg.h:108 */
typedef BITCODE_RS *BITCODE_TU;                      /* include/dwg.h:207 (UCS-2) */

static unsigned int loglevel;                        /* src/bits.c:43 */
/* src/logging.h LOG_WARN/LOG_ERROR expand to statement blocks; off the crash
   path (pure logging), so faithful no-op blocks keep call sites valid even where
   the source omits a trailing ';' (e.g. LOG_ERROR ("Out of memory")). */
#define LOG_WARN(...)  { }
#define LOG_ERROR(...) { }

/* ===================== TARGET FUNCTION (verbatim) ===================== */
ATTRIBUTE_MALLOC
BITCODE_TU
bit_utf8_to_TU (char *restrict str, const unsigned cquoted)
{
  BITCODE_TU wstr;
  size_t i = 0;
  size_t len = strlen (str);
  unsigned char c;

  if (len > 0xFFFE)
    {
      loglevel = 1;
      LOG_WARN ("Overlong string truncated (len=%lu)",
                (unsigned long)len);
      len = UINT16_MAX - 1;
    }
  wstr = (BITCODE_TU)calloc (2, len + 1);
  if (!wstr)
    {
      loglevel = 1;
      LOG_ERROR ("Out of memory")
      return NULL;
    }
  while (len > 0 && (c = *str++))
    {
      len--;
      if (c < 128)
        {
          if (cquoted && c == '\\' && len > 1 &&
              // skip \" to " and \\ to \.
              (*str == '"' || *str == '\\' || *str == 'r'
               || *str == 'n'))
            {
              c = *str++;
              if (c == 'r')
                wstr[i++] = '\r';
              else if (c == 'n')
                wstr[i++] = '\n';
              // else skip \ and " from \\ and \"
              else
                wstr[i++] = c;
            }
          else
            wstr[i++] = c;
        }
      else if ((c & 0xe0) == 0xc0)
        {
          /* ignore invalid utf8 for now */
          if (len >= 1)
            wstr[i++] = ((c & 0x1f) << 6) | (str[1] & 0x3f);
          len--;
          str++;
        }
      else if ((c & 0xf0) == 0xe0)
        {
          /* ignore invalid utf8? */
          if (len >= 2
              && ((unsigned char)str[1] < 0x80 || (unsigned char)str[1] > 0xBF
                  || (unsigned char)str[2] < 0x80
                  || (unsigned char)str[2] > 0xBF))
            {
              LOG_WARN ("utf-8: BAD_CONTINUATION_BYTE %s", str);
            }
          if (len >= 1 && c == 0xe0 && (unsigned char)str[1] < 0xa0)
            {
              LOG_WARN ("utf-8: NON_SHORTEST %s", str);
            }
          if (len >= 2)
            wstr[i++] = ((c & 0x0f) << 12) | ((str[1] & 0x3f) << 6)
                        | (str[2] & 0x3f);
          str++;
          str++;
          len--;
          len--;
        }
      /* everything above 0xf0 exceeds ucs-2, 4-6 byte seqs */
    }
  return wstr;
}

/* ============================ direct-call driver ============================ */
int
main (int argc, char **argv)
{
  if (argc < 2)
    return 0;
  FILE *f = fopen (argv[1], "rb");
  if (!f)
    return 0;
  fseek (f, 0, SEEK_END);
  long sz = ftell (f);
  fseek (f, 0, SEEK_SET);
  if (sz < 0)
    {
      fclose (f);
      return 0;
    }
  unsigned char *data = (unsigned char *) malloc ((size_t) sz + 1);
  size_t n = fread (data, 1, (size_t) sz, f);
  fclose (f);
  data[n] = 0;

  /* FDP-style: first byte -> cquoted scalar; the rest -> the heap string arg.
     str is a tight malloc so any read past its end is ASAN-guarded. */
  unsigned cquoted = 0;
  size_t off = 0;
  if (n >= 1)
    {
      cquoted = (unsigned) (data[0] & 1u);
      off = 1;
    }
  size_t slen = n - off;
  char *str = (char *) malloc (slen + 1);
  memcpy (str, data + off, slen);
  str[slen] = '\0';

  BITCODE_TU r = bit_utf8_to_TU (str, cquoted);

  free (r);
  free (str);
  free (data);
  return 0;
}
