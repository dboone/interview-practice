#include <iostream>

struct Node {
	int data;
	Node* next;
};

void printList( Node* head )
{
	Node* curr = head;
	while(curr)
	{
		std::cout << curr->data << " ";
		curr = curr->next;
	}
	std::cout << std::endl;
}

void append(Node** head, Node* node)
{
	Node* curr = *head;
	while( curr->next )
	{
		curr = curr->next;
	}

	curr->next = node;
	node->next = NULL;
}

Node* merge(Node** left, Node** right)
{
    if (!*left && !*right)
    {
        return NULL;
    }

    Node* curr = NULL;

    if (*left && *right)
    {
        if ((*left)->data <= (*right)->data)
        {
            curr = *left;
            *left = (*left)->next;
        }
        else
        {
            curr = *right;
            *right = (*right)->next;
        }
    }

    Node* head = curr;

    while(*left && *right)
    {
        if ((*left)->data <= (*right)->data)
        {
            curr->next = *left;
            *left = (*left)->next;
        }
        else
        {
            curr->next = *right;
            *right = (*right)->next;
        }

        curr = curr->next;
    }

    if (*left)
    {
        curr->next = *left;
    }
    else
    {
        curr->next = *right;
    }

    return head;
}


Node* mergeRef(Node*& left, Node*& right)
{
    if (!left && !right)
        return NULL;
    else if (left && !right)
        return left;
    else if (!left && right)
        return right;

    Node* curr = NULL;

    if (left->data <= right->data)
    {
        curr = left;
        left = left->next;
    }
    else
    {
        curr = right;
        right = right->next;
    }

    Node* head = curr;

    while(left && right)
    {
        if (left->data <= right->data)
        {
            curr->next = left;
            left = left->next;
        }
        else
        {
            curr->next = right;
            right = right->next;
        }

        curr = curr->next;
    }

    curr->next = (left) ? left : right;
    return head;
}

Node* mergeRef2(Node*& left, Node*& right)
{
    if (!left && !right)
        return NULL;
    
    Node dummy = Node();
    Node* dummyHead = &Node(); dummyHead->data = -1;
    Node* curr = dummyHead;

    while(left && right)
    {
        if (left->data <= right->data)
        {
            curr->next = left;
            left = left->next;
        }
        else
        {
            curr->next = right;
            right = right->next;
        }

        curr = curr->next;
    }

    curr->next = (left) ? left : right;
    return dummyHead->next;
}

void reverse_r(Node*& head, Node*& curr, Node*& newHead)
{
    if (!head)
        return;

    if (!head->next)
    {
        newHead = head;
        curr = head;
        return;
    }

    reverse_r(head->next, curr, newHead);
    curr->next = head;
    curr = curr->next;
    head->next = NULL;
}

Node* reverse(Node*& head)
{
    Node rev, c;
    Node* revHead = &rev;
    Node* curr = &c;
    reverse_r(head, curr, revHead);

    return revHead;
}

Node* simple_reverse(Node*& head)
{
    Node *prev = NULL, *curr = head;

    while (curr)
    {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;        
    }
    return prev;
}

int main(int argc, char* argv[])
{
    Node h1 = Node();
	Node* head1 = &h1;
	head1->data = 0;
	head1->next = NULL;

    Node h2 = Node();
	Node* head2 = &h2;
	head2->data = 1;
	head2->next = NULL;

	Node n1;
	n1.data = 2;
	append(&head1, &n1);

	Node n2;
	n2.data = 13;
	append(&head1, &n2); 

	Node m1;
	m1.data = 7;
	append(&head2, &m1);

	printList(head1);
	printList(head2);

	//Node* m = merge(&head1, &head2);
    //Node* mRef = mergeRef2(head1, head2);

    //printList(mRef);

    //Node* rev = simple_reverse(mRef);

    //printList(rev);

	return 0;
}