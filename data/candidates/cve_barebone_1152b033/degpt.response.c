// Synchronous HCI request wrapper function
// Parameters:
//   hdev: Pointer to the HCI device structure
//   req: Function pointer to the HCI request handler
//   opt: Optional parameter passed to the request handler
//   timeout: Timeout value in milliseconds for the request
//   hci_status: Pointer to store the HCI status code
// Returns:
//   -100 if the device is not open/ready
//   Otherwise, returns the result from __hci_req_sync
int hci_req_sync(hci_dev *hci_device, _func_int_hci_request_ptr_unsigned_long *request_handler, unsigned_long request_option, u32 timeout_ms, u8 *status_code)
{
    // Check if the HCI device is open (bit 0 of flags indicates open state)
    if (!test_bit(0, &hci_device->flags)) {
        return -100;
    }
    // Acquire the request lock to ensure thread-safe access
    mutex_lock(&hci_device->req_lock);
    // Call the internal synchronous HCI request function
    int result = __hci_req_sync(hci_device, request_handler, request_option, timeout_ms, status_code);
    // Release the request lock
    mutex_unlock(&hci_device->req_lock);
    // Return the result from the internal function
    return result;
}