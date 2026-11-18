/*
 * Converts an InfiniBand MTU value (in bytes) to the corresponding
 * IB_MTU_* enum constant.
 *
 * Parameters:
 *   mtu - The MTU size in bytes. Valid values are 256, 512, 1024, 2048, and 4096.
 *
 * Returns:
 *   The corresponding IB_MTU_* enum value on success.
 *   -1 if the provided MTU value is not recognized or invalid.
 */
int int_to_ibta_mtu(int mtu_bytes)
{
  /* Check for MTU size 256 bytes */
  if (mtu_bytes == 0x100) {
    return IB_MTU_256;
  }
  /* Check for MTU size 512 bytes */
  else if (mtu_bytes == 0x200) {
    return IB_MTU_512;
  }
  /* Check for MTU size 1024 bytes */
  else if (mtu_bytes == 0x400) {
    return IB_MTU_1024;
  }
  /* Check for MTU size 2048 bytes */
  else if (mtu_bytes == 0x800) {
    return IB_MTU_2048;
  }
  /* Check for MTU size 4096 bytes */
  else if (mtu_bytes == 0x1000) {
    return IB_MTU_4096;
  }
  /* Return error code for unsupported MTU values */
  else {
    return -1;
  }
}