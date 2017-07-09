/**menu driven control management system
# saurabh jindal
# language used c
# file handling in binary mode
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>


COORD coord = {0,0};
void gotoxy(int x,int y)
{
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);

}
// main function start here....
int main()
{
	FILE *fp;
	FILE *ft;
	char another,choice;
	struct emp{
		char name[40];
		int age;
		float salary;
	}e;
	char empname[40];
	long int recsize;
	fp = fopen("EMP.xlsx","r+");
	if(fp == NULL)
	{
		fp = fopen("EMP.xlsx","w+");
		if(fp == NULL)
		{
			printf("file not open...");
			exit(1);
		}
	}

	recsize = sizeof(e);
	while(1)
	{
		system("cls");
		gotoxy(30,10);
		printf("1. Add Record");
		gotoxy(30,12);
		printf("2. List Record");
		gotoxy(30,14);
		printf("3. Modify Record");
		gotoxy(30,16);
		printf("4. Delete");
		gotoxy(30,18);
		printf("5. Exit");
		gotoxy(30,20);
		printf("Enter Your Choices: ");
	
	fflush(stdin);
	choice = getche();
	switch(choice)
	{
		case '1' :
			system("cls");
			fseek(fp,0,SEEK_END);
			another = 'y';
			while(another == 'y')
			{
				printf("\nEnter name: ");
				scanf("%s",&e.name);
				printf("\nEnter age: ");
				scanf("%d",&e.age);
				printf("\nEnter basic salary: ");
				scanf("%f",&e.salary);
				fwrite(&e,recsize,1,fp); // write the record to the file ..
				printf("\nAdd Another record(y/n)");
				fflush(stdin);
				another = getche();
			}
			break;
			case '2':
				system("cls");
				rewind(fp); // allocates the pointer to start of the file.....
			while(fread(&e,recsize,1,fp) == 1) //  read the file and fetch the record one record per fetch
			{
				printf("\n%s %d %.2f",e.name,e.age,e.salary);
			}	
			getch();
			break;
			case '3':
			system("cls");
			another = 'y';
			while(another == 'y')
			{
				printf("Enter the employee name to modify..: ");
				scanf("%s",empname);
				rewind(fp);
				while(fread(&e,recsize,1,fp) == 1)
				{
					if (strcmp(e.name,empname) == 0)
					{
						printf("\nEnter new name: ");
						scanf("%s",&e.name);
						printf("\nEnter new age: ");
						scanf("%d",&e.age);
						printf("\nEnter new salary: ");
						scanf("%f",&e.salary);
						
						
						fseek(fp,-recsize,SEEK_CUR);
						fwrite(&e,recsize,1,fp);
						break;
					}
				}
				printf("\nModify another record(y/n)");
				fflush(stdin);
				another = getche();
				}
				break;
			case '4':
				system("cls");
				another = 'y';
				while(another == 'y')
				{
					printf("\nEnter name of the employee to delete: ");
					scanf("%s",empname);
					ft = fopen("temp.xlsx","w");
					rewind(fp);
					while(fread(&e,recsize,1,fp) == 1)
					{
						if(strcmp(e.name,empname) != 0)
						{
							fwrite(&e,recsize,1,ft);
						}
					}
					fclose(fp);
					fclose(ft);
					
					rename("temp.xlsx","EMP.xlsx");
					fp = fopen("EMP.xlsx","r+");
					printf("Delete another record...(y/n)");
					fflush(stdin);
					another = getche();



				}
				break;
				case '5':
					fclose(fp);
					exit(0);






		}

	}
	return 0;




}




