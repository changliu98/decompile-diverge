//

#define NULL ((void*)0)
  // Customize by platform.
 
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
#define  OHCI_USB_OPER 131 
#define  OHCI_USB_RESET 130 
#define  OHCI_USB_RESUME 129 
#define  OHCI_USB_SUSPEND 128 

char *hcfs2string(int state)
{
	switch (state) {
	case OHCI_USB_RESET:
		return "reset";
	case OHCI_USB_RESUME:
		return "resume";
	case OHCI_USB_OPER:
		return "operational";
	case OHCI_USB_SUSPEND:
		return "suspend";
	}
	return "?";
}
