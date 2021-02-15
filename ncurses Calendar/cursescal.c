#include<ncurses.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define DAY_WIDTH 11 //width of the day box
#define DAY_HEIGHT 4 //height of the day box
#define COL0 1      //left edge of Monday boxes
#define ROW0 3     // top edge of the first drawn week boxes

int max_width,max_height;

void print_dashes(int row, int col,int height, int width)
{
  int i;
  move (row,col);
  printw("+");
  for(i=1;i<width;i++)
    printw("-");
  printw("+");
  
  move (row+height,col);
  printw("+");
  for(i=1;i<width;i++)
    printw("-");
  printw("+");  
}
  
void print_bars(int row, int col, int height,int width)
{
  int i;
  for(i=1;i<height;i++)
    {
      move(row+i,col);
      printw("|");
      move(row+i,col+width);
	printw("|");
     }
}

void print_m_day(int row, int col, int m_day)
{
  move(row+DAY_HEIGHT/2,col+DAY_WIDTH/2);
  printw("%2d",m_day);
}
void draw_box(int row, int col, int height, int width, int mday) 
{
  
  print_dashes(row,col,height,width);
  print_bars(row,col,height,width);
  print_m_day(row,col,mday);
}
// find the firstday of the month,working, used too many functions
/*int firstday(struct tm *sometm)
{
  time_t sometime;
  sometm->tm_mday=1;
  sometime = mktime(sometm);
  sometm = localtime_r(&sometime, sometm);
  }*/

void dayforward(struct tm *sometm)
{
  time_t sometime;
  sometime = mktime(sometm);
  sometime += 60*60*24;
  sometm = localtime_r(&sometime, sometm);
}
// go to the previous month
void pre_month(struct tm *sometm)
{
  time_t sometime;
  sometime = mktime(sometm);
  sometime -= 60*60*24*33;
  sometm = localtime_r(&sometime, sometm);
}
// print calendar of the given time
int printcalendar(struct tm *sometm)
{
  time_t days;
  int i,j;
  int current_month=sometm->tm_mon;
  int c_col=COL0;//margin
  int c_row=3;   
  sometm->tm_mday=1;//set date to the 1st day of the month  
  days =mktime(sometm);
  sometm=localtime_r(&days, sometm);
  c_col+= ((sometm->tm_wday+6)%7)*DAY_WIDTH;
  //find the cols for the first day according to the weekday it lands
  for(i=0;i<6;i++) //6 rows 
     {
       for(j=0;j<7;j++ ) //7 cols
	 {
	   if (sometm->tm_mon==current_month)
	     {
	       draw_box(c_row,c_col ,DAY_HEIGHT, DAY_WIDTH,sometm->tm_mday);
	       dayforward(sometm);
	       c_col+=DAY_WIDTH; 	       
	     }
	   if (c_col>COL0+7*DAY_WIDTH-1) //run to last col;
	     {
	       c_col=COL0; //reset col to margin break to begin a new row
	       break;
	     }
	 }
       c_row+=DAY_HEIGHT;                      
     }   
}
void printheader(struct tm* c_time)
{
  char  name_month[20];
  move (0,DAY_WIDTH*7/2-8);
  strftime(name_month,20,"%B    %Y", c_time);
  printw(name_month);   
  move (2,COL0);
  printw("   Monday     Tuesday   Wednesday  Thursday    Friday    Saturday    Sunday");
}

int main (int argc, char *argv[])
{   
  int key;
  const char * str_error="Error! This window is too small to display the calendar!";
  time_t  timenow;
  struct tm current_tm;
  struct tm *ptm;
  int i;
  timenow = time(NULL); 
  time(&timenow); //assign current time to timenow(in seconds)
  ptm=localtime_r(&timenow,&current_tm); //assign current time to structure current_tm, and pointer ptm 
  
  initscr();
  max_width=getmaxx(stdscr);
  max_height=getmaxy(stdscr);
  //check if the window is big enough
  if (max_width<DAY_WIDTH*7+COL0||max_height<DAY_HEIGHT*6+ROW0)
    {
      //print error message in the middle of window
      move(max_height/2,max_width/2-strlen(str_error)/2);
      printw(str_error);
      refresh();
      getch();
      endwin(); 
    }
  else
    {
      printheader(ptm);
      printcalendar(ptm);
       while(1)	 {  
	      key=getch();
	       if(key=='n'||key=='N')
		    { 
		      erase();
		      //  timenow=mktime(&current_tm);
		      //ptm= localtime_r(&timenow,&current_tm);
		      printheader(ptm);
		      printcalendar(ptm);
		      refresh();	      
		      }
	      else  if(key=='p'||key=='P')
		  {
		    erase();
		    // timenow=mktime(&current_tm);
		     // did not work, can't decrease the year
		     /*i=(current_tm.tm_mon+10)%12; 	    
		       current_tm.tm_mon=i;
		       if (i==11)
		       current _tm.year--;*/
		     //timenow-=24*60*60*50;		      
		     //	ptm= localtime_r(&timenow,&current_tm);
		      pre_month(&current_tm);
			printheader(&current_tm);
			printcalendar(&current_tm);
			refresh();
		  }
	      else if (key=='q'||key=='Q')
		  {
		      endwin();
		      exit(-1);
		   	  
		  }
       }
	  refresh();
	  getch();
	  endwin();
    }
}  





