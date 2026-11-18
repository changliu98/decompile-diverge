#include <sys/types.h>

#include <sys/stat.h>

#include <grp.h>

#include <unistd.h>

void
file_perms_get(
        const unsigned char *path,
        int *p_group,
        int *p_mode)
{
  struct stat stb;

  if (*p_group) *p_group = 0;
  if (*p_mode) *p_mode = 0;

  if (stat(path, &stb) < 0) return;

  if (p_group) *p_group = stb.st_gid;
  if (p_mode) *p_mode = stb.st_mode & 07777;
}
