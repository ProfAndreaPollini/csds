#ifndef CSDS_LIST_H
#define CSDS_LIST_H

void hello(void);

#define TRUE 1
#define FALSE 0

typedef struct csds_list_item {
    void*data;
    struct csds_list_item* p_next;
} csds_list_item_t;

typedef struct csds_list {
    csds_list_item_t* p_head;
    csds_list_item_t* p_tail;

    int item_size;
    int size;
} csds_list_t;

csds_list_t* csds_list_create(int item_size);
void csds_free_list(csds_list_t*list);
void csds_free_list_remove_last(csds_list_t*list);
csds_list_item_t* csds_list_append(csds_list_t*list);
csds_list_item_t* csds_list_insert(csds_list_t*list, int pos);
void csds_list_remove(csds_list_t*list, int pos);

csds_list_t* csds_list_map(csds_list_t*list, void (*fn)(csds_list_item_t*new_el,csds_list_item_t*el));
csds_list_t* csds_list_filter(csds_list_t*list, void (*fn)(csds_list_t*list,csds_list_item_t*el));

void* csds_list_find(csds_list_t*list, int (*fn)(void*data));

#endif //CSDS_LIST_H
