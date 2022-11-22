// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>

#include "hello1.h"

struct hello_private {
	struct list_head node;
	ktime_t timestamp;
	ktime_t duration;
};

static LIST_HEAD(hello_list);

static void hello_list_free(void)
{
	struct hello_private *priv, *tmp;

	list_for_each_entry_safe(priv, tmp, &hello_list, node) {
		pr_info("hello, print timestamp: %lld ns\n", priv->timestamp);
		pr_info("hello, print duration: %lld ns\n", priv->duration);

		list_del(&priv->node);
		kfree(priv);
	}

	BUG_ON(!list_empty(&hello_list));
}

static int hello_add_node(void)
{
	struct hello_private	*priv;
	int			rc;

	priv = kmalloc(sizeof(*priv), GFP_KERNEL);
	rc = (priv == NULL) ? -ENOMEM : 0;

	if (rc == 0) {
		priv->timestamp = ktime_get();
		pr_info("Hello, world!\n");
		priv->duration = ktime_get() - priv->timestamp;

		list_add(&priv->node, &hello_list);
	}

	return rc;
}

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
		for (i = 0; i < n; i++) {
			rc = hello_add_node();
			if (rc != 0) break;
		}
	}

	if (rc == -ENOMEM)
		hello_list_free();

	return rc;
}
EXPORT_SYMBOL_GPL(hello_print);

void hello_destroy(void)
{
	hello_list_free();
}
EXPORT_SYMBOL_GPL(hello_destroy);

MODULE_AUTHOR("Oleh Kuzhylnyi <o.kuzhyl@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");
