#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE  12
#define EMPTY -1

/*------------STRUCTURE DEFINES--------------*/
typedef struct queue {
    struct node* p_front;
    struct node* p_back;
}queue;

typedef struct customers{
  char* p_name;
  int numOfSmootihes;
  int lineNumber;
  int enterLineTime;
}customers;

typedef struct node{
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
customers* createCustomers(customers*, int m);

/*------------QUEUE FUNCTIONS----------------*/
void init(queue* qPtr) {
    qPtr->p_front = NULL;
    qPtr->p_back = NULL;
}

int enqueue(queue* qPtr, customers* cPtr) {

    struct node* p_temp = malloc(sizeof(struct node));
    
    if(p_temp == NULL){
        return 0; 
    }


    p_temp->p_customer = cPtr; // data became p_customer // second note... p_customer needs to equal what? I think when i enqueue I need to store customer[i] data? I have put line number to satisfy equaling x.// I have updated this to p_temp->p_customer = cPtr; I believe this is putting customer[i] data into p_customer in p_temp wich is a node. 
    p_temp->p_next = NULL;

    if(qPtr->p_back == NULL){ // I need to do something about qPtr-<p_back for a 2nd or more entry
        qPtr->p_front = p_temp;
        qPtr->p_back = p_temp;

        return 1; 
    }

    qPtr->p_back->p_next = p_temp;
    qPtr->p_back = p_temp;

    return 1; 

}

int dequeue(queue* qPtr) {

    if(empty(qPtr)){
        return EMPTY;
    }

    struct node* p_temp = qPtr->p_front;
    qPtr->p_front = qPtr->p_front->p_next;
    int retval = p_temp->p_customer->lineNumber; // data became p_customer->lineNumber to satify the retVal
    free(p_temp);

    /*This is written because of the above 5 lines*/
    if(empty(qPtr))
        qPtr->p_back = NULL;
    return retval;
}

int empty(queue* qPtr) {
    if(!qPtr){
        return EMPTY;
    }
}

int peek(queue* qPtr) {
    if(!qPtr){
        return EMPTY;
    }
    return qPtr->p_front->p_customer->lineNumber;
}

void displayQueue(queue* myQ) {
  struct node *t =  myQ->p_front;
 while(t){
    //for(int i = 0; i < MAX_SIZE; i++){
    printf("%s ", t/*[i]*/->p_customer->p_name);
    t = t/*[i]*/->p_next;
   // }
  }
}


/*------------CUSTOMER FUCTIONS---------------*/
node* createCustomerNode(node* p_front){

  node* p_newNode = (node*)malloc(sizeof(node));
  p_newNode->p_next = NULL;
  
  return p_newNode;
}

customers* createCustomers(customers* p_customer, int m){
    
    p_customer = (customers*)malloc(sizeof(customers)*m);
      
      for(int i = 0; i < m; i++){
          p_customer[i].enterLineTime = EMPTY;
        scanf("%d", &p_customer[i].enterLineTime); 
        scanf("%d", &p_customer[i].lineNumber); 
        p_customer[i].p_name = (char*)malloc(sizeof(char)*15);
        scanf("%s", p_customer[i].p_name);
        /* if(strlen(p_customer[j].p_name) > 15)
        //   printf("Name is larger than 15 characters");

        // int l = 0;
        // while (p_customer[j].p_name[l] != '\n') {
        //     char ch = p_customer[i].p_name[l];
        //     putchar(toupper(ch));
        //     j++;
         }*/
        scanf("%d", &p_customer[i].numOfSmootihes);
      }
  
  return p_customer;
}


/*------------MAIN FUNCTION------------------*/
int main(void) {
  
  customers* customers = NULL; 
  
  int c; 
  scanf("%d", &c);
  int m;
  scanf("%d", &m);

  queue q[MAX_SIZE];
    for(int i = 0; i < MAX_SIZE; i++){
        init(&q[i]);
    }


  for(int i =0; i < c; i++){
  
    customers = createCustomers(customers, m);
  

/*------------DEBUGGING START----------------*/    
    // confirming customers are returning to main
    for(int j = 0; j < m; j++){
      enqueue(&q[(customers[j].lineNumber)-1], &customers[j]);  
      // printf("\nCustomer [%d] entered line at time %d\n", i, customers[i].enterLineTime);
      // printf("Customer [%d] entered line number %d\n", i, customers[i].lineNumber);
      // printf("Customer [%d] Name is %s\n", i, customers[i].p_name);
      // printf("Customer [%d] ordered %d number of smoothies\n\n", i, customers[i].numOfSmootihes);
    }// finish test
/*------------DEBUGGING END------------------*/
      
      for(int k = 0; k < m; k++)
        displayQueue(&q[k]);

  }
  
  return 0;
}