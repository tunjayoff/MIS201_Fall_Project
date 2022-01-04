/* A website web search simulation for MIS201_FALL_PROJECT */

#include <windows.h>     //For colors
#include <iostream>
using namespace std;

struct node
{
    string website;
    node* prev;
    node* next;
};

node *current = new node;

void Color(int color);
void push(node** head_ref, string url);
void append(node** head_ref, string url);
void deleteNode(node** head_ref, node* del);
void deleteList(node** head_ref);
void insertAfter(node* prev_node, string url);
void history(node* head);
node* search(node* head, string website_name);

int main(void)
{
    
    /* Start with the empty list */ 
    node* head = NULL; 

    // Let's create a search history with different functions first 
    append(&head, "www.google.com");   
    push(&head, "www.yandex.com"); 
    push(&head, "www.first.com"); 
    append(&head, "www.coursera.org"); 
    insertAfter(head->next, "www.edx.org");
    insertAfter(head->next->next, "www.ibm.com");
    append(&head, "www.last.com");
    Color(64);
    cout<<"     +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+     \n"<<
          "      W   E   B   S   I   T   E   R   A   T   O   R      \n"<<
          "     +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+     \n";
    Color(10);
    cout << "\n---------------------------OPTIONS------------------------\n"<<
            "| 1.) Press 1 to go previus website                      |\n"<<
            "| 2.) Press 2 to go new website                          |\n"<< 
            "| 3.) Press 3 to go next website                         |\n"<<
            "| 4.) Press 4 for history                                |\n"<<
            "| 5.) Press 5 to delete a specific website in history    |\n"<<
            "| 6.) Press 6 to delete whole history                    |\n"<<
            "| 7.) Press 7 to exit                                    |\n"<<
            "---------------------------OPTIONS------------------------\n";
    Color(7);
    current = head;
    // And then write an interactive user program
    char controller;
    do
    {
        string url;
        Color(1);
        cout << "Choice: ";
        Color(4);
        cin >> controller;
        Color(7);
        switch (controller)
        {
            case '1':
            {
                if (current == NULL)
                {
                    Color(4);
                    cout << "History is empty!\n" << endl;
                    Color(7);
                }
                else if(current->prev == NULL)
                {
                    Color(4);
                    cout << "There is no previous website!\n\n";
                    Color(7);
                }
                else
                {
                    cout << current->prev->website << "\n\n";
                    current = current -> prev;
                }
                break;
            }

            case '2':
            {
                cout << "Enter the website url: ";
                cin >> url;
                if (search(head, url) == NULL)
                {
                    append(&head, url);
                    current = search(head, url);
                    Color(9);
                    cout << "Succesfully added. Now you're in " << url << "\n\n";
                    Color(7);
                }
                else
                {
                    current = search(head, url);
                    Color(9);
                    cout << "Already in history. Now you're in " << url << "\n\n";
                    Color(7);
                }

                if(current == NULL)
                    current = head;
                break;
            }

            case '3':
            {
                if (current == NULL)
                {
                    Color(4);
                    cout << "History is empty!\n" << endl;
                    Color(7);
                }
                else if(current->next == NULL)
                {
                    Color(4);
                    cout << "There is no next website!\n" << endl;
                    Color(7);
                }
                else
                {
                    cout << current->next->website << "\n\n";
                    current = current -> next;
                }
                break;
            }

            case '5':
            {
                string deleted_website;
                cout << "Please enter the full site name: ";
                cin >> deleted_website;
                if(search(head, deleted_website) != NULL)
                {
                    deleteNode(&head, search(head, deleted_website));
                    Color(9);
                    cout << deleted_website << " was succesfully deleted\n\n";
                    Color(7);
                }
                else
                {
                    Color(4);
                    cout << "Website couldn't found please enter a valid adress!" << "\n\n";
                    Color(7);
                }
                
                
                break;
            }

            case '4':
            {
                cout << "------- History --------" << endl;
                history(head);
                cout << "\n";
                break;
            }
            
            case '6':
            {
                deleteList(&head);
                current = head;
                break;
            }

            default:
            {
                if (controller != '7')
                {
                    cout << "\nPlease enter a valid option!" << endl;
                    break;
                }
                else
                {
                    break;
                }
            }
        }
    } while (controller != '7');

    return 0;
}

/* Create a function which add a string before the first node */
void push(node **head_ref, string url)
{
    // 1. Allocate space for new node
    node *new_node = new node;

    // 2. Add a site address in node
    new_node->website = url;

    // 3. Make next of new node as head and prev of the new node as null */
    new_node->next = *head_ref;
    new_node->prev = NULL;

    // 4. Change prev of the head node as new node
    if ((*head_ref) != NULL)
    {
        (*head_ref)->prev = new_node;
    }
    
    // 5. move the head to point to the new node
    *head_ref = new_node;
}

/* Given a node prev_node, insert a new node after the given prev_node */
void insertAfter(node* prev_node, string url)
{
    // 1. Check if the given prev_node is NULL 
    if (prev_node == NULL) 
    { 
        cout<<"The given previous node cannot be NULL"; 
        return; 
    }

    // 2. Allocate new node
    node* new_node = new node;

    // 3. Put in the data
    new_node->website = url;

    // 4. Make next of new node as next of prev_node, and prev of new_node as prev_node
    // and more
    new_node->next = prev_node->next;
    new_node->prev = prev_node->next->prev;
    prev_node->next->prev = new_node;
    prev_node -> next = new_node;
}

/* Adding a new node to the end */
void append(node** head_ref, string url)
{
    // 1. Allocate space new node
    node* new_node = new node;
    node* last = *head_ref;

    // 2. Put in the data
    new_node->website = url;

    // 3. This new node will be the last node, so make the next of new_node as NULL
    new_node->next = NULL;
    new_node->prev = NULL;

    // 4. Check linked list. If it is empty then make the new_node as head
    if(*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    // 5. Else traverse till the last node
    while (last->next != NULL)
    {
        last = last->next;
    }

    // 6. Change the next of last node, now it will point our new_node
    last->next = new_node;

    // 7. Make the last node as prev node of new_node
    new_node->prev = last;

    return;
}

/* Print the whole history */
void history(node* head)
{
    node* temp = new node();
    temp = head;
    int count = 1;
    while(temp != NULL)
    {
        cout << count << ".) " << temp->website << endl;
        temp = temp->next;
        count++;
    }
}

/* Search and return the result's node.
   Will used with deleteNode */
node* search(node* head, string website_name)
{
    node *temp = new node();
    temp = head;
    while(temp != NULL)
    {
        if(temp -> website == website_name)
            return temp;
        else
            temp = temp -> next;
    }
    return NULL;
}

// Delete a given node. Designed for using with search and delete a website.
// Simple using: deleteNode(head, search(head, "www.example.com"));
void deleteNode(node** head_ref, node* del)
{
    /* base case */
    if (*head_ref == NULL || del == NULL)
        return;
 
    /* If node to be deleted is head node */
    else if (*head_ref == del){
        *head_ref = del->next;
        del->next->prev = NULL;
        free(del);
    }
    /* If node to be deleted is not
       the last node */
    else if (del->next != NULL){
        del->next->prev = del->prev;
        del->prev->next = del->next;
        free(del);
    }
    /* If node to be deleted is the 
       last node */
    else if (del->next == NULL){
        del->prev->next = NULL;
        free(del);
    }
}

/* Delete whole list. Will used for deleting all history. */
void deleteList(node** head_ref)
{
 
    /* deref head_ref to get the real head */
    node* current = *head_ref;
    node* next = NULL;
 
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
 
    /* deref head_ref to affect the real head back
        in the caller. */
    *head_ref = NULL;
    Color(4);
    cout << "History was deleted\n\n";
    Color(7);
}

//For colors
void Color(int color)
{
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
