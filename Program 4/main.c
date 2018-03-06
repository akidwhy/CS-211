//Abdullah Kidwai
//akidwa2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "header.h"


int main(int argc, char **argv)
{

	char *input;
	int ch;


	WaitList *Head = (WaitList *)malloc(sizeof(WaitList));

	Head->GroupName = NULL;
	Head->GroupSize = -1;
	Head->GroupStatus = -1;
	Head->pNext = NULL;


	printf("Starting Restaurant Wait List Program\n\n");
	printf("Enter command: ");

	while ((ch = getNextNWSChar()) != EOF)
	{
		/* check for the various commands */
		if ('q' == ch)
		{
			printf("Quitting Program\n");
			return (0);
		}
		else if ('?' == ch)
		{
			printCommands();
		}
		else if ('a' == ch)
		{
			doAdd(Head);
		}
		else if ('c' == ch)
		{
			doCallAhead(Head);
		}
		else if ('w' == ch)
		{
			doWaiting(Head);
		}
		else if ('r' == ch)
		{
			doRetrieve(Head);
		}
		else if ('l' == ch)
		{
			doList(Head);
		}
		else if ('d' == ch)
		{
			doDisplay(Head);
		}
		else
		{
			printf("%c - in not a valid command\n", ch);
			printf("For a list of valid commands, type ?\n");
			clearToEoln();
		}

		printf("\nEnter command: ");
	}

	printf("Quiting Program - EOF reached\n");
	return 1;
}
