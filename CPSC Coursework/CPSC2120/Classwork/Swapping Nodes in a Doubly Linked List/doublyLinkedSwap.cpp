/*
 * Name: Michael Joseph Ellis
 * Date Submitted: Feb 11, 2025
 * Class Section: 001
 * Assignment Name: Swapping Nodes in a Doubly Linked List
 */

#include "doublyLinkedSwap.h"

// Implement the following function:
// p and afterp are pointers to the nodes to be swapped.
void swapWithNext(Node * p)
{
    // ensure p and its next node are not the head or tail dummy nodes
    if (!p || !p->next || !p->prev || !p->next->next) return;
    
    Node *afterp = p->next; // this is the node to swap with
    Node *beforep = p->prev; // this is the node before p
    Node *afterAfterp = afterp->next; // the node after afterp
    
    // adjust the previous and next pointers
    beforep->next = afterp;
    afterp->prev = beforep;

    afterp->next = p;
    p->prev = afterp;

    p->next = afterAfterp;
    if (afterAfterp) afterAfterp->prev = p;
}

//Be sure to comment out the main() function when submitting to codePost
// int main()
// {
//     int array[] = {1, 3, 6, 10, 15, 21, 28, 36, 45, 55};
//     Node * head = arrayToList(array, 10);
//     printForwards(head);
//     printBackwards(getTail(head));
    
//     cout << "Swap [0],[1]" << endl;
//     Node * p = getNode(head, 0);
//     swapWithNext(p);
//     printForwards(head);
//     printBackwards(getTail(head));
    
//     cout << "Swap [4],[5]" << endl;
//     p = getNode(head, 4);
//     swapWithNext(p);
//     printForwards(head);
//     printBackwards(getTail(head));
    
//     cout << "Swap [8],[9]" << endl;
//     p = getNode(head, 8);
//     swapWithNext(p);
//     printForwards(head);
//     printBackwards(getTail(head));
// }

//Do not modify any functions below this line
Node * arrayToList(int array[], int size)
{
    Node * head;
    Node * p;
    int pos = 0;
    if (size > 0)
    {
        head = new Node();
        head->prev = nullptr;
        head->value = 0;
        p = head;
        while (pos < size)
        {
            p->next = new Node();
            p->next->prev = p;
            p = p->next;
            p->value = array[pos];
            pos++;
        }
        p->next = new Node();
        p->next->prev = p;
        p = p->next;
        p->value = 0;
        p->next = nullptr;
    }
    else
    {
        return nullptr;
    }
    return head;
}

//Return pointer to end of the list
Node * getTail(Node * head)
{
    Node * p = head;
    while (p->next != nullptr)
    {
        p = p->next;
    }
    return p;
}

//Return pointer to node with "index"
//First node "index" 0, second node "index" 1, ...
Node * getNode(Node * head, int index)
{
    int pos = 0;
    Node * p = head->next;
    if (pos == index)
    {
        return p;
    }
    else if (index < 0)
    {
        return head;
    }
    else
    {
        while (pos < index && p->next != nullptr)
        {
            p = p->next;
            pos++;
        }
    }
    return p;
}

//Print list forwards from start
void printForwards(Node * head)
{
    Node * p = head->next;
    while (p->next != nullptr)
    {
        cout << p->value << " ";
        p = p->next;
    }
    cout << endl;
}

//Print list backwards from end
void printBackwards(Node * tail)
{
    Node * p = tail->prev;
    while (p->prev != nullptr)
    {
        cout << p->value << " ";
        p = p->prev;
    }
    cout << endl;
}