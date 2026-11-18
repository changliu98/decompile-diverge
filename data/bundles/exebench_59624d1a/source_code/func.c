#include <linux/types.h>

#include <linux/limits.h>

#include <sys/ioctl.h>

static inline void set_autofs_type_any(unsigned int *type)
{
 *type = 0U;
}
