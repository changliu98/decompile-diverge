#ifndef DDIV_H
#define DDIV_H
#include <stddef.h>

/* Optional: expose a local value or pointed-to buffer while it is still alive.
 * The last observation with a given name is its post-state. Observe initialized
 * bytes, not pointer addresses or uninitialized struct padding. No source changes
 * are needed for stdout/stderr, process status, files, or writable globals. */
void ddiv_observe(const char *name, const void *bytes, size_t size);
#define DDIV_OBSERVE(name, value) ddiv_observe((name), &(value), sizeof(value))

#endif
