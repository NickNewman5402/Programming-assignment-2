/*
Nick Newman
6/16/24
5295926
Computer Science 1 - Programming assignment 2
Due: 6/16/24
Dr. Tanvir Ahmed Summer 2024
*/

#include <stdio.h>
#include <stdlib.h>


#define MAX_SIZE  12
#define EMPTY -1
#define MAX_SMOOTHIES 100
#define MAX_TIME 10000000000

/*------------STRUCTURE DEFINES--------------*/
typedef struct queue {
	struct node* p_front;
	struct node* p_back;
}queue;

typedef struct customers {
	char* p_name;
	int numOfSmoothies;
	int lineNumber;
	int enterLineTime;
}customers;

typedef struct node {
	customers* p_customer;
	struct node* p_next;
}node;

/*------------FUNCTION SIGNATURES------------*/
void init(queue* qPtr);
void displayQueue(queue* myQ);
int enqueue(queue* qPtr, customers* cPtr);
int empty(queue* qPtr);
int peek(queue* qPtr);
int findNextCustomer(queue*, int*);
customers* dequeue(queue* qPtr);
customers* createCustomers(customers* , int*);

/*------------QUEUE FUNCTIONS----------------*/
void init(queue* qPtr) {
	qPtr->p_front = NULL;
	qPtr->p_back = NULL;
}

int enqueue(queue* qPtr, customers* cPtr) {

	struct node* p_temp = malloc(sizeof(struct node));

	if (p_temp == NULL) {
		return 0;
	}

	p_temp->p_customer = cPtr; 
	p_temp->p_next = NULL;

	if (qPtr->p_front == NULL) { // if I have no one in line make this customer first in line
		qPtr->p_front = p_temp;
		qPtr->p_back = p_temp;

		return 1;
	}

		//if front is not null (I have someone in line) put this customer behind the last person
	qPtr->p_back->p_next = p_temp;
	qPtr->p_back = p_temp;

	return 1;

}

customers* dequeue(queue* qPtr) {

	if (empty(qPtr)) {
		return EMPTY;
	}

	struct node* p_temp = qPtr->p_front;
	qPtr->p_front = qPtr->p_front->p_next;
	customers* retval = p_temp->p_customer; // data became p_customer->lineNumber to satify the retVal
	free(p_temp);

	/*This is written because of the above 5 lines*/
	if (empty(qPtr))
		qPtr->p_back = NULL;
	return retval;
}

int empty(queue* qPtr) {
	if (!qPtr) {
		return EMPTY;
	}
	return 0;
}

int peek(queue* qPtr) {
	if (!qPtr) {
		return EMPTY;
	}
	return qPtr->p_front->p_customer->lineNumber;
}

void displayQueue(queue* myQ) {
	struct node *t = myQ->p_front;
	while (t)
	{
		printf("%s ", t->p_customer->p_name);
		t = t->p_next;
	}
}


/*------------CUSTOMER FUCTIONS---------------*/

customers* createCustomers(customers* p_customer, int* p_m) {

	//int m;
	scanf("%d", p_m);

	p_customer = (customers*)malloc(sizeof(customers)*(*p_m));

	for (int j = 0; j < (*p_m); j++) {
		scanf("%d", &p_customer[j].enterLineTime);
		scanf("%d", &p_customer[j].lineNumber);
		p_customer[j].p_name = (char*)malloc(sizeof(char) * 15);
		scanf("%s", p_customer[j].p_name);
		scanf("%d", &p_customer[j].numOfSmoothies);
	}

	return p_customer;
}

int findNextCustomer(queue* p_q, int* p_cT) {
	int sC = 101;
	int nC = -1;

		// finding the customer who has been in line less than the current time and has the least amount of smoothies
	for (int k = 0; k < MAX_SIZE; k++) {
		if ((p_q[k].p_front != NULL) && (p_q[k].p_front->p_customer->enterLineTime < *p_cT) && (p_q[k].p_front->p_customer->numOfSmoothies < sC)) {
			sC = p_q[k].p_front->p_customer->numOfSmoothies;
			nC = k;

		}
	}// end first confition for


	// out of the customers who have been in line longer than the current time. I need to find the one that arrived first (best time... lowest time number?)
	if (nC == -1) {

		int lowestTime = 10000000001;

				// go through all the queues
		for (int k = 0; k < MAX_SIZE; k++) {
						// finding the customer that has been in line greater than current time but less than all others in the front
			if (p_q[k].p_front != NULL && p_q[k].p_front->p_customer->enterLineTime <= lowestTime) {
				lowestTime = p_q[k].p_front->p_customer->enterLineTime;
				nC = k;
			}

		}// End 2nd condition for
	}// end check of if I found a customer already
	return nC; // returning the index for the next customer
}// End queue for 



/*------------MAIN FUNCTION------------------*/
int main(void) {

	//atexit(report_mem_leak); //for memory leak detector.

	customers* customerList;
	customerList = NULL;

	int c;
	int choosenIndex = 0;
	int smoothieCount = MAX_SMOOTHIES;
	int nextCustomer = 0;
	int m = 0;


	queue q[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++)
		init(&q[i]);

	scanf("%d", &c);

	for (int i = 0; i < c; i++) {// cycle through test cases 

		customerList = createCustomers(customerList, &m);// creating customers

		long long int currentTime = 0;

		for (int j = 0; j < m; j++) {// putting customers in queues
			enqueue(&q[(customerList[j].lineNumber) - 1], &customerList[j]);
		}// finish queing customers


		// FINDING A SERVICABLE CUSTOMER
		for(int k = 0; k < m; k++){
		nextCustomer = findNextCustomer(q, &currentTime);

		if (q[nextCustomer].p_front->p_customer->enterLineTime > currentTime) {
			currentTime = q[nextCustomer].p_front->p_customer->enterLineTime;
		}
			currentTime += 30 + (q[nextCustomer].p_front->p_customer->numOfSmoothies * 5);

			printf("At time %lld, %s left the counter from line %d.\n", currentTime, q[nextCustomer].p_front->p_customer->p_name, nextCustomer + 1);
			customers* temp = dequeue(&q[nextCustomer]);
			free(temp->p_name);
		}

		free(customerList);

	}// End for test case loop



	return 0;
}
