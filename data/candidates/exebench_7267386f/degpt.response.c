int _hclib_atomic_dec_release(int *counter)
{
    // Acquire lock to ensure atomicity of the read-modify-write operation
    LOCK();
    
    // Read the current value of the target variable
    int previous_value = *counter;
    
    // Decrement the target variable by 1
    *counter = previous_value - 1;
    
    // Release the lock
    UNLOCK();
    
    // Return the decremented value
    return previous_value - 1;
}