#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define n 8
#define M 66
int i,j,h,k,l,t;
int step[n][n];
int eight[n][n][n];

typedef struct{
	int x;
	int y;
	int direct;
}point;

typedef struct{
	point *base;
	point *top;
}stack;

 stack s;
 
 Initstack()
 {
  s.base=(point*)malloc(M*sizeof(point));
  if(s.base==NULL)
  {printf("error");
  exit(0);}
  s.top=s.base;
 }
 
  empty()
{
	if(s.base==s.top)return(0);
	return(1);
 } 
 
 pop()
{
	if(s.base==s.top)return(0);
	s.top--;
    return(1);
}

 push( point e )
{
	*s.top=e;
	s.top++;
}

point next(point p, int d)
{
	switch(d)
	{
	case 0:
		p.x+=2; p.y+=1;
		break;
	case 1:
		p.x+=1;p.y+=2;
		break;
	case 2:
		p.x-=1;p.y+=2;
		break;
	case 3:
		p.x-=2;p.y+=1;
		break;
	case 4:
		p.x-=2;p.y-=1;
		break;
	case 5:
		p.x-=1;p.y-=2;
		break;
	case 6:
		p.x+=1;p.y-=2;
		break;
	case 7:
		p.x+=2;p.y-=1;
		break;
	}
	return p;
}
 
 check( point e )
{
	point *rear;
	if(e.x<0||e.x>n-1||e.y<0||e.y>n-1)
	return(0);
	for(rear=s.base;rear!=s.top;rear++)
	{
	 if((*rear).x==e.x&&(*rear).y==e.y)
	 return(0);
	}
	return(1);
}

 sets()
{
	point g1,g2;
	for(i=0;i<n;i++)
	 for(j=0;j<n;j++)
	 {
	  g1.x=i;
	   g1.y=j;
	    step[i][j]=0;
	  for(h=0;h<n;h++)
	  {
	     g2=next(g1,h);
	      if(g2.x>=0&&g2.x<n&&g2.y>=0&&g2.y<n)
	      step[i][j]++;
	  }
	 }
}

 sete()
{
	point q1,q2;
	int order[n];
	for(i=0;i<n;i++)
	 for(j=0;j<n;j++)
	 {
	  q1.x=i;
	   q1.y=j;
	    for(h=0;h<n;h++)
	    {
	     q2=next(q1,h);
	   	  if(q2.x<0||q2.x>n-1||q2.y<0||q2.y>n-1)
	   	   order[h]=0;
	   	 else 
	   	   order[h]=step[q2.x][q2.y];
	    }
	   for(k=0;k<n;k++)
	   {
	   	l=k;
	   	for(t=0;t<n;t++)
	   	{
		 if(order[t]<order[l])
	   	  l=t;
		}
		order[l]=10;
		eight[i][j][k]=l;
	   }
	 }
}

 horse( point p )
{
	int r,count=0;
	point bp=p;
	push(bp);
	count++;
	r=eight[(s.top-1)->x][(s.top-1)->y][(s.top-1)->direct];
	bp=next(*(s.top-1),r);
	bp.direct=0;
	 while(empty())
	 {
	 	if( check(bp) )
	 	{
	 		push(bp);
	 		count++;
	 		if(count==n*n)return(0);
	 		r=eight[(s.top-1)->x][(s.top-1)->y][(s.top-1)->direct];
	 		bp=next(*(s.top-1),r);
	 		bp.direct=0;
		 }
		else
		{
			while(empty()&&((s.top-1)->direct)==n-1 )
			{
			  pop();
			  count--;
			}
			if(empty()&&((s.top-1)->direct)<n-1 )
			{
			 r=eight[(s.top-1)->x][(s.top-1)->y][++(s.top-1)->direct];
	 		 bp=next(*(s.top-1),r);
	 		 bp.direct=0;
			}
		 } 
    }
  return(1);
} 

 print()
{
	int out[n][n];
	point *g=s.base;
	for(i=1;g!=s.top;i++)
	{
		out[g->x][g->y]=i;
		g++;
	}
	for(h=0;h<n;h++)
	{
		printf("\n\n");
		for(k=0;k<n;k++)
		{
			printf("%3d ",out[h][k]);
		}
	}
}

main()
{
	point first;
	srand((unsigned int)time(NULL));
	first.x=rand()%8;
	first.y=rand()%8;
	first.direct=0;
	Initstack();
	sets();
	sete();
	while(horse(first))
	{
	 first.x=rand()%8;
	 first.y=rand()%8;
	 first.direct=0;
	}
	print();
}


