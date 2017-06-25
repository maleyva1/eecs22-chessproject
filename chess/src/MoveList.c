#include "MoveList.h"
#include <assert.h>
MoveList *newList(void)
{
    MoveList *list;
    list = malloc(sizeof(MoveList));
    if(!list)
    {
        perror("Cannot allocate space more new Moves List");
        return NULL;
    }

    list->mostRecent = NULL;
    list->last = NULL;
    
    return list;
}

MoveEntry *newEntry(Move *move)
{
    MoveEntry *entry;
    entry = malloc(sizeof(MoveEntry));
    if(!entry)
    {
        perror("Cannot allocated memotry for move entry.");
        return NULL;
    }

    entry->list = NULL;
    entry->next = NULL;
    entry->prev = NULL;
    entry->index = move;

    return entry;
}

void addMove(MoveList *list, MoveEntry *entry)
{
assert(entry->index->Xbefore >= 0);
assert(entry->index->Ybefore >= 0);
assert(entry->index->Xafter >= 0);
assert(entry->index->Yafter >= 0);
    if(!list)
    {
        perror("List is empty.");
    }

    entry->list = list;

    /* If List is empty */
    if(list->mostRecent == NULL && list->last == NULL)
    {
        list->mostRecent = entry;
        list->last = entry;
    }
    else if(list->mostRecent == list->last)
    {
        list->mostRecent = entry;
        list->last->prev = entry;
        list->mostRecent->next = list->last;
    }
    else
    {
        list->mostRecent->prev =entry;
        entry->next = list->mostRecent;
        list->mostRecent = entry;
    }
}

/* This function is wrong I need to fix the implementation */
Move *getMostRecentMove(MoveList *list)
{
assert(list->mostRecent->index);
assert(list->mostRecent->index->Xbefore >= 0);
assert(list->mostRecent->index->Ybefore >= 0);
assert(list->mostRecent->index->Yafter >= 0);
assert(list->mostRecent->index->Xafter >= 0);
    Move *temp;
    if(!list)
    {
        perror("List is empty.");
        return NULL;
    }
    /* If there's only one item in the list */
    else if(list->mostRecent == list->last)
    {
        temp = list->mostRecent->index;
        list->mostRecent = NULL;
        list->last = NULL;
        return temp;
    }
    else
    {
        temp = list->mostRecent->index;
        list->mostRecent = list->mostRecent->next;
        list->mostRecent->prev = NULL;
        return temp;
    }
}
