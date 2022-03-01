#ifndef _LINUX_SWORK_H
#define _LINUX_SWORK_H

#include <linux/llist.h>

struct swork_event {
	struct llist_node item;
	unsigned long flags;
	void (*func)(struct swork_event *);
};

static inline void INIT_SWORK(struct swork_event *event,
			      void (*func)(struct swork_event *))
{
	event->flags = 0;
	event->func = func;
}

bool swork_queue(struct swork_event *sev);

static inline int swork_get(void) { return 0; }
static inline void swork_put(void) { }

#endif /* _LINUX_SWORK_H */
