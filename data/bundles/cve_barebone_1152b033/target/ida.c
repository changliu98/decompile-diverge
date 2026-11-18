int __cdecl hci_req_sync(
        hci_dev *hdev,
        int (*req)(hci_request *, unsigned __int64),
        unsigned __int64 opt,
        u32 timeout,
        u8 *hci_status)
{
  int ret; // [rsp+Ch] [rbp-34h]

  if ( !test_bit(0, &hdev->flags) )
    return -100;
  mutex_lock(&hdev->req_lock);
  ret = _hci_req_sync(hdev, req, opt, timeout, hci_status);
  mutex_unlock(&hdev->req_lock);
  return ret;
}