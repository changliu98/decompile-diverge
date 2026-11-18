int hci_req_sync(struct hci_dev *hdev, int (*req)(struct hci_request *, void *),
                 void *data, u32 tmout, __u8 *status) {
  int err;
  if (!test_bit(0, &hdev->flags)) return -100;
  mutex_lock(&hdev->req_mutex);
  err = __hci_req_sync(hdev, req, data, tmout, status);
  mutex_unlock(&hdev->req_mutex);
  return err;
}