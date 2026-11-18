/*
 * gcap_string - Converts a set of global capability flags into a string representation.
 *
 * @s: Pointer to the output buffer where the string will be written.
 * @c: The global capability flags to convert.
 *
 * This function checks each bit in the capability mask 'c' against known
 * global capability constants (CEPH_CAP_G*). For each set bit, it appends
 * a corresponding character to the string pointed to by 's' and advances
 * the pointer.
 *
 * The mapping is as follows:
 *   CEPH_CAP_GSHARED   -> 's'
 *   CEPH_CAP_GEXCL     -> 'x'
 *   CEPH_CAP_GCACHE    -> 'c'
 *   CEPH_CAP_GRD       -> 'r'
 *   CEPH_CAP_GWR       -> 'w'
 *   CEPH_CAP_GBUFFER   -> 'b'
 *   CEPH_CAP_GWREXTEND -> 'a'
 *   CEPH_CAP_GLAZYIO   -> 'l'
 *
 * Returns: Pointer to the end of the written string (i.e., the next position
 *          after the last character written).
 */
char * gcap_string(char *output_buffer,int capability_flags)
{
  /* Check for shared global capability */
  if ((capability_flags & CEPH_CAP_GSHARED) != 0) {
    *output_buffer = 's';
    output_buffer++;
  }
  /* Check for exclusive global capability */
  if ((capability_flags & CEPH_CAP_GEXCL) != 0) {
    *output_buffer = 'x';
    output_buffer++;
  }
  /* Check for cache global capability */
  if ((capability_flags & CEPH_CAP_GCACHE) != 0) {
    *output_buffer = 'c';
    output_buffer++;
  }
  /* Check for read global capability */
  if ((capability_flags & CEPH_CAP_GRD) != 0) {
    *output_buffer = 'r';
    output_buffer++;
  }
  /* Check for write global capability */
  if ((capability_flags & CEPH_CAP_GWR) != 0) {
    *output_buffer = 'w';
    output_buffer++;
  }
  /* Check for buffer global capability */
  if ((capability_flags & CEPH_CAP_GBUFFER) != 0) {
    *output_buffer = 'b';
    output_buffer++;
  }
  /* Check for write extend global capability */
  if ((capability_flags & CEPH_CAP_GWREXTEND) != 0) {
    *output_buffer = 'a';
    output_buffer++;
  }
  /* Check for lazy I/O global capability */
  if ((capability_flags & CEPH_CAP_GLAZYIO) != 0) {
    *output_buffer = 'l';
    output_buffer++;
  }
  /* Return pointer to the end of the constructed string */
  return output_buffer;
}