#include<ncurses.h>
#include<time.h>

char grid [50][100];
int startx=0 , test =1 , starty = 20 , shootery=40 , old = 40 ,bulletx=49 , bullety , game=1 , bulletFlag=0;

void init()
{
	int i,j;
	for( i=0 ; i<50 ; i++ )
		for ( j=0 ; j<100 ; j++) 
			grid[i][j] = ' ';
}

void placeInvaders ()
{
	int i,j;
	for( i=0 ; i<20 ; i++ )
		for ( j=0 ; j<40 ; j++ )
			grid[startx+i][starty+j] = 'M';
}

void placeShooter()
{
	int i;
	for( i=0 ; i<10 ; i++ )
	{
		if ( i ==5 )
			grid[49][shootery+i] = 'T';
		else
			grid[49][shootery+i] = 'o';
	}
}

void print()
{
	printw("%d\n",test);
	int i,j;
	for ( i=0 ; i<50 ; i++ )
	{
		printw("|");
		for ( j=0 ; j<100 ; j++ )
		{
			printw("%c",grid[i][j]);
			if ( j==99)
				printw("|");
		}
		printw("\n");
	}
	for ( i=0 ; i<102 ; i++ )
		printw("-");
}

void shoot ()
{
	bulletFlag = 1;
	bulletx=48;
	bullety=shootery+5;
	grid[bulletx][bullety] = 'i';
}

void elevateBullet()
{
	if(bulletx==0)
	{
		bulletFlag=0;
		grid[bulletx][bullety]=' ';
		return;
	}
	if ( grid[bulletx-1][bullety]=='M')
	{
		test=0;	
		grid[bulletx-1][bullety] = ' ';
		grid[bulletx][bullety]=' ';
		bulletFlag=0;
	}
	else
	{
		grid[bulletx][bullety] = ' ';
		bulletx--;
		grid[bulletx][bullety] = 'i';
	}
}


int main()
{
	init();
	placeInvaders();
	placeShooter();
	initscr();
	noecho();
	halfdelay(2);
	char c;
	while(game)
	{
		c = getch();
		switch (c)
		{
			case 'o':
			{
				if (  shootery > 0 )
				{
					grid[49][shootery+9] = ' ';
					shootery--;
			    erase();
          placeShooter();
					if (bulletFlag)
			 			elevateBullet();	
				}
			}
				break;
			case 'p':
			{
				if (  shootery <89 )
				{
					grid[49][shootery] = ' ';
					shootery++;
		      erase();
          placeShooter();
					if (bulletFlag)
			 			elevateBullet();	
				}
			}

			break;
			case 'w':
			{
				if (!bulletFlag)
				{
		      erase();
					shoot();
				}
				else
					erase();
			}
			break;

			default :
			{
				erase();
				if (bulletFlag)
			 		elevateBullet();	
			}
			break;
		}
	print();
	}
	getch();
	echo();
	endwin();
	return 0;
}


