// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
#include <linux/init.h>
#include <linux/module.h>

#include "hello1.h"

static unsigned int hello_print_num_param = 1;

module_param_named(print_num, hello_print_num_param, uint, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(print_num, "Number of Hello, world printage");

static int __init hello_init(void)
{
	return hello_print(hello_print_num_param);
}

static void __exit hello_exit(void)
{
	/* Nothing for now */
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("Oleh Kuzhylnyi <o.kuzhyl@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");
