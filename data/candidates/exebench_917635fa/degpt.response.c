// Adds the values of in1, in2, and the current value pointed to by in_out1
// and stores the result back into the location pointed to by in_out1.
void adders_io(int first_operand, int second_operand, int *accumulator_pointer)
{
    // Update the value at in_out1 by adding in1, in2, and the original value at in_out1
    *accumulator_pointer = first_operand + second_operand + *accumulator_pointer;
}