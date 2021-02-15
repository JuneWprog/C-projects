#include<stdio.h>
//output 172 AC
// number 0-256 and hex

int main()
{ 
  for(int i=0; i<=256;i++)
    printf("%3d%4X\n", i,i);
  return 0;
}
