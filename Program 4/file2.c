//Abdullah Kidwai
//akidwa2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "header.h"


void addToList(WaitList *head, char name[], int size, int status)
{
	WaitList *temp = (WaitList *)malloc(sizeof(WaitList));
	strcpy(temp->GroupName, name);
	temp->GroupSize = size;
	temp->GroupStatus = status;

	if (head == NULL)
	{
		head = temp;
		return;
	}
	
	WaitList *cur = head;
	WaitList *previous = NULL;

	while (cur != NULL)
	{
		previous = cur;
		cur = cur->pNext;
	}
	previous->pNext = temp;

	return;
}

int doesNameExist(WaitList *head, char name[])
{
	WaitList *cur = head;

	while (cur != NULL)
	{
		if (strcmp(cur->GroupName, name) == 0)
			return 1;
		else
			cur = cur->pNext;
	}
	return 0;
}

void displayListInformation(WaitList *head)
{
	WaitList *cur = head;

	int i = 0;
	while (cur != NULL)
	{
		i++;
		printf("Name: %s\t", cur->GroupName);
		printf("Size: %d\t", cur->GroupSize);
		cur = cur->pNext;
	}

	printf("\nTotal groups: %d\n", i);
}

void updateStatus(WaitList *head, char name[])
{
	WaitList *cur = head;

	while (cur != NULL)
	{
		if (strcmp(cur->GroupName, name) == 0)
		{
			cur->GroupStatus = 1;
		}
		
		cur = cur->pNext;
	}
}

int countGroupsAhead(WaitList *head, char name[])
{
	WaitList *cur = head;

	int i = 0;
	while (cur != NULL)
	{
		i++;
		if (strcmp(cur->GroupName, name) == 0)
			return i;
		
		cur = cur->pNext;
	}
}

void displayGroupSizeAhead(WaitList *head, char name[])
{
	WaitList *cur = head;

	while (strcmp(cur->GroupName, name) != 0)
	{
		printf("%d\n", cur->GroupSize);
		cur = cur->pNext;
	}
}

void retrieveAndRemove(WaitList *head, int tableSize)
{
	WaitList *cur = head;
	WaitList *previous = head;

	if (cur == NULL)
	{
		printf("list is empty\n");
	}
	
	if (cur->GroupSize <= tableSize && cur->GroupStatus == 1)
		head = head->pNext;

	while (cur != NULL)
	{
		previous = cur;
		if (cur->GroupSize <= tableSize && cur->GroupStatus == 1)
			previous->pNext = cur->pNext;
		else
			cur = cur->pNext;
	}

}
