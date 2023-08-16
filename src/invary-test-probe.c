/*****************************************************************************
 * Invary Test Probe Module
 * Copyright (C) 2023 Invary, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * For the complete terms of the GNU General Public License, please see this URL:
 * http://www.gnu.org/licenses/gpl-2.0.html
 *
 ****************************************************************************/

#include <linux/module.h>

#define VERSION_STR		    "0.0.1"
#define INVARY_TEST_PROBE_TAG       "INVARY-TEST-PROBE: "

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Invary Test Probe Module");
MODULE_AUTHOR("Paul Couto (paul@invary.com)");
MODULE_VERSION(VERSION_STR);

// Not real eicar data as that would be problematic!
char *invary_test_probe = "EICAR-STANDARD-KERNEL-TEST-FILE!";

int invary_test_probe_init(void);
void invary_test_probe_exit(void);

int invary_test_probe_init(void) {
    printk(KERN_ALERT INVARY_TEST_PROBE_TAG "initialized\n");
    return 0;
}

void invary_test_probe_exit(void) {
    printk(KERN_ALERT INVARY_TEST_PROBE_TAG "exited\n");
}

EXPORT_SYMBOL(invary_test_probe);
module_init(invary_test_probe_init);
module_exit(invary_test_probe_exit);
