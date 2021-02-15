#include<stdio.h>
char myname[]="Jun Wang";
char alphabet[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
extern void *__data_start;
extern void *_edata;
unsigned int *pbegin=(void * )&__data_start;
unsigned int *pend=(void * )&_edata;

int main (int argc, char* argv[])
{
  int i, j, myval;
  char character;
  while(pbegin<=pend)
    {
      printf("%p : 0x%08x ",pbegin,*pbegin);
      for(i=31;i>=0;i--)
	{
	  myval=((*pbegin)>>i)&1;
	  printf("%d", myval);
	  if((i%4)==0)
	    printf(" ");
	}
      for(j=24;j>=0;j-=8)
	{
	  character=(*pbegin>>j)&(0xff);
	  if (character<='Z'&& character>='A' ||character>='a' && character<='z')
	   printf("%c",character);
	} 
      
      pbegin++;
      printf("\n");
    }
  
  return 0;
   
  
   
}



















