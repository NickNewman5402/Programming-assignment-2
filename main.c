/*
Nick Newman
6/14/24
5295926
Computer Science 1 - Programming assignment 2
Due: 6/16/24
Dr. Tanvir Ahmed Summer 2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

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
int enqueue(queue* qPtr, customers* cPtr);
int dequeue(queue* qPtr);
int empty(queue* qPtr);
int peak(queue* qPtr);
int front(queue* qPtr);
void displayQueue(queue* myQ);
customers* createCustomers(customers*, int*);

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

		//init(qPtr);

	p_temp->p_customer = cPtr; // data became p_customer // second note... p_customer needs to equal what? I think when i enqueue I need to store customer[i] data? I have put line number to satisfy equaling x.// I have updated this to p_temp->p_customer = cPtr; I believe this is putting customer[i] data into p_customer in p_temp wich is a node. 
	p_temp->p_next = NULL;

	if (qPtr->p_back == NULL) { // I need to do something about qPtr->p_back for a 2nd or more entry
		qPtr->p_front = p_temp;
		qPtr->p_back = p_temp;

		return 1;
	}

	qPtr->p_back->p_next = p_temp;
	qPtr->p_back = p_temp;

	return 1;

}

int dequeue(queue* qPtr) {

	if (empty(qPtr)) {
		return EMPTY;
	}

	struct node* p_temp = qPtr->p_front;
	qPtr->p_front = qPtr->p_front->p_next;
	int retval = p_temp->p_customer->lineNumber; // data became p_customer->lineNumber to satify the retVal
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
node* createCustomerNode(node* p_front) {

	node* p_newNode = (node*)malloc(sizeof(node));
	p_newNode->p_next = NULL;

	return p_newNode;
}

customers* createCustomers(customers* p_customer, int* p_m) {

	//int m;
	scanf("%d", p_m);

	p_customer = (customers*)malloc(sizeof(customers)*(*p_m));

	for (int j = 0; j < (*p_m); j++) {
		scanf("%d", &p_customer[j].enterLineTime);
		scanf("%d", &p_customer[j].lineNumber);
		p_customer[j].p_name = (char*)malloc(sizeof(char) * 15);
		scanf("%s", p_customer[j].p_name);
		// if(strlen(p_customer[j].p_name) > 15)
		//   printf("Name is larger than 15 characters");

		char ch;
		int l = 0;
		do {
			ch = p_customer[j].p_name[l];
			if (ch != '\0') {
				p_customer[j].p_name[l] = toupper(ch);
				//putchar(p_customer[j].p_name[l]);
			}
			l++;
		} while (ch != '\0');
		scanf("%d", &p_customer[j].numOfSmoothies);
	}

	return p_customer;
}


/*------------MAIN FUNCTION------------------*/
int main(void) {

	customers* customers;
	customers = NULL;
	int c;
	scanf("%d", &c);
	long long int currentTime = llround(pow(10, 9));
	int nextCustomer = 0;
	int m = 0;
	//int* p_m = &m;


	queue q[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++)
		init(&q[i]);

	for (int i = 0; i < c; i++) {

		customers = createCustomers(customers, &m);


		/*------------DEBUGGING START----------------*/
			// confirming customers are returning to main
		for (int j = 0; j < m; j++) {
			enqueue(&q[(customers[j].lineNumber) - 1], &customers[j]);
			// printf("\nCustomer [%d] entered line at time %d\n", i, customers[i].enterLineTime);
			// printf("Customer [%d] entered line number %d\n", i, customers[i].lineNumber);
			// printf("Customer [%d] Name is %s\n", i, customers[i].p_name);
			// printf("Customer [%d] ordered %d number of smoothies\n\n", i, customers[i].numOfSmootihes);
		}// finish test
	/*------------DEBUGGING END------------------*/

		/*
		for (int k = 0; k < MAX_SIZE; k++) {
			printf("Queue line %d: ", k + 1);
			if (q[k].p_front == NULL) {
				printf("EMPTY");
			}
			displayQueue(&q[k]);
			printf("\n");
		}//*/

		int k = 0;
		int* p_k = &k;

		while (m > 0) {// while I still have customers
			for (*p_k; *p_k < MAX_SIZE; (*p_k)++) {// itterate through each queue
				if (q[*p_k].p_front != NULL && q[*p_k].p_front->p_customer->enterLineTime <= currentTime) {// find my least time of all front customer in all queues
					currentTime = q[*p_k].p_front->p_customer->enterLineTime;
					nextCustomer = *p_k;
				}
			}
			currentTime = q[nextCustomer].p_front->p_customer->enterLineTime + (30 + (q[nextCustomer].p_front->p_customer->numOfSmoothies * 5));
			printf("At time %lld, %s left the counter from line %d\n", currentTime, q[nextCustomer].p_front->p_customer->p_name, nextCustomer+1);
			dequeue(&q[nextCustomer]);
			*p_k = 0;
			m--;
		}







		/* I am not sure why this isnt working. This was not saved in the latest commit
		for (int i = 0; i < sizeof(customers) + 1; i++) {
			free(customers[i].p_name);
			free(&customers[i]);
		}
		//free(p_temp);
			//*/

	}// End for test case loop



	return 0;
}
