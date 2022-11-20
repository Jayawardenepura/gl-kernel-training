// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
#include <linux/init.h>
#include <linux/module.h>

#include "hello1.h"

int hello_print(unsigned int n)
{
	size_t	i;
	int	rc;

	rc = 0;

	if (n >= 5 && n <= 10) {
		pr_warn("hello, wrong param value");
	} else if (n > 10) {
		rc = -EINVAL;
	}

	if (rc == 0) {
		for (i = 0; i < n; i++)
			pr_info("Hello, world!\n");
	}

	return rc;
}
EXPORT_SYMBOL_GPL(hello_print);

MODULE_AUTHOR("Oleh Kuzhylnyi <o.kuzhyl@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");
