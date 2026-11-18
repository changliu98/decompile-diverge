#include <linux/types.h>

#include <linux/limits.h>

#include <sys/ioctl.h>

static inline void set_autofs_type_direct(unsigned int *type)
{
 *type = 2U;
}
