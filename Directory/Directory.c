#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct cvor* Folder;

typedef struct cvor
{
	char name[20];
	Folder sibling;
	Folder child;
}Node;

typedef struct stog* Pozicija;

typedef struct stog
{
	Folder data;
	Pozicija next;
}Stog;

Pozicija Alocation1();

Folder Alocation();

void Menu();

void Mdirectory(Folder, char[]);

Folder ChangeDirF(Folder, Pozicija, char[]);

void Dir(Folder);

void Push(Pozicija, Folder);

Folder Pop(Pozicija);

int main()
{
	int test = 0;
	char temp[20];
	Folder root = Alocation();
	Folder current = root;
	Pozicija head;
	head = Alocation1();
	printf("Nalazite se u Root direktoriju, on je prazan!\n");
	while (test != 5)
	{
		Menu();
		scanf("%d", &test);
		switch (test)
		{
		case 1:
			printf("Unesite ime datoteke: ");
			scanf("%s", temp);
			Mdirectory(current, temp);
			break;
		case 2:
			printf("Unesite ime datoteke: ");
			scanf("%s", temp);
			current = ChangeDirF(current, head, temp);
			break;
		case 3:
			current = Pop(head);
			break;
		case 4:
			Dir(current);
			break;
		default:
			printf("Krivi unos!!\n");
			break;
		}
	}




	return 0;
}

Pozicija Alocation1()
{
	Pozicija novi;
	novi = (Pozicija)malloc(sizeof(Stog));
	novi->next = NULL;
	novi->data = NULL;
	return novi;
}

Folder Alocation()
{
	Folder novi;
	novi = (Folder)malloc(sizeof(Node));
	novi->child = NULL;
	novi->sibling = NULL;
	strcpy(novi->name, "");
	return novi;
}

void Menu()
{
	printf("\n#####################\n");
	printf("1. za md\n");
	printf("2. za cd\n");
	printf("3. za cd ..\n");
	printf("4. za dir\n");
	printf("5. za izlaz\n");
	printf("#####################\n\n");
}

void Mdirectory(Folder current, char name[])
{
	Folder novi = Alocation();
	strcpy(novi->name, name);
	if (current->child == NULL)
	{
		current->child = novi;
	}
	else
	{
		current = current->child;
		if (current->sibling == NULL)
		{
			current->sibling = novi;
		}
		else
		{
			while (current->sibling != NULL)
			{
				current = current->sibling;
			}
			current->sibling = novi;
		}
	}
}

void Dir(Folder current)
{
	if (current->child == NULL)
	{
		printf("Datoteka je prazna!\n");
	}
	else
	{
		if (current->child->sibling == NULL)
		{
			printf("%s\n", current->child->name);
		}
		else
		{
			current = current->child;
			while (current->sibling != NULL)
			{
				printf("%s\n", current->name);
				current = current->sibling;
			}
			printf("%s\n", current->name);
		}

	}
}

Folder ChangeDirF(Folder current, Pozicija head, char name[])
{
	Push(head, current);
	Folder glavna = current;
	if (current->child == NULL)
	{
		printf("Datoteka je prazna!!\n");
	}
	else
	{
		current = current->child;
		while (current->sibling != NULL)
		{
			if (!(strcmp(current->name, name)))
			{
				return current;
			}
			current = current->sibling;
		}
		if (!(strcmp(current->name, name)))
		{
			return current;
		}
		else
		{
			printf("Ne postoji takva datoteka\n");
			return glavna;
		}
	}
}

void Push(Pozicija head, Folder current)
{
	if (head->next == NULL)
	{
		Pozicija novi = Alocation1();
		novi->data = current;
		head->next = novi;
	}
	else
	{
		while (head->next != NULL)
		{
			head = head->next;
		}
		Pozicija novi = Alocation1();
		novi->data = current;
		head->next = novi;
	}
}

Folder Pop(Pozicija head)
{
	Folder novi;
	Pozicija temp;
	while (head->next->next != NULL)
	{
		head = head->next;
	}
	novi = head->next->data;
	temp = head->next;
	head->next = NULL;
	free(temp);
	return novi;
}

