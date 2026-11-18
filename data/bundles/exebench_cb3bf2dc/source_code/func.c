#include <linux/types.h>

#include <linux/limits.h>

#include <sys/ioctl.h>

static inline void set_autofs_type_indirect(unsigned int *type)
{
 *type = 1U;
}
