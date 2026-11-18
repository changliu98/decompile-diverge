/* cve_barebone direct-call harness for CVE (resiprocate vendored c-ares)
 * Target: ares_parse_a_reply  (rutil/dns/ares/ares_parse_a_reply.c)
 * Bug class: heap-buffer-overflow READ (CWE-125).
 *
 * Root cause (from the fix diff, commit d67a9ca6fd06ca65d23e313bdbad1ef4dd3aa0df):
 *   after decoding an answer RR's fixed header (`aptr += RRFIXEDSZ`), the vulnerable
 *   version does NOT verify that the RR's data field (`rr_len` bytes at `aptr`) actually
 *   fits inside the message buffer before using it. The fix inserts:
 *       if (aptr + rr_len > abuf + alen) { free(rr_name); status = ARES_EBADRESP; break; }
 *   Without that guard, a T_A record whose declared rr_len == sizeof(struct in_addr) (4)
 *   but whose actual remaining buffer is shorter causes
 *       memcpy(&addrs[naddrs], aptr, sizeof(struct in_addr));
 *   to read past the end of the (heap-allocated, attacker-sized) `abuf` buffer.
 *
 * ares_expand_name (used to decode both the question name and RR names, including
 * message-compression pointers) is copied verbatim from the sibling file
 * data_cve/cve_126b0499/source_code/rutil/dns/ares/ares_expand_name.c -- it is the
 * direct, unmodified dependency ares_parse_a_reply calls into; nothing here is invented.
 *
 * Build (dc_batch/dc_try, in cvf-builder):
 *   clang -fsanitize=address -fno-omit-frame-pointer -g -O1 harness.c -lm
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/nameser.h>
#include <arpa/nameser_compat.h>

/* ---- status codes, verbatim subset from source_code/rutil/dns/ares/ares.h ---- */
#define ARES_SUCCESS      0
#define ARES_ENODATA      1
#define ARES_EBADNAME     8
#define ARES_EBADRESP     10
#define ARES_ENOMEM       15

/* ==== VERBATIM subset from data_cve/cve_126b0499/source_code/rutil/dns/ares/ares_dns.h
 * (the project's OWN header-field-parsing macros ares_parse_a_reply uses -- distinct from
 * the system <arpa/nameser.h> constants HFIXEDSZ/QFIXEDSZ/RRFIXEDSZ/C_IN/T_A/T_CNAME/
 * INDIR_MASK, which the vendored ares_dns.h assumes are already in scope.) ==== */
#define DNS__16BIT(p)			(((p)[0] << 8) | (p)[1])
#define DNS__32BIT(p)			(((p)[0] << 24) | ((p)[1] << 16) | \
					 ((p)[2] << 8) | (p)[3])
#define DNS_HEADER_QDCOUNT(h)		DNS__16BIT((h) + 4)
#define DNS_HEADER_ANCOUNT(h)		DNS__16BIT((h) + 6)
#define DNS_RR_TYPE(r)			DNS__16BIT(r)
#define DNS_RR_CLASS(r)			DNS__16BIT((r) + 2)
#define DNS_RR_TTL(r)			DNS__32BIT((r) + 4)
#define DNS_RR_LEN(r)			DNS__16BIT((r) + 8)
/* ==== end verbatim ares_dns.h subset ==== */

/* ==== VERBATIM from data_cve/cve_126b0499/source_code/rutil/dns/ares/ares_expand_name.c ====
 * (ares_parse_a_reply's own direct dependency: decodes RFC1035 encoded names, including
 * message-compression pointers, honouring abuf/alen bounds itself.) */
static int name_length(const unsigned char *encoded, const unsigned char *abuf,
		       int alen);

int ares_expand_name(const unsigned char *encoded, const unsigned char *abuf,
		     int alen, char **s, long *enclen)
{
  int len, indir = 0;
  char *q;
  const unsigned char *p;

  len = name_length(encoded, abuf, alen);
  if (len == -1)
    return ARES_EBADNAME;
  *s = malloc(len + 1);
  if (!*s)
    return ARES_ENOMEM;
  q = *s;

  /* No error-checking necessary; it was all done by name_length(). */
  p = encoded;
  while (*p)
    {
      if ((*p & INDIR_MASK) == INDIR_MASK)
	{
	  if (!indir)
	    {
	      *enclen = (long)(p + 2 - encoded);
	      indir = 1;
	    }
	  p = abuf + ((*p & ~INDIR_MASK) << 8 | *(p + 1));
	}
      else
	{
	  len = *p;
	  p++;
	  while (len--)
	    {
	      if (*p == '.' || *p == '\\')
		*q++ = '\\';
	      *q++ = *p;
	      p++;
	    }
	  *q++ = '.';
	}
    }
  if (!indir)
    *enclen = (long)(p + 1 - encoded);

  /* Nuke the trailing period if we wrote one. */
  if (q > *s)
    q--;
  /* Write a trailing NUL in any case. */
  *q = 0;

  return ARES_SUCCESS;
}

static int name_length(const unsigned char *encoded, const unsigned char *abuf,
		       int alen)
{
  int n = 0, offset, indir = 0;

  if (encoded == abuf + alen)
    return -1;

  while (*encoded)
    {
      if ((*encoded & INDIR_MASK) == INDIR_MASK)
	{
	  if (encoded + 1 >= abuf + alen)
	    return -1;
	  offset = (*encoded & ~INDIR_MASK) << 8 | *(encoded + 1);
	  if (offset >= alen)
	    return -1;
	  encoded = abuf + offset;

	  if (++indir > alen)
	    return -1;
	}
      else
	{
	  offset = *encoded;
	  if (encoded + offset + 1 >= abuf + alen)
	    return -1;
	  encoded++;
	  while (offset--)
	    {
	      n += (*encoded == '.' || *encoded == '\\') ? 2 : 1;
	      encoded++;
	    }
	  n++;
	}
    }

  return (n) ? n - 1 : n;
}
/* ==== end verbatim ares_expand_name.c ==== */

/* ==== VERBATIM from data_cve/cve_126b0499/target/original_function.c ==== */
int ares_parse_a_reply(const unsigned char *abuf, int alen,
		       struct hostent **host)
{
  unsigned int qdcount, ancount;
  int status, i, rr_type, rr_class, rr_len, naddrs;
  long int len;
  int naliases;
  const unsigned char *aptr;
  char *hostname, *rr_name, *rr_data, **aliases;
  struct in_addr *addrs;
  struct hostent *hostent;

  /* Set *host to NULL for all failure cases. */
  *host = NULL;

  /* Give up if abuf doesn't have room for a header. */
  if (alen < HFIXEDSZ)
    return ARES_EBADRESP;

  /* Fetch the question and answer count from the header. */
  qdcount = DNS_HEADER_QDCOUNT(abuf);
  ancount = DNS_HEADER_ANCOUNT(abuf);
  if (qdcount != 1)
    return ARES_EBADRESP;

  /* Expand the name from the question, and skip past the question. */
  aptr = abuf + HFIXEDSZ;
  status = ares_expand_name(aptr, abuf, alen, &hostname, &len);
  if (status != ARES_SUCCESS)
    return status;
  if (aptr + len + QFIXEDSZ > abuf + alen)
    {
      free(hostname);
      return ARES_EBADRESP;
    }
  aptr += len + QFIXEDSZ;

  /* Allocate addresses and aliases; ancount gives an upper bound for both. */
  addrs = malloc(ancount * sizeof(struct in_addr));
  if (!addrs)
    {
      free(hostname);
      return ARES_ENOMEM;
    }
  aliases = malloc((ancount + 1) * sizeof(char *));
  if (!aliases)
    {
      free(hostname);
      free(addrs);
      return ARES_ENOMEM;
    }
  naddrs = 0;
  naliases = 0;

  /* Examine each answer resource record (RR) in turn. */
  for (i = 0; i < (int)ancount; i++)
    {
      /* Decode the RR up to the data field. */
      status = ares_expand_name(aptr, abuf, alen, &rr_name, &len);
      if (status != ARES_SUCCESS)
	break;
      aptr += len;
      if (aptr + RRFIXEDSZ > abuf + alen)
	{
	  free(rr_name);
	  status = ARES_EBADRESP;
	  break;
	}
      rr_type = DNS_RR_TYPE(aptr);
      rr_class = DNS_RR_CLASS(aptr);
      rr_len = DNS_RR_LEN(aptr);
      aptr += RRFIXEDSZ;

      if (rr_class == C_IN && rr_type == T_A
	  && rr_len == sizeof(struct in_addr)
	  && strcasecmp(rr_name, hostname) == 0)
	{
	  memcpy(&addrs[naddrs], aptr, sizeof(struct in_addr));
	  naddrs++;
	  status = ARES_SUCCESS;
	}

      if (rr_class == C_IN && rr_type == T_CNAME)
	{
	  /* Record the RR name as an alias. */
	  aliases[naliases] = rr_name;
	  naliases++;

	  /* Decode the RR data and replace the hostname with it. */
	  status = ares_expand_name(aptr, abuf, alen, &rr_data, &len);
	  if (status != ARES_SUCCESS)
	    break;
	  free(hostname);
	  hostname = rr_data;
	}
      else
	free(rr_name);

      aptr += rr_len;
      if (aptr > abuf + alen)
	{
	  status = ARES_EBADRESP;
	  break;
	}
    }

  if (status == ARES_SUCCESS && naddrs == 0)
    status = ARES_ENODATA;
  if (status == ARES_SUCCESS)
    {
      /* We got our answer.  Allocate memory to build the host entry. */
      aliases[naliases] = NULL;
      hostent = malloc(sizeof(struct hostent));
      if (hostent)
	{
	  hostent->h_addr_list = malloc((naddrs + 1) * sizeof(char *));
	  if (hostent->h_addr_list)
	    {
	      /* Fill in the hostent and return successfully. */
	      hostent->h_name = hostname;
	      hostent->h_aliases = aliases;
	      hostent->h_addrtype = AF_INET;
	      hostent->h_length = sizeof(struct in_addr);
	      for (i = 0; i < naddrs; i++)
		hostent->h_addr_list[i] = (char *) &addrs[i];
	      hostent->h_addr_list[naddrs] = NULL;
	      *host = hostent;
	      return ARES_SUCCESS;
	    }
	  free(hostent);
	}
      status = ARES_ENOMEM;
    }
  for (i = 0; i < naliases; i++)
    free(aliases[i]);
  free(aliases);
  free(addrs);
  free(hostname);
  return status;
}
/* ==== end verbatim original_function.c ==== */

int main(int argc, char **argv)
{
  if (argc < 2)
    return 0;
  FILE *f = fopen(argv[1], "rb");
  if (!f)
    return 0;
  if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 0; }
  long sz = ftell(f);
  if (sz < 0) { fclose(f); return 0; }
  if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 0; }

  /* HEAP-allocate the input EXACTLY at the input length: `alen` == the heap
   * allocation size, so any RR data field that overruns the declared message
   * length also overruns the actual ASAN-guarded heap buffer -- no slack pad. */
  unsigned char *abuf = (unsigned char *)malloc((size_t)sz > 0 ? (size_t)sz : 1);
  if (!abuf) { fclose(f); return 0; }
  size_t n = fread(abuf, 1, (size_t)sz, f);
  fclose(f);

  struct hostent *host = NULL;
  int rc = ares_parse_a_reply(abuf, (int)n, &host);
  fprintf(stderr, "rc=%d host=%p\n", rc, (void *)host);

  free(abuf);
  return 0;
}
