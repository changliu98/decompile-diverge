static int
elf_print_buildid(struct magic_set *ms, unsigned char *eh, int swap,
    size_t nhdr, size_t shoff, size_t shentsize, size_t len,
    int *mflags)
{
 unsigned char buf[20];
 int rv;
 if (shentsize == sizeof(struct elf32_shdr) &&
     strcmp((char *)(eh + shoff), "GNU") == 0 &&
     nhdr == 3 && (len >= shentsize || len >= sizeof(struct elf32_shdr))) {
  unsigned char *shstr;
  unsigned int shstrndx;
  unsigned int shstrsz;
  char *shstrtab;
  char *shstrtabend;
  char *shstrtabp;
  char *shstrtabnp;
  char *shstrtabpp;
  char *shstrtabnpp;
  char *shstrtabnppp;
  char *shstrtabnpppp;
  char *shstrtabnppppp;
  char *shstrtabnpppppp;
  char *shstrtabnpppppp;
  char *shstrtabnpppppp;
  char *shstrtabnpppppp;
  char *shstrtabnpppppp;
  char *shstrtabnpppppp;
  char *shstrtabnpppppp;

  *mflags |= 0x00000010;

  shstrndx = ((struct elf32_shdr *)(eh + shoff))[1].sh_link;
  shstrsz = ((struct elf32_shdr *)(eh + shoff))[1].sh_size;
  shstr = (unsigned char *)eh + ((struct elf32_shdr *)(eh + shoff))[1].sh_offset;
  if (file_printf(ms, ", BuildID[%s]=",
      (shstrsz == 8 ? "xxHash" :
      (shstrsz == 16 ? "md5/uuid" :
      (shstrsz == 20 ? "sha1" : "unknown"))) == -1)
   return 1;
  memcpy(buf, shstr, shstrsz);
  for (rv = 0; rv < shstrsz; rv++) {
   if (file_printf(ms, "%02x", buf[rv]) == -1)
    return 1;
  }
  return 1;
 } else
  return 0;
}