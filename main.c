#include <stdio.h>
#include <string.h>

#define MAX_TASKS 25
#define MAX_DESC_SIZE 50

typedef struct Task {
	int isDone;
	char description[MAX_DESC_SIZE];
}Task;


void displayMenu();
void addTask();
void printTasks();
void markTask();
void loadTasks();
void saveTasks();


Task taskList[MAX_TASKS];
int tasksCount = 0;

void main()
{
	int choice;
	char ch;

	loadTasks();

	do {
		displayMenu();
		printf("Please enter your choice: ");
		scanf("%d", &choice);
		ch = getchar();

		switch (choice)
		{
		case 1:
			addTask();
			break;
		case 2:
			printTasks();
			break;
		case 3:
			markTask();
			break;
		case 4:
			printf("GOODBYE!\n");
			break;
		default:
			printf("invalid choice\n");
			break;
		}
	} while (choice != 4);

	saveTasks();
}


void displayMenu() {
	system("CLS");
	printf("\n===== To-Do List Menu =====\n");
	printf("1. Add a task\n");
	printf("2. View tasks\n");
	printf("3. Mark task as done\n");
	printf("4. Exit\n");
	printf("===========================\n");
}

void addTask()
{
	char ch;
	if (tasksCount < MAX_TASKS)
	{
		printf("Please enter your task description: ");
		scanf("%[^\n]", taskList[tasksCount].description);
		taskList[tasksCount++].isDone = 0;
	}
	else {
		printf("Tasks list is full\n");
		printf("Enter any key to continue");
		ch = getch();
	}
}

void printTasks()
{
	char ch;
	system("CLS");
	if (tasksCount > 0)
	{
		for (int i = 0; i < tasksCount; i++)
		{
			if (taskList[i].isDone == 0)
			{
				printf("o\t %s\n", taskList[i].description);
			}
			else {
				printf("x \t %s\n", taskList[i].description);
			}
		}
		printf("====================================\n");
	}
	else {
		printf("You dont have any tasks\n");
	}
	printf("Enter any key to continue");
	ch = getch();
}

void markTask()
{
	int taskNum;
	Task temp; 
	char ch;

	printf("Please enter which task did you done with? ");
	scanf("%d", &taskNum);

	if (taskNum < tasksCount)
	{
		taskList[taskNum - 1].isDone = 1;
	}
	else {
		printf("Task not exist\n");
	}
	printf("Enter any key to continue");
	ch = getch();
	
}

void loadTasks()
{
	FILE* fp = fopen("tasks.txt", "r");
	while (fscanf(fp, "%d;%[^\n]", &taskList[tasksCount].isDone, taskList[tasksCount].description) == 2)
	{
		tasksCount++;
	}
	fclose(fp);
	printf("Task loaded from file\n");
}

void saveTasks()
{
	FILE* fp = fopen("tasks.txt", "w");
	for (int i = 0; i < tasksCount; i++) {
		fprintf(fp, "%d;%s\n", taskList[i].isDone, taskList[i].description);
	}
	fclose(fp);
	printf("Tasks saved to file\n");
}