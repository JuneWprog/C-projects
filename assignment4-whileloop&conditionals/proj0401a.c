#include <stdio.h>
//        J        74     0x4a
//output: char  asicii    hex 

int main()
{
  //PART A
  char myname[] = "Jun Wang";
  char *p = (char *) &myname;
  
  while(*p != '\0')
    {
      printf("%c\t%3d\t0x%02x\n", *p, *p, *p);
      p++;
    }
}


