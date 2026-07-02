#include <stdio.h>
#include <iostream>

class Item { // essencially an abstraction of each index
    public:
        const char* value = ""; // the value the index stores
        Item* nextItem = NULL; // the next item in the list
        Item(const char* val) { // constructor, initializes the class with the value it stores
            value = val;
        }
        void printValue() { // a quick print of the item in the array
            printf("%s\n", value);
        }
};

class LinkedList { // the container of the list
    public:
        Item* start = NULL; // every element needs to be allocated during run-time
        void add(const char* value) { // adds the 'value' to the list
            if (start == NULL) { // if the start value has not been assigned, then assign it now
                start = (Item*) malloc(sizeof(Item)); // allocates an item pointer of the size of item
                *(start) = Item (value);// dereference start to set the value to an Item with 'value'
                return;
            }
            // essentially looping through the items in the list until you get to the last defined item
            Item* curItem = start; // the start is the current item, also accounts for allocating the second item (x = 0)
            while (curItem->nextItem != NULL) { // ensrures you don't get a segfault by calling a NULL pointer (x < listSize)
                curItem = curItem->nextItem; // sets the current item to the next item in the list (x++)
            }
            curItem->nextItem = (Item*) malloc(sizeof(Item)); // allocate memory to the newest item to the list
            *(curItem->nextItem) = Item (value); // assign a value to the newest item in the list
        }

        void print() { // loop through the list and print out each item
            if (start == NULL) {printf("[]\n"); return;} // can't print out any item if there is no item
            Item* curItem = start; // same as adding an item you start with the first item (x=0)
            printf("["); // stylistic choice
            while (curItem->nextItem != NULL) { // (x < listLength) NULL is when the list stops
                printf("%s->", curItem->value); // print the index out
                curItem = curItem->nextItem; // (x++)
            }
            printf("%s]\n", curItem->value); // print the last item out
        }

        void kill() {
            if (start == NULL) return; // can't deallocate memory that you haven't allocated yet
            Item* curItem = start; // same as looping through the lists with the other two methods (x=0)
            while (curItem->nextItem != NULL) { // (x < listLength)
                Item* nextItem = curItem->nextItem; // get the next item before we free the current item
                free(curItem); // free our current item
                curItem = nextItem; // set the current item to the next item (x++)
            }
            free(curItem); // free the last item in the list
        }
};

int main() {
    LinkedList ll; // demonstration of the functionality
    ll.add("hello");
    ll.add("world");
    ll.add("what in the?");
    ll.add("why?");
    ll.add("how did you?");

    Item* why = ll.start->nextItem->nextItem->nextItem;
    Item* world = ll.start->nextItem;
    Item* how = ll.start->nextItem->nextItem->nextItem->nextItem;

    ll.print();

    ll.kill();
    // you know it's deallocated everything because uncommenting out the following lines will result in a segfault
    // ll.start->printValue();
    // why->printValue();
    // world->printValue();
    // how->printValue();

    return 0;
}