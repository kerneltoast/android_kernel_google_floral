/*
 * Copyright (C) 2014 BMW Car IT GmbH, Daniel Wagner daniel.wagner@bmw-carit.de
 * Copyright (C) 2022 Sultan Alsawaf <sultan@kerneltoast.com>.
 *
 * Provides a framework for enqueuing callbacks from irq context
 * PREEMPT_RT_FULL safe. The callbacks are executed in kthread context.
 */

#include <linux/swait.h>
#include <linux/swork.h>
#include <linux/kthread.h>

#define SWORK_EVENT_PENDING     1

static atomic_t run_sworks = ATOMIC_INIT(0);
static DECLARE_SWAIT_QUEUE_HEAD(swork_wq);
static LLIST_HEAD(swork_llist);

static int swork_kthread(void *arg)
{
	for (;;) {
		struct swork_event *sev, *tmp;
		struct llist_node *node;

		swait_event_interruptible(swork_wq,
					  (node = llist_del_all(&swork_llist)));

		llist_for_each_entry_safe(sev, tmp, node, item) {
			WARN_ON_ONCE(!test_and_clear_bit(SWORK_EVENT_PENDING,
							 &sev->flags));
			sev->func(sev);
		}
		atomic_set(&run_sworks, 0);
	}
	return 0;
}

/**
 * swork_queue - queue swork
 *
 * Returns %false if @work was already on a queue, %true otherwise.
 *
 * The work is queued and processed on a random CPU
 */
bool swork_queue(struct swork_event *sev)
{
	if (test_and_set_bit(SWORK_EVENT_PENDING, &sev->flags))
		return false;

	llist_add(&sev->item, &swork_llist);
	if (!atomic_cmpxchg_relaxed(&run_sworks, 0, 1))
		swake_up(&swork_wq);
	return true;
}

static int __init swork_init(void)
{
	struct task_struct *thread;

	thread = kthread_run(swork_kthread, NULL, "kswork");
	BUG_ON(IS_ERR(thread));
	return 0;
}
early_initcall(swork_init);
