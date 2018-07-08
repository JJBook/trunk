#ifndef __KLIST_H
#define __KLIST_H

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({		      \
	const typeof(((type *)0)->member)*__mptr = (ptr);    \
	(type *)((char *)__mptr - offsetof(type, member)); })

struct list_head
{
	struct list_head* prev;
	struct list_head* next;
};

#define LIST_HEAD_INIT(name) {&(name), &(name)}
#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name) 


static inline void INIT_LIST_HEAD(struct list_head* list)
{
	list->prev = list;
	list->next = list;
}

static inline void __list_add(struct list_head* new, struct list_head* prev, struct list_head* next)
{
	prev->next = new;
	new->next = next;
	new->prev = prev;
	next->prev = new;
}

static void list_add(struct list_head* new, struct list_head* head) 
{
	__list_add(new, head, head->next);
}

static inline void list_add_tail(struct list_head* new, struct list_head* head)
{
	__list_add(new, head->prev, head);
}

static inline void __list_del(struct list_head* prev, struct list_head* next)
{
	prev->next = next;
	next->prev = prev;
}

static inline void list_del(struct list_head* entry)
{
	__list_del(entry->prev, entry->next);
	entry->next = (void*)0x00100100;
	entry->prev = (void*)0x00200200;
}

static inline void __list_del_entry(struct list_head* entry)
{
	__list_del(entry->prev, entry->next);
}

static inline void list_del_init(struct list_head* entry)
{
	__list_del_entry(entry);
	INIT_LIST_HEAD(entry);
}

static inline void list_replace(struct list_head* new, struct list_head* old)
{
	new->next = old->next;
	new->prev = old->prev;
	old->next->prev = new;
	old->prev->next = new;
}

static inline void list_replace_init(struct list_head* new, struct list_head* old)
{
	list_replace(new, old);
	INIT_LIST_HEAD(old);
}

//move a entry in one list to another list
static inline void list_move(struct list_head* entry, struct list_head* head)
{
	__list_del_entry(entry);
	list_add(entry, head);
}

static inline void list_move_tail(struct list_head* entry, struct list_head* head)
{
	__list_del_entry(entry);
	list_add_tail(entry, head);
}

static inline int list_is_last(struct list_head* entry, struct list_head* head)
{
	return entry->next == head;
}

static inline int list_is_empty(struct list_head* head)
{
	return head->next == head;
}

static inline int list_empty_careful(struct list_head* head)
{
	struct list_head* next = head->next;
	return (next == head) && (next == head->prev);
}

/*
 * ���ֱ���:
 * 1.����ڵ�����һ��, ������������ͷ����,�����ϵĽڵ�ѭ������һ��
 *		h 1 2 3
 *		h 2 3 1
 * 2.����ͷ�͵�һ���ڵ㽻��һ��
 * 		h 1 2 3
 * 		1 h 2 3
 */
static inline void list_rotate_left(struct list_head* head)
{
	struct list_head* first;
	if (!list_empty_careful(head))
	{
		first = head->next;
		list_move_tail(first, head);
	}
}

//tests whether a list has just one entry
static inline int list_is_singular(struct list_head* head)
{
	return (!list_empty_careful(head)) && (head->next == head->prev);
}

static inline void __list_cut_position(struct list_head* list, struct list_head* head, struct list_head* entry)
{
	struct list_head* new_first = entry->next;
	list->next = head->next;
	head->next->prev = list;
	list->prev = entry;
	entry->next = list;

	head->next = new_first;
	new_first->prev = head;
}

/*
 *	list: 	�����к�ڵ��¼��������
 *  head: 	�����е�����
 *  entry:	head�����еĽڵ�
 *
 *  ˵��:	
 *  		1.entry: head�����б����������ڵ�,�ɵ����߱�֤,��head������û��entry����ڵ�,�����δ֪���.
 *  		1.����entry�ڵ�(including)֮ǰ�����нڵ����, ���뵽list
 *          2.list����Ӧ��Ϊ�����������������޹ؽ�Ҫ������
 *          3.�������ɼ��:
 *          				headΪ��;
 *          				headΪ���ڵ������Ҳ���entry;
 *          				head == entry
 *
 *
 *  	head 1 2 3 4 5 6 7 8
 *  	entry����Ϊ��5���ڵ�
 *
 *  ���:
 *  	head 6 7 8 
 *  	list 1 2 3 4 5  
 */
static inline void list_cut_position(struct list_head* list, struct list_head* head, struct list_head* entry)
{
	if (list_is_empty(head))
		return;
	if (list_is_singular(head) && (entry != head && entry != head->next))
		return;

	if (entry == head)
		INIT_LIST_HEAD(list);
	else
		__list_cut_position(list, head, entry);
}


static inline void __list_splice(const struct list_head* list, struct list_head* prev, struct list_head* next)
{
	struct list_head* first = list->next;
	struct list_head* last = list->prev;

	first->prev = prev;
	prev->next = first;

	last->next = next;
	next->prev = last;
}

//��list�����еĽڵ�ȫ��ƴ�ӵ�head������,����ͷ��
static inline void list_splice(struct list_head* list, struct list_head* head)
{
	if (!list_is_empty(list))
		__list_splice(list, head, head->next);
}

//��list�����еĽڵ�ȫ��ƴ�ӵ�head������,����β��
static inline void list_splice_tail(struct list_head* list, struct list_head* head)
{
	if (!list_is_empty(list))
		__list_splice(list, head->prev, head);
}

static inline void list_splice_init(struct list_head* list, struct list_head* head)
{
	if (!list_is_empty(list))
	{
		__list_splice(list, head, head->next);
		INIT_LIST_HEAD(list);//reinitialise the emptied list
	}
}

static inline void list_splice_tail_init(struct list_head* list, struct list_head* head)
{
	if (!list_is_empty(list))
	{
		__list_splice(list, head->prev, head);
		INIT_LIST_HEAD(list);//reinitialise the emptied list
	}
}

/*
 *	ptr:	struct list_headָ��
 *	type:	container struct type
 *	name:	struct list_head ��Ա��
 *
 *	���ptr����container�ṹ����׵�ַ.
 */
#define list_entry(ptr, type, name) \
	container_of(ptr, type, name)

#define list_first_entry(ptr, type, name) \
	list_entry((ptr)->next, type, name)

//����ÿ��struct list_head
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_prev(post, head)	\
	for (pos = (head)->prev; pos != (head); pos = pos->prev)

//����ÿ��container�ṹ��
#define list_for_each_entry(pos, head, name)	\
	for (pos = list_entry((head)->next, typeof(*pos), name);	\
			&(pos->name) != (head);	\
			pos = list_entry(pos->name.next, typeof(*pos), name))	

/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_entry((head)->next, typeof(*pos), member),	\
		n = list_entry(pos->member.next, typeof(*pos), member);	\
	     &pos->member != (head); 					\
	     pos = n, n = list_entry(n->member.next, typeof(*n), member))



/**
* list_for_each_safe - iterate over a list safe against removal of list entry
* @pos:    the &struct list_head to use as a loop cursor.
* @n:      another &struct list_head to use as temporary storage
* @head:   the head for your list.
*/
#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)


#endif
