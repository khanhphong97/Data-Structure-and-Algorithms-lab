#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
	char Model[50];
	char Memory[20];
	char ScreenSize[30];
	int Price;
} PHONE;

PHONE *get_input(int start,int end,int *m)
{
	FILE *f = fopen("PhoneDB.dat","rb");
	if (f == NULL)
	{
		printf("Error opening PhoneDB.dat\n\n");
		return NULL;
	}
	if (end == -1) // All
	{
		fseek(f,0,SEEK_END);
		end = ftell(f) / sizeof(PHONE);
	}
	int n = end - start + 1;
	PHONE *phone = (PHONE *) malloc(n * sizeof(PHONE));
	if (fseek(f,(start - 1) * sizeof(PHONE),SEEK_SET))
	{
		printf("Error in fseek\n\n");
		return NULL;
	}
	*m = fread(phone,sizeof(PHONE),n,f);
	fclose(f);
	return phone;
}

void importFromTxt()
{
	FILE *fi = fopen("PhoneDB.txt","r");
	if (fi == NULL)
	{
		printf("Error opening PhoneDB.txt\n");
		return;
	}
	FILE *fo = fopen("PhoneDB.dat","wb");
	PHONE phone;
	while (ftell(fi) != SEEK_END)
	{
		phone.Model[0] = '\0';
		fscanf(fi,"%s%s%s%d",phone.Model,phone.Memory,phone.ScreenSize,&phone.Price);
		if (strlen(phone.Model) == 0) break;
		fwrite(&phone,sizeof(PHONE),1,fo);
	}
	fclose(fi);
	fclose(fo);
	printf("Import data from text successfully!\n\n");
}

void importFromDB()
{
	printf("You want:\n");
	printf(" 1. Full list\n");
	printf(" 2. A part\n");
	printf("Your choice: ");
	int choice,start,end = 0;
	scanf("%d",&choice);
	switch (choice)
	{
	case 1:
		start = 1;
		end = -1; // Read full
		break;
	case 2:
		printf("Input the start point: ");
		scanf("%d",&start);
		if (start <= 0)
		{
			printf("The start point must be a positive number\n\n");
			return;
		}
		printf("Input the end point: ");
		scanf("%d",&end);
		break;
	default:
		printf("Invalid command\nThe choice must be from 1 to 2\n\n");
		return;
	}
	int n;
	PHONE *phone = get_input(start,end,&n);
	if (phone == NULL)
	return;

	printf("%*s%*s%*s%*s%*s\n",-3,"STT",-50,"MODEL",-20,"MEMORY",-30,"SCREEN SIZE",-15,"PRICE (VND)");
	
	for (int i=0; i<n; i++)
	printf("%*d%*s%*s%*s%*d\n",-3,i+start,-50,phone[i].Model,-20,phone[i].Memory,-30,phone[i].ScreenSize,-15,phone[i].Price);
	
	printf("\n");
	free(phone);
}

void printDB()
{
	int n;
	PHONE *phone = get_input(1,-1,&n);
	if (phone == NULL)
	return;
	int cnt = 3;
	
	printf("%*s%*s%*s%*s%*s\n",-3,"STT",-50,"MODEL",-20,"MEMORY",-30,"SCREEN SIZE",-15,"PRICE (VND)");
	
	for (int i=0; i<n; i++)
	{
		printf("%*d%*s%*s%*s%*d\n",-3,i+1,-50,phone[i].Model,-20,phone[i].Memory,-30,phone[i].ScreenSize,-15,phone[i].Price);
		cnt++;
		if (cnt == 25) // reach the final line of a part
	{
		printf("Press any key to continue...");
		char c;
		scanf("%*c%c",&c);
		cnt = 1;
	}
	}
	
	printf("\n");
	free(phone);
}

void findModel()
{
	char model[50];
	printf("Input the model you want to find: ");
	scanf("%*c"); gets(model);
	int n;
	PHONE *phone = get_input(1,-1,&n);
	if (phone == NULL)
	return;
	
	printf("%*s%*s%*s%*s%*s\n",-3,"STT",-50,"MODEL",-20,"MEMORY",-30,"SCREEN SIZE",-15,"PRICE (VND)");
	for (int i=0; i<n; i++) {
		// Check string in string
	for (int j=0; j+strlen(model)-1<strlen(phone[i].Model); j++)
		{
		int check = 1;
		for (int k=0; k<strlen(model); k++)
			if (tolower(model[k]) != tolower(phone[i].Model[j+k]))
			{
				check = 0;
				break;
			}
		if (check)
			printf("%*d%*s%*s%*s%*d\n",-3,i+1,-50,phone[i].Model,-20,phone[i].Memory,-30,phone[i].ScreenSize,-15,phone[i].Price);
		}
		}
	
}

int main()
{
	int select;
	while (select != 5) {
		printf(" 1. Import DB from text\n");
		printf(" 2. Import from DB\n");
		printf(" 3. Print all database\n");
		printf(" 4. Find model\n");
		printf(" 5. Exit\n");
		printf("Your choice: ");
		scanf("%d",&select);
		switch (select) {
		case 1: importFromTxt(); break;
		case 2: importFromDB(); break;
		case 3: printDB(); break;
		case 4: findModel(); break;
		case 5: return 0;
		default:
			printf("Not a valid! only 1 > 5\n\n");
			break;
		}
	}
}
