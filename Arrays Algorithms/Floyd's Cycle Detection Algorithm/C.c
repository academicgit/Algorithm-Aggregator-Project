// Totoise & Hare Problem (Cycle Detection) Algorithm
#include <stdio.h>
#include <stdlib.h>

/*            _ _ _ _ _ _ 
 *           |           | Length of the loop => lambda
 *           |           |
 *           |           |
 *           |           |                       head
 *           ------------------------------------
 *                       <-------- mu ---------->
 *
 *
 *           If a loop exists, then there exists an i >= mu such that x(i) = x(i + k*lambda) where the argument to x() denotes the number
 *           of steps taken while traversing the list and k is any positive number . This situation is bound to occur in case a loop exists. 
 *           Now, let us consider an i >= mu which is a multiple of lambda ( length of the loop ). Such an will exist since starting from
 *           the head we will traverse the list in steps of one and i will eventually take every possible value starting from 1 as the we
 *           won't get out of the loop.So, at some point during our traversal , we'll have 
 *           
 *           i = (k')*lambda, k' > 0 , i >= mu                                          ----- (1)
 *
 *           But we also know that 
 *           x(i) = x(i + k*lambda) for i >= mu , k > 0                                 ----- (2)
 *           Let k = k', So we have
 *           x(i) = x(i + (k')*lambda)  
 *      ==>  x(i) = x(2i)                  ( Since i = (k')*lambda )                    ----- (3)
 *           So at some point during our traversal, a situation like (3) will definitely occur at some point in the loop, Since 
 *           condition (1) was assumed for a point within the loop.
 *	     
 *	     So, now comes the trick , if we take two pointers starting from the head ( hare, tortoise ) such that hare always traverses
 *	     twice as fast as the tortoise then the following relation always holds between the distances covered by them.
 *	     For every i steps taken by the tortoise, the hare would take 2*i steps. And this is don deliberately.
 *
 *	     When the tortoise will take steps equal to the value of 'i' in case (3) which it will take eventually since it is moving in
 *	     steps of one and will loop without stopping, we would have
 *	     x(i) = x(2i)  where i are the number of steps taken by the tortoise.
 *	     But notice that at this point of time, the number of steps taken by the hare would have been 2i which is precisely the R.H.S
 *	     of the above equation. Here i is some point within the loop as proved above in case (3) and this implies that the hare and the
 *	     tortoise at this time would point to the same node which is the eventual observation that would help us detect the loop. 
 *
 *	     We need to note that this won't occur, i.e the hare and the tortoise will never meet when the list has no loops since the hare
 *	     would eventually reach the end of the list which can be detected followed by the tortoise reaching the end as well.
 *
 *	     Once we find such a situation, we will make note of this 'i' i.e the number of steps taken by the tortoise upto this point, since
 *	     it would be a multiple of lambda ( length of the loop ).
 *
 *	     Now , we find the first element which gets repeated in the list or in other words the start point of the loop, so we get the value
 *	     of mu. Finally keeping one pointer at the start node of the loop just found , we increment another pointer starting at the same 
 *	     position until it meets the start poin of the loop, at this counting the number of steps taken for this gives the length of the loop.
 ** */

struct node
{
	int data;
	struct node* next;
};

struct node *head = NULL, *sentinel = NULL;
int flag = 0;

struct node* insert_node_last(struct node** head,struct node** sentinel,int data)
{
	int n,i = 0; /* n => node to which the new node's next will point to */
	struct node *temp,*new_node = (struct node*)malloc(sizeof (struct node));
	new_node->data = data;
	
	if ( *sentinel != NULL )
	{	
		(*sentinel)->next = new_node;
		
	}
	else
	{
		*head = new_node;
	}
	*sentinel = new_node;  
	
	while ( 1 )
	{
		temp = *head;
		printf("\nEnter the node to whom the next pointer of this node will point to (Enter -1 for NULL):\n");
		scanf("%d",&n);

		if ( n == -1 )
		{
			/* User does not want to create a cycle */
			new_node->next = NULL;
			break;
		}
		else
		{
			/* User wants to create a cycle */
			while ( i < n - 1 && temp != NULL )
			{	
				temp = temp->next; i++;
			}
			if ( i == n - 1 ) 
			{
				if ( temp != NULL )
				{	
					/* Cycle created */
					new_node->next = temp;
					flag = 1;
					break;
				}
				else
					printf("Such a node does not exist\n"); /*node number given just is one greater than the length of the list*/
					/* Cycle not created */

			}
			else
				printf("Such a node does not exist\n");
		}
	}
	temp = *head; i = 1;
	while ( temp != NULL && flag != 1 )
	{
		printf("(%d,%d)-->",i,temp->data);
		temp = temp->next; i++;
	}
return NULL;
}

struct node* inc_steps(struct node* pt,int steps)
{
	int i; struct node* temp = pt;
	for ( i = 0; i < steps ; i ++ )
		{
			temp = temp->next;
		}
	return temp;
}


int main()
{
	printf("\nEnter the nodes in the linked list\n");
	int data, nos, period, lambda = 1, mu = 1; char op = 'Y';
	while( ( op == 'Y' || op == 'y' ) && flag != 1 )
	{
		printf("\nEnter the data for the new node\n");
		scanf("%d",&data);
		insert_node_last(&head,&sentinel,data);
		if ( flag != 1 ) 
		{	printf("\nDo you want to insert more data ( Y or N )\n");
			scanf("%c",&op);
			scanf("%c",&op);
		}
	}

	struct node *hare, *tortoise;
	hare = ( tortoise = head ) ;
	
	//#TODO In case of No loops or 0 nodes => This shouldn't run .Error check for NULL pointer . May cause segmentation fault.
	tortoise = tortoise ->next;
	hare = hare->next->next;
	//#TODO In case of No loops or 0 nodes => This shouldn't run .Error check for NULL pointer . May cause segmentation fault.
	nos = 1;

	while ( hare != tortoise && hare != NULL )
	{
		/* They should meet at a point somewhere inside the loop 
		 * When they meet the nos shhould be a multiple of the length
		 * of the loop i.e nos = k*l where l is the length of the loop. */
		
		//#TODO In case of No loops or 0 nodes => This shouldn't run. Error check for NULL pointer . May cause segmentation fault.
		tortoise = tortoise->next;
		hare = hare->next->next;
		//#TODO In case of No loops or 0 nodes => This shouldn't run .Error check for NULL pointer . May cause segmentation fault.
		nos++;
	}

	if ( hare == NULL ) /* No loop exists in the linked list */
	{
		printf("\n :: No loop exists in the list :: \n");
		return 0;
	}
	
	if ( hare == tortoise ) /* A loop exists */
	{
		period = nos;
	}
	/* Now starting from the head of the list, we need to find the first element in the list which repeats itself
	 * i.e precisely the start node of the loop */
	//#TODO In case of No loops or 0 nodes => This shouldn't run. Error check for NULL pointer . May cause segmentation fault.
	tortoise = head;
	//#TODO In case of No loops or 0 nodes => This shouldn't run. Error check for NULL pointer . May cause segmentation fault.
	while ( tortoise != inc_steps(tortoise,period) )
	{
		tortoise = tortoise->next;
		mu++;
	}
        if ( tortoise == inc_steps(tortoise,period) )
		printf("\n :: The start node of the loop is at node no. %d :: \n",mu);
	/* Now we will find the length of the loop by keeping the tortoise fixed and moving the hair
	 * one step each until it circles around and meets the tortoise at the start node of the loop */
	
	//#TODO In case of No loops or 0 nodes => This shouldn't run. Error check for NULL pointer . May cause segmentation fault.
	hare = tortoise->next;
	//#TODO In case of No loops or 0 nodes => This shouldn't run. Error check for NULL pointer . May cause segmentation fault.
	
	while ( hare != tortoise )
	{
		hare = hare->next;
		lambda++;
	}
	if ( hare == tortoise )
	{
		printf("\n :: The length of the loop is %d :: \n ",lambda);
	}
	return 0;
}