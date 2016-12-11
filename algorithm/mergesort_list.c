#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int val;
	struct node* next;
} node;

// utility
void split(node* head, node** l, node** r) {
	node* fast = head->next, *slow = head;
	// assume fast have at least two element
	while (fast != NULL) {
		fast = fast->next;
		if (fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*l = head;
	*r = slow->next;
	slow->next = NULL;
}

// merge two list
node* merge(node* l, node* r) {
	// assume both not null 
	node* result;
	node** p = &result;
	// assume l and r not null
	while (l != NULL && r != NULL) {
		if (l->val <= r->val) {
			*p = l;
			p = &l->next;
			l = l->next;
		} else {
			*p = r;
			p = &r->next;
			r = r->next;
		}
	}
	if (l != NULL) {
		*p = l;
	}
	if (r != NULL) {
		*p = r;
	}
	return result;
}

node* merge_sort(node* n) {

	node* l, *r;
	// base case
	// already check for merge and split function
	if (n==NULL || n->next == NULL)
		return n;
	// split n
	split(n, &l, &r);

	l = merge_sort(l);
	r = merge_sort(r);
	
	return merge(l, r);

}


/* Function to print nodes in a given linked list */
void printList(struct node *node)
{
  while(node!=NULL)
  {
   printf("%d ", node->val);
   node = node->next;
  }
  printf("\n");
}
 
/* Function to insert a node at the beginging of the linked list */
void push(struct node** head_ref, int new_data)
{
  /* allocate node */
  struct node* new_node =
            (struct node*) malloc(sizeof(struct node));
  
  /* put in the data  */
  new_node->val  = new_data;
  
  /* link the old list off the new node */
  new_node->next = (*head_ref);    
  
  /* move the head to point to the new node */
  (*head_ref)    = new_node;
} 
  
/* Drier program to test above functions*/
int main()
{

  struct node* a = NULL;
  
  /* Let us create a unsorted linked lists to test the functions
   Created lists shall be a: 2->3->20->5->10->15 */
  push(&a, 15);
  push(&a, 10);
  push(&a, 5); 
  push(&a, 20);
  push(&a, 3);
  push(&a, 2); 
  
  /* Sort the above created Linked List */
  a = merge_sort(a);
  
  printf("Sorted Linked List is: \n");
  printList(a);           
  
  return 0;
}