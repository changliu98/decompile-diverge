int __cdecl hci_req_sync(
        hci_dev *hdev,
        int (*req)(hci_request *, unsigned __int64),
        unsigned __int64 opt,
        u32 timeout,
        u8 *hci_status)
{
  // Check if the HCI device is up (typically bit 0 corresponds to HCI_UP)
  if (!test_bit(0, &hdev->flags))
    return -100; // -100 corresponds to -ENETDOWN in Linux

  // Serialize access to the HCI request mechanism
  mutex_lock(&hdev->req_lock);
  
  // Execute the synchronous request
  int ret = _hci_req_sync(hdev, req, opt, timeout, hci_status);
  
  mutex_unlock(&hdev->req_lock);
  
  return ret;
}