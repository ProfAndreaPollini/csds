//
// Created by pollini on 13/09/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct test {
    int value;
} test_t;

void print_list(csds_list_t* l) {
    csds_list_item_t *current = l->p_head;
    printf("<--->\n");
    while (current != NULL) {
        printf("v[%p] = %d\n",current,((test_t*)current->data)->value);
        current = current->p_next;
    }
    printf("<--->\n");
}

void f(csds_list_item_t*new_el,csds_list_item_t*el)
{
    test_t* v = malloc(sizeof(test_t));
    v->value = ((test_t*)el->data)->value * 2;
    new_el->data = v;
}

void filter_test_f(csds_list_t* l,csds_list_item_t*el)
{
    if (((test_t*)el->data)->value>41) {
        csds_list_item_t *new_el = csds_list_append(l);
        test_t *v = malloc(sizeof(test_t));
        v->value = ((test_t *) el->data)->value;
        new_el->data = v;
    }
}


 int find_test_f(void*data) {
    test_t* d = (test_t*)data;

    if (d->value == 42) {
        return TRUE;
    }

    return FALSE;
}
int main() {
    csds_list_t* l = csds_list_create(sizeof(test_t));
    csds_list_item_t*el = csds_list_append(l);

    test_t* v1 = malloc(sizeof(test_t));
    v1->value = 41;

    el->data = v1;


    test_t* v2 = malloc(sizeof(test_t));
    v2->value = 42;
    csds_list_item_t* el2 = csds_list_append(l);
    el2->data = v2;

    test_t* v3 = malloc(sizeof(test_t));
    csds_list_item_t* el3 =csds_list_insert(l,1);
    v3->value = 43;
    el3->data = v3;

    test_t* v4 = malloc(sizeof(test_t));
    csds_list_item_t* el4 =csds_list_insert(l,1);
    v4->value = 44;
    el4->data = v4;

    print_list(l);
//    csds_free_list_queue(l);
//    print_list(l);
    csds_list_remove(l,1);
    print_list(l);
    csds_list_t* l1 =csds_list_map(l,f);

    print_list(l1);

    csds_list_t* l2 =csds_list_filter(l,filter_test_f);

    print_list(l2);

    test_t* ret = csds_list_find(l,find_test_f);
    if(ret) {
        printf("\n found !! \n");
    }
//    csds_list_remove(l,3);
//    print_list(l);

    return 0;
}