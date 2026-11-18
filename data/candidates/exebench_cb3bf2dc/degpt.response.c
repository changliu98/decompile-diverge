/**
 * Sets the autofs mount type to indirect.
 *
 * @param type Pointer to the integer variable that will be set to 1,
 *             indicating an indirect mount type.
 */
void set_autofs_type_indirect(uint *mount_type)
{
    *mount_type = 1;
}