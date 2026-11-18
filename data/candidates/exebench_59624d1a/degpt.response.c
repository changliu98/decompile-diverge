/**
 * set_autofs_type_any - Sets the autofs type to 'any'.
 * @type: Pointer to the autofs type variable to be set.
 *
 * This function initializes the autofs type to 0, which represents
 * the 'any' type in the autofs subsystem.
 */
void set_autofs_type_any(uint *autofs_type)
{
    *autofs_type = 0;
}