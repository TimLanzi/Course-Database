//begin guarding header file
#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>
using namespace std;

//template declaration
template <typename T>

//declare node class
class node {

//delcare public variables/functions
public:
    T value;	//templated value variable
    node<T>* next;	//pointer to net node in list

	  //node constructor
    node(const T& item, node *prevNode=NULL) : value(item), next(NULL)
    {
		    //makes this the next node in the list
        if(prevNode != NULL)
        {
            prevNode->next = this;
        }
    }

	  //overloaded [] operator
    node<T>* operator [](const int i)
    {
        node<T>* ans = this;
        for (int n =0; n<i; n++)
        {
            ans = ans->next;
            if(ans == NULL)
                break;
        }

        return ans;
    }
};

//function to create new node
template <typename T>
node<T>* CreateNode(const T &value)
{
    return new node<T> (value);
}

//function to insert new node in linked list
template <typename T>
void InsertNode(node<T>* &front, const T &value )
{
    node<T>* newNode = CreateNode(value);

    // if the list is empty or if we are inserting before the front node
    if (front == NULL || newNode->value < front->value )
    {
        newNode->next = front;
        front = newNode;
    }
    else
    {
        //locate the node before the point of insertion
        node<T>* curr = front;
        while (curr->next!=NULL && curr->next->value < newNode->value)
        {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
}

//function for adding node to the back of the list (used for prereqs only)
template <typename T>
void AddNode(node<T>* &front, const T &value )
{
    node<T>* newNode = CreateNode(value);

    // if the list is empty or if we are inserting before the front node
    if (front == NULL )
    {
        newNode->next = front;
        front = newNode;
    }
    else
    {
        //locate the end node
        node<T>* curr = front;
        while (curr->next!=NULL)
        {
            curr = curr->next;
        }
        newNode->next = NULL;
        curr->next = newNode;
    }
}

//function for searching linked lists for specified values using basic linear search algorithm
template <typename T>
node<T>* SearchNode(node<T>* front, const string &value)
{
    node<T> *curr = front;

    while(curr != NULL)
    {
        if (curr->value == value)
        {
            break;
        }
        else
        {
            curr = curr->next;
        }
    }

    return curr;
}

//function for deleting a single node
template <typename T>
void DeleteNode(node<T>* &front, const string & value )
{
    node<T>  *curr = front, *prev = NULL;
    bool foundItem = false;

    //linear seach for desired node
    while (curr != NULL && !foundItem)
    {
        if (curr->value == value)
        {
            if (prev == NULL)
            {
                front = front->next;
            }
            else
            {
                prev->next = curr->next;
            }

            delete curr;	//delete node if found

            foundItem = true;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
}

//function for printing all course data for each course in the linked list
template <typename T>
void printList(node<T>* data)
{
    for(node<T> *curr = data; curr != NULL; curr = curr -> next)
    {
        cout << curr->value <<endl;
    }
}

#endif
