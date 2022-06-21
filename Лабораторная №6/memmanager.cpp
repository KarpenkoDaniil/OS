#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <locale.h>
#include <iomanip>
#include <windows.h> 
char bufRus[256];
char* Rus(const char* text)
{
	CharToOem(text, bufRus);
	return bufRus;
}
using namespace std;

void add_proc(int col_pages, string *processes, int *numbers, char* memory[], int &size1, int &free_pages, int page_size, string *Vprocesses, int *Vnumbers, char* Vmemory[], int* obr, int &Vcol_pages)
{
    string m;
    printf(Rus("������� ��� ��������: "));
    fflush(stdin);
    getline(cin, m);
    int i, n, min, j, n1;
    printf(Rus("������� ���������� ����, ������ ��������: "));
    while(n <= 0 || isalpha( n ) != 0){
    	scanf("%d", &n);
    	fflush(stdin);
		if(n <= 0)
			puts(Rus("�������� �����"));
    }
    n1 = n;
    
    int pages, h;
    pages = n / page_size;
    if(n % page_size != 0)
    	pages++;
    
    /*
	rand = rand();
    printf("%d", rand);
    dfjgmfdm
    */
    
    if(pages <= col_pages) {
	    if(size1 >= n){
		    for(i = 0; i < col_pages, n != 0; i++){
		    	if(processes[i] == "" && numbers[i] == 0 && n >= page_size){
		    		processes[i] = m;
		    		numbers[i] = page_size;
		    		obr[i] = 1;
		    		memory[i] = (char*) malloc (page_size);
		    		free_pages--;
		    		size1 = size1 - page_size;
		    		n = n - page_size;
				} else if(processes[i] == "" && numbers[i] == 0 && n < page_size){
					processes[i] = m;
		    		numbers[i] = n;
		    		obr[i] = 1;
		    		memory[i] = (char*) malloc (n);
		    		free_pages--;
		    		size1 = size1 - page_size;
		    		n = 0;
				}
			}
			
			puts(Rus("\n������� ��������"));
			
		} else {     // ������� ������ ��� ��������� ������, ����� �������� �������� ����������
			i = 0;
			while(n != 0){
		    	min = 500; 
		    	for(h=0; h < col_pages; h++)
		    		if(min > obr[h] && obr[h]>0) min = obr[h];
		    	//printf("MIN = %d\n", min);
		    	if(processes[i] == "" && numbers[i] == 0 && size1 != 0){
		    		processes[i] = m;
		    		numbers[i] = page_size;
		    		obr[i] = 999;
		    		memory[i] = (char*) malloc (page_size);
		    		free_pages--;
		    		size1 = size1 - page_size;
		    		n = n - page_size;
		    		pages = pages - 1;
				} else if(processes[i] != "" && numbers[i] != 0 && size1 == 0){
					if(obr[i] == min){
						for( h = 0; h<col_pages; h++){
		    				if(Vprocesses[h] == "" && Vnumbers[h] == 0) {
		    					Vprocesses[h] = processes[i];
			    				Vnumbers[h] = numbers[i];
			    				Vmemory[h] = memory[i];
			    				Vcol_pages++;
			    				free(memory[i]);
			    				break;
							}
						}
			    		processes[i] = m;
			    		if(pages > 1)
			    		{
			    			numbers[i] = page_size;
			    			memory[i] = (char*) malloc (page_size);
			    			n = n - page_size;
			    			obr[i] = 999;
			    			pages--;
			    		}
			    		else
			    		{
			    			numbers[i] = n;
			    			memory[i] = (char*) malloc (n);
			    			n = 0;
			    			obr[i] = 999;
			    			pages--;
			    			printf(Rus("\n������� �������� � ������ � ���������� �������."));
			    		}
					}
				}
				i++;
				if(i == col_pages) i = 0;
			}
			
			for( i = 0; i < col_pages; i++){
				if(processes[i] == m) {
					obr[i] = 1;
				}
			}		
		}
	} else
		puts(Rus("���������� �������� �������, �.�. �� �� ���������� � ������"));
}

void delete_process(int col_pages, string *processes, int *numbers, char* memory[], int &size1, int &free_pages, int page_size, int* obr)
{
    string m;
    printf(Rus("������� ��� ��������, ������� ������ �������: "));
    fflush(stdin);
    getline(cin, m);
    
	int d = 0, i;
	
	for(i = 0; i < col_pages; i++){
		if(processes[i] == m && numbers[i] != 0) {
            processes[i] = "";
            numbers[i] = 0;
            obr[i] = 0;
            free(memory[i]);
            free_pages++;
			size1 = size1 + page_size;	
			d++;		
		}
	}
 
    if(d == 0)
		printf(Rus("\n�������� �� �������������!"));
	else
    	printf(Rus("\n������ ����������� �� �������� ��������."));
}

void call_process(int col_pages, string *processes, int *numbers, char* memory[], int &size1, int &free_pages, int page_size, int* obr)
{
    string m;
    printf(Rus("������� ��� ��������, � �������� ������ ����������: "));
    fflush(stdin);
    getline(cin, m);
    
	int i, b = 0;
	
	for(i = 0; i < col_pages; i++){
		if(processes[i] == m && numbers[i] != 0) {
            obr[i]++;
			b++;	
		}
	//	printf("%d\n", obr[i]);
	}
 	if(b == 0){
 		puts(Rus("������� �� ������"));
	 }else{
	 	puts(Rus("������� ������"));
	 }
}

void menu()
{
	puts(Rus("\n1. ����������"));
    puts(Rus("2. �������� �������"));
    puts(Rus("3. ������� �� ��������"));
    puts(Rus("4. ������� �������"));
    puts(Rus("5. ����� �������� �� ������"));
    puts(Rus("6. ����� �� ���������"));
    printf(Rus("\n�������� ����� ����: "));
}

void table(int col_pages, string *processes, int *numbers) //����� �������
{
	int i;
	//�����
	const char *S;
	printf("%c", 218);
	for(i=0;i<16;i++) printf("%c", 196);  printf("%c", 194); for(i=0;i<19;i++) printf("%c", 196);  printf("%c", 194);
	for(i=0;i<25;i++) printf("%c", 196); printf("%c\n", 191);
	printf(Rus("%c ����� �������� %c �������� �������� %c ���������� ������� ���� %c\n"), 179,179,179,179);
	for(int j=0; j<col_pages; j++)
	{
		if(j!=col_pages-1)
		{
			printf("%c", 195); for(i=0;i<16;i++) printf("%c", 196); printf("%c", 197);
			for(i=0;i<19;i++) printf("%c", 196); printf("%c", 197); for(i=0;i<25;i++) printf("%c", 196); printf("%c\n", 180);
			S = processes[j].c_str();
			printf(Rus("%c%8d        %c%10s         %c%15d          %c\n"), 179, j+1, 179, S, 179, numbers[j], 179);
		}
		else
		{
			printf("%c", 195); for(i=0;i<16;i++) printf("%c", 196); printf("%c", 197);
			for(i=0;i<19;i++) printf("%c", 196); printf("%c", 197); for(i=0;i<25;i++) printf("%c", 196); printf("%c\n", 180);
			S = processes[j].c_str();
			printf(Rus("%c%8d        %c%10s         %c%15d          %c\n"), 179, j+1, 179, S, 179, numbers[j], 179);
			
			printf("%c", 192); for(i=0;i<16;i++) printf("%c", 196); printf("%c", 193);
			for(i=0;i<19;i++) printf("%c", 196); printf("%c", 193); for(i=0;i<25;i++) printf("%c", 196); printf("%c", 217);
		}
	}
}

int main()
{
	int size = -1; //������ ����� ������
    int col_pages = -1; //���������� �������
    int page_size = -1; // ������ ����� ��������
    int free_pages = -1; //���������� ��������� �������
    int Vcol_pages = 0;
       
    while(size <= 0 || isalpha( size ) != 0){
    	printf(Rus("������� ����� ������ � ������: "));
    	scanf("%d",&size);
    	fflush(stdin);
		if(size <= 0)
			puts(Rus("�������� ����� ������"));
    }
    
    while(col_pages <= 0 || page_size < 1 || isalpha( col_pages ) != 0){
    	printf(Rus("������� ���������� �������: "));
    	scanf("%d",&col_pages); //���������� �������
    	fflush(stdin);
    	if( col_pages != 0 && isalpha( col_pages ) == 0){
			page_size = size / col_pages;
			if(page_size < 1)
				puts(Rus("������ �������� ������ ������ �����"));
		}
    	if(col_pages <= 0 || page_size < 1)
			puts(Rus("�������� ���-�� �������"));
    }
    
     // ������ ����� ��������
    free_pages = col_pages;
    
    int size1 = size;
    
    int obr[col_pages];
    
    string processes[col_pages]; //������ ���� ���������
    string Vprocesses[col_pages];
    
    int numbers[col_pages]; //������ ���������� ������ ���������
    int Vnumbers[col_pages];
    
    for(int i = 0; i < col_pages; i++)
	{
		processes[i] = "";
		numbers[i] = 0;
		Vprocesses[i] = "";
		Vnumbers[i] = 0;
	}
    
    char* memory[col_pages]; //������ ������ ��� ��������
    char* Vmemory[col_pages];
    
    int k = 0;
    while(true)
    {	
    	int b = 0;
        while(b == 0){
			menu();
        	scanf("%d",&k);
        	fflush(stdin);
        	if(isalpha( k ) != 0 || k <= 0){
        		system("cls");
        		puts(Rus("������� ������������ ��������"));
			} else
				b = 1;
		}	
        system("cls");
        switch(k)
    	{
		case 1:
			printf(Rus("����������:\n"));
			printf(Rus("����� ������ (� ������): %d\n"),size);
			printf(Rus("����� ��������� ������ (� ������): %d\n"),size1);
			printf(Rus("������ �������� (� ������): %d\n"), page_size);
			printf(Rus("����� �������: %d\n"), col_pages);
			printf(Rus("����� ��������� �������: %d\n"), free_pages);
			k = -1;
			break;
		case 2:
			add_proc(col_pages, processes, numbers, memory, size1, free_pages, page_size, Vprocesses, Vnumbers, Vmemory, obr, Vcol_pages);
			k = -1;
			break;
		case 3:
			delete_process(col_pages, processes, numbers, memory, size1, free_pages, page_size, obr);
			k = -1;
			break;
		case 4:
			printf(Rus("\n ����������� ������ ����������\n"));
			table(col_pages, processes, numbers);
			printf(Rus("\n\n ��������(��������) ������ ����������\n"));
			table(Vcol_pages, Vprocesses, Vnumbers);
			k = -1;
			break;
		case 5:
			call_process(col_pages, processes, numbers, memory, size1, free_pages, page_size, obr);
			k = -1;
			break;
		case 6:
			exit(0);
			break;
		default:
			puts(Rus("������ ������������ ����� ����!"));
			k = -1;
	   }
	   printf("\n");
    }
    return 0;
}
