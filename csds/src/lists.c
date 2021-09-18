//
// Created by pollini on 13/09/2021.
//

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

csds_list_t* csds_list_create(int item_size)
{
    csds_list_t*new_list = (csds_list_t*)malloc(sizeof(csds_list_t));
    new_list->item_size = item_size;
    new_list->size=0;

    new_list->p_head = NULL;
    new_list->p_tail = NULL;

    return new_list;
}


void csds_free_list_remove_last(csds_list_t* list)
{
    csds_list_item_t *current = list->p_head;
    while (current->p_next != list->p_tail) {
        current = current->p_next;
    }
    free(current->p_next->data);
    free(current->p_next);
    current->p_next = NULL;
    list->p_tail = current;
    list->size--;
}

void csds_free_list(csds_list_t* list)
{
    csds_list_item_t* p_el = list->p_head;
    while(p_el != NULL) {

        csds_list_item_t* p_next = p_el->p_next;
        free(p_el->data);
//        p_el = list->p_head->p_next;
        free(list->p_head);
        list->size--;
        list->p_head = p_next;
        p_el = list->p_head;
    }
    list->p_tail=NULL;
    free(list);
}

csds_list_item_t* csds_list_append(csds_list_t* list)
{
    csds_list_item_t* new_element = (csds_list_item_t*) malloc(sizeof(csds_list_item_t));
//    new_element->data = malloc(list->item_size);
    new_element->p_next=NULL;

    if(list->size == 0) {
        list->p_head = new_element;

    }  else {
        csds_list_item_t *current = list->p_head;
        while (current->p_next != NULL) {
            current = current->p_next;
        }
        current->p_next = new_element;
    }


    list->size++;
    list->p_tail = new_element;
    return new_element;
}

csds_list_item_t* csds_list_insert(csds_list_t*list, int pos){
    if(pos > list->size) return NULL;

    csds_list_item_t* new_element = (csds_list_item_t*) malloc(sizeof(csds_list_item_t));
    new_element->p_next = NULL;
    if (pos ==0) {
        new_element->p_next = list->p_head;
        list->p_head = new_element;
        list->size++;
        return new_element;
    }
     if (pos == list->size) {
         list->p_tail->p_next = new_element;
         list->p_tail = new_element;
         list->size++;
         return new_element;
        }

    csds_list_item_t *current = list->p_head;
    while(--pos >0) {
        current = current->p_next;
    }

    new_element->p_next=current->p_next;
    current->p_next = new_element;
    list->size++;

    return new_element;
}
void csds_list_remove(csds_list_t*list, int pos){
    if(pos >= list->size) return;
    if (pos ==0) {
        csds_list_item_t *next_element = list->p_head->p_next;
        free(list->p_head->data);
        free(list->p_head);
        list->p_head = next_element;
        return;
    }

    csds_list_item_t *prev_element = list->p_head;



    while(--pos >0) {
        prev_element = prev_element->p_next;
    }

    csds_list_item_t *current_element = prev_element->p_next;
    csds_list_item_t *next_element = prev_element->p_next->p_next;

    free(current_element->data);
    free(current_element);

    prev_element->p_next = next_element;
    list->size--;
}

csds_list_t* csds_list_map(csds_list_t*l,
                           void (*fn)(csds_list_item_t*new_el,csds_list_item_t*el)){
    csds_list_t* mapped = csds_list_create(l->item_size);

    //scorro gli elementi
    csds_list_item_t*current = l->p_head;

    while(current != NULL) {
        csds_list_item_t* new_element = csds_list_append(mapped);
        fn(new_element,current);
        current = current->p_next;
    }
    return mapped;
}

csds_list_t* csds_list_filter(csds_list_t* l, void (*fn)(csds_list_t*list,csds_list_item_t*el))
{
    csds_list_t* filtered = csds_list_create(l->item_size);
    //scorro gli elementi
    csds_list_item_t*current = l->p_head;

    while(current != NULL) {

        fn(filtered,current);
        current = current->p_next;
    }
    return filtered;
}

void* csds_list_find(csds_list_t*l, int (*fn)(void*data))
{
    csds_list_item_t*current = l->p_head;

    while(current != NULL) {

        if(fn(current->data) == TRUE) {
            return current->data;
        }
        current = current->p_next;
    }
    return NULL;
}