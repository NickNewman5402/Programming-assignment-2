#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE  12

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

node* createNode(node* p_front){

  node* p_newNode = (node*)malloc(sizeof(node));
  p_newNode->p_next = NULL;
  
  return p_newNode;
}

customers* createCustomers(customers*);


customers* createCustomers(customers* p_customer){
    
    int m;
    scanf("%d", &m);
    p_customer = (customers*)malloc(sizeof(customers)*m);
      
      for(int j = 0; j < m; j++){
        scanf("%d", &p_customer[j].enterLineTime); 
        scanf("%d", &p_customer[j].lineNumber); 
        p_customer[j].p_name = (char*)malloc(sizeof(char)*15);
        scanf("%s", p_customer[j].p_name);
        /* if(strlen(p_customer[j].p_name) > 15)
        //   printf("Name is larger than 15 characters");

        // int l = 0;
        // while (p_customer[j].p_name[l] != '\n') {
        //     char ch = p_customer[i].p_name[l];
        //     putchar(toupper(ch));
        //     j++;
         }*/
        scanf("%d", &p_customer[j].numOfSmootihes);
      }
  
  return p_customer;
}

int main(void) {
  
  customers* customers; 
  int c; 
  scanf("%d", &c);

  for(int i =0; i < c; i++){
  
    customers = createCustomers(customers);

    // confirming customers are returning to main
    for(int i = 0; i < 5; i++){
      printf("\nCustomer [%d] entered line at time %d\n", i, customers[i].enterLineTime);
      printf("Customer [%d] entered line number %d\n", i, customers[i].lineNumber);
      printf("Customer [%d] Name is %s\n", i, customers[i].p_name);
      printf("Customer [%d] ordered %d number of smoothies\n\n", i, customers[i].numOfSmootihes);
    }// finish test
    
  }
  
  return 0;
}