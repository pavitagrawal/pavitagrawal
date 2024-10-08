# include <stdio.h>
#include<stdlib.h>
struct node
{
	int info;
	struct node *link;
}*start;
int create_list(int),addatbeg(int),addafter(int,int),del(int),display(),count(),rev(),search(int);
main()
{
	int choice,n,m,position,i;
	start=NULL;
	while(1)
	{
		printf("\n\n");
		printf("1.Create List\n");
		printf("2.Add at begining\n");
		printf("3.Add after \n");
		printf("4.Delete\n");
		printf("5.Display\n");
		printf("6.Count\n");
		printf("7.Reverse\n");
		printf("8.Search\n");
		printf("9.Quit\n");
		printf("Enter your choice : ");
		scanf("%d",&choice);
		switch(choice)
		{
		 case 1:
			printf("How many nodes you want : ");
			scanf("%d",&n);
			for(i=0;i<n;i++)
			{
				printf("Enter the element : ");
				scanf("%d",&m);
				create_list(m);
			}
			break;
		 case 2:
			printf("Enter the element : ");
			scanf("%d",&m);
			addatbeg(m);
			break;
		 case 3:
			printf("Enter the element : ");
			scanf("%d",&m);
			printf("Enter the position after which this element is inserted : ");
			scanf("%d",&position);
			addafter(m,position);
			break;
		 case 4:
			if(start==NULL)
			{
				printf("List is empty\n");
				continue;
			}
			printf("Enter the element for deletion : ");
			scanf("%d",&m);
			del(m);
			break;
		 case 5:
			display();
			break;
		 case 6:
			count();
			break;
		 case 7:
			rev();
			break;
		 case 8:
			printf("Enter the element to be searched : ");
			scanf("%d",&m);
			search(m);
			break;
		 case 9:
			exit(0);
		 default:
			printf("Wrong choice\n");
		}
	}
}
int create_list(int data)
{
	struct node *q,*tmp;
	tmp=(struct node *) malloc(sizeof(struct node));
	tmp->info=data;
	tmp->link=NULL;
	if(start==NULL)
		start=tmp;
	else
	{
		q=start;
		while(q->link!=NULL)
			q=q->link;
		q->link=tmp;
	}
}
int addatbeg(int data)
{
	struct node *tmp;
	tmp=(struct node *)malloc(sizeof(struct node));
	tmp->info=data;
	tmp->link=start;
	start=tmp;
}
int addafter(int data,int pos)
{
	struct node *tmp,*q;
	int i;
	q=start;
	for(i=0;i<pos-1;i++)
	{
		q=q->link;
		if(q==NULL)
		{
			printf("There are less than %d elements",pos);
		}
	}
	tmp=(struct node *)malloc(sizeof(struct node) );
	tmp->link=q->link;
	tmp->info=data;
	q->link=tmp;
}
int del(int data)
{
	int found=0;
	struct node *tmp,*q,*pre;
	if(start->info == data)
	{
		tmp=start;
		start=start->link;
		free(tmp);
		found=1;
	}
	else
	{
		found=0;
		q=start;
		while(q->link!=NULL)
		{
			if(q->info==data)
			{
				found=1;
				pre->link=q->link;
				tmp=q;
				free(tmp);
				break;
			}
			pre=q;
			q=q->link;
		}
		if(q->info==data)
		{
			tmp=q;
			free(tmp);
			pre->link=NULL;
			found=1;
		}
	}
	if(found==0){
		printf("Element %d not found\n",data);
	}
}
int display()
{
	struct node *q;
	if(start == NULL)
	{
		printf("List is empty\n");
	}
	q=start;
	printf("List is :\n");
	while(q!=NULL)
	{
		printf("%d ", q->info);
		q=q->link;
	}
	printf("\n");
}
int count()
{
	struct node *q=start;
	int cnt=0;
	while(q!=NULL)
	{
		q=q->link;
		cnt++;
	}
	printf("Number of elements are %d\n",cnt);
}
int rev()
{
	struct node *p1,*p2,*p3;
	if (start==NULL||start->link==NULL){
        return;
	}
    p1=start;
    p2=p1->link;
    p3=p2->link;
    p1->link=NULL;
    p2->link=p1;
	while(p3!=NULL)
	{
		p1=p2;
		p2=p3;
		p3=p3->link;
		p2->link=p1;
	}
	start=p2;
}
int search(int data)
{
	struct node *ptr = start;
	int pos = 1;
	while(ptr!=NULL)
	{
		if(ptr->info==data)
		{
			printf("Item %d found at position %d\n",data,pos);
		}
		ptr = ptr->link;
		pos++;
	}
	if(ptr == NULL)
		printf("Item %d not found in list\n",data);
}
