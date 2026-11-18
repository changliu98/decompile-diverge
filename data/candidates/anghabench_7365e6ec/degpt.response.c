// Calculates the number of used sequence numbers in the window.
// Parameters:
//   ns: The current sequence number.
//   dnr: The difference between the next expected sequence number and the current one.
// Returns:
//   The count of used sequence numbers based on the relationship between ns and dnr.
int llc_shdlc_w_used(int current_seq, int seq_diff)
{
    // If ns is less than dnr, calculate 8 - dnr; otherwise, return -dnr.
    return current_seq + (current_seq < seq_diff ? 8 - seq_diff : -seq_diff);
}