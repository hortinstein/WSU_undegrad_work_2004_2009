#include "local.h"
#include <stdlib.h> 

typedef struct AELNode{
    int x;
    int y;
    struct AELNode *next;
} Node;

Node *addAEL(Node **p, int x, int y);
void sort(Node *n);
void print(Node *n);
Node* addEdge(int Ax, int Ay, int Bx, int By);
/* fillTri -- fill in a triangle (needs work!) */

void fillTri(int p[N_VTX][2]) {
    int i=0,i2=0,lowx,highx;  
    Node* Heade1 = NULL;
    Node* Heade2 = NULL;
    Node* Heade3 = NULL;
    Node* temp = NULL;
    Node* EL = NULL;    
    //seperated these due to unexplainable seg faults when passing in head
    Heade1 = addEdge(p[0][0],p[0][1],p[1][0],p[1][1]);   
    Heade2 = addEdge(p[2][0],p[2][1],p[1][0],p[1][1]);
    Heade3 =addEdge(p[2][0],p[2][1],p[0][0],p[0][1]);
    
    EL = Heade1;
    temp = EL;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = Heade2;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = Heade3;
    sort(EL);    
    while (EL->next != NULL)
        {
            printf("Y IS %d \n",EL->y);
            lowx = EL->x;
            highx = EL->x;
            while (EL->next->y == EL->y && EL->next != NULL)
            {
                if (EL->next->x < lowx)
                    lowx = EL->next->x;
                if (EL->next->x > highx)
                    highx = EL->next->x;
                EL = EL->next;
                if (EL->next == NULL)
                    break;
            }
            printf("omg5\n");
            
            printf("lowx %d highx %d\n",lowx,highx);            
            for (;lowx < highx;lowx++)
            {
                 setCell(lowx,EL->y,.4,.7,1);
            }
            if (EL->next != NULL)
                EL = EL->next;

        }
   
}

Node *addAEL(Node **p, int x, int y)
{
    //loosly based on wikipedia's linked list implementation
    Node *n = (Node *)malloc(sizeof(Node));
    n->next = *p; 
    *p = n; 
    n->x = x;
    n->y = y;
    return *p;
}
void sort(Node *list)
{ 
  //based on algorithm...modified for this project http://www.openasthra.com/c-tidbits/sorting-a-linked-list-with-bubble-sort/
  Node *lst, *tmp = list, *prev, *potentialprev = list;
  int idx, idx2, n = 0;
  for (;tmp->next; tmp=tmp->next)
  {
    n++;
  }
  for (idx=0; idx<n-1; idx++) 
  {
    for (idx2=0,lst=list; 
         lst && lst->next && (idx2<=n-1-idx);
         idx2++)
    {
      if (!idx2)
      {
        prev = lst;
      }
      if (lst->next->y < lst->y) 
      {  
        tmp = (lst->next?lst->next->next:0);
 
        if (!idx2 && (prev == list))
        {
          list = lst->next;
        }
        potentialprev = lst->next;
        prev->next = lst->next;
        lst->next->next = lst;
        lst->next = tmp;
        prev = potentialprev;
      }
      else
      {
        lst = lst->next;
        if(idx2)
        {
          prev = prev->next;
        }
      }     
    } 
  }
  return list;
} 

void print(Node *n)
{
    Node *counter=n;
    int count = 0,i = 0,i2 =0;
    while (counter->next != NULL){
        printf ("%d %d\n",counter->x, counter->y);
        counter = counter->next;
    }
    printf ("%d %d\n",counter->x, counter->y);   
}
Node* addEdge(int Ax, int Ay, int Bx, int By)
{    
    Node* Head = NULL;
       int yi=Ay,yf=By,xi=Ax,xf=Bx,temp,x,y;
    double delta = 0,ynext = -1,error = 0,dx,dy;
    if ( abs(By-Ay) > abs(Bx-Ax))
    {
        xi = Ay;//making swaps so the algorithm can run a 
        yi = Ax;
        xf = By;
        yf = Bx;
    }
    if (xi > xf)
    {
        temp = xi;//making swaps so the algorithm can run a 
        xi = xf;
        xf = temp;        
        temp = yi;
        yi = yf;
        yf = temp;
    }
    dy = (abs(yf - yi)) ;
    dx = (xf - xi);
    delta = dy/dx;
    if (yi < yf)
    {
        ynext = 1;
    }
    y = yi;
    for (x = xi; x <= xf; x++) {
        if (abs(By-Ay) > abs(Bx-Ax)) 
        {        
            addAEL(&Head,y, x); 
        }
        else 
        {
            addAEL(&Head,x, y);
        }
        error+=delta;
        if (error >= .5){
            y+=ynext;
            error--;
        }
    }
    return Head;
}
