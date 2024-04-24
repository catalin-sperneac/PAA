#include"GP.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int main(void)
{
    Graf G1;
    initializeGraph(&G1);
    Nod nod1={0,10};
    Nod nod2={1,20};
    Nod nod3={2,30};
    Nod nod4={3,40};
    Nod nod5={4,50};
    Nod nod6={5,60};
    Arc arc1={0,1,23};
    Arc arc2={0,2,54};
    Arc arc3={0,3,12};
    Arc arc4={0,4,29};
    Arc arc5={0,5,20};
    Arc arc6={1,2,15};
    Arc arc7={1,3,34};
    Arc arc8={1,4,33};
    Arc arc9={1,5,19};
    Arc arc10={2,3,43};
    Arc arc11={2,4,44};
    Arc arc12={2,5,50};
    Arc arc13={3,4,14};
    Arc arc14={3,5,24};
    Arc arc15={4,5,47};
    insertNode(&G1,nod1);
    insertNode(&G1,nod2);
    insertNode(&G1,nod3);
    insertNode(&G1,nod4);
    insertNode(&G1,nod5);
    insertNode(&G1,nod6);
    insertArc(&G1,arc1);
    insertArc(&G1,arc2);
    insertArc(&G1,arc3);
    insertArc(&G1,arc4);
    insertArc(&G1,arc5);
    insertArc(&G1,arc6);
    insertArc(&G1,arc7);
    insertArc(&G1,arc8);
    insertArc(&G1,arc9);
    insertArc(&G1,arc10);
    insertArc(&G1,arc11);
    insertArc(&G1,arc12);
    insertArc(&G1,arc13);
    insertArc(&G1,arc14);
    insertArc(&G1,arc15);
    printf("greutatea totala a arcelor este %d\n",KruskalFaraSortare(&G1));
    printf("greutatea totala a arcelor este %d\n",KruskalCuSortare(&G1));
    return 0;
}