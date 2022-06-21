 #include <stdio.h>
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

void menu()
{
	puts(Rus("\n1. Информация"));
    puts(Rus("2. Добавить процесс"));
    puts(Rus("3. Удалить по названию"));
    puts(Rus("4. Таблица страниц"));
    puts(Rus("5. Выход из программы"));
    printf(Rus("\nВыберите пункт меню: "));
}

void add_proc(string* processes,int* numbers,int &size1, int size, char* memory[], int &v_call) {
	string m;
    printf(Rus("Введите имя процесса: "));
    fflush(stdin);
    getline(cin, m);
    int n;
    printf(Rus("Введите количество байт, нужных процессу: "));
    scanf("%d", &n);
   	int ind=0, q = 0;
    int check = 0;
    string buf;
	int check_max = 0;

	    for(int i = size - 1; i >= 0; i--)
	    {
	    	if(processes[i] == "" && numbers[i] == 0)
	    	{
	    		check++;
			}else if(processes[i] != "" && numbers[i] != 0){
				check = 0;			
			}
			if(check==n){
				ind=i;
				break;
			}
	    }
	    
	    if(check == 0 || n > check) {  
	    	int k, k_max=0;
			for(int i = size - 1; i >= 0; i--) {
				k=0;
				for(int j= size - 1; j >= 0; j--) {
				    if(processes[i] == processes[j] && processes[i] != "") {
				    	k++;
					}
				}
				if(k_max < k) {
					k_max = k;
					ind = i;
				}
			}
			
			buf = processes[ind];
			int ind1 = ind;
			int ind2;
					
			int k_max1 = k_max;
			for(int i = 0; i < size, k_max != 0; i++) {
				if(processes[i] == processes[ind1]){
					processes[i] = "";
					size1 = size1 + 1;
		    	    numbers[i] = 0;
		    	    free(memory[i]);
		    	    if(k_max == 1)
		    	    	ind = ind2 = i;
		    	    k_max--;
				}
		    }
		    	
		    check_max = 0;
		    check = 0;
		    
		    for(int i = size - 1; i >= 0; i--)
			{
			   	if(processes[i] == "" && numbers[i] == 0)
			   	{
			  		check++;
				}else if(processes[i] != "" && numbers[i] != 0){
					check = 0;			
				}
				if(check_max < check)
					check_max = check;	
				if(check==n){
					ind=i;
				}
			}
			
			if(n > check_max) {
				ind=ind2;
				
				for(int i = ind; i < size, k_max1 != 0; i++) {
			        processes[i] = buf;
					size1 = size1 - 1;
			        numbers[i] = 1;
			   	    memory[i] = (char*) malloc (1);
			        if(k_max == 1)
			        	ind = i;
			        k_max1--;
			    }
				
				puts(Rus("Невозможно добавить процесс"));
				
				return;
			}
			q = 1;
		}
	
	
	for(int i = ind; i < size, n > 0; i++)
    {
    	if(processes[i] == "" && numbers[i] == 0)
    	{
    		processes[i] = m;
    		numbers[i] = 1;
    		size1 = size1 - 1;
    		memory[i] = (char*) malloc (1);
    		n--;
		}
    }
    if(q == 0) {
    	puts(Rus("Процесс добавлен"));
		v_call++;    	
	}
	else {
		puts(Rus("Процесс добавлен с замещением"));	
		v_call++; 
	}
}

void delete_process(string* processes,int* numbers,int &size1, int size, char* memory[]) {
	string m;
    printf(Rus("Введите имя процесса, который хотите удалить: "));
    fflush(stdin);
    getline(cin, m);
	int k = 0;

	for(int i = 0; i < size; i++) {
        if(processes[i] == m && numbers[i] != 0)
        {
            processes[i] = "";
            size1 = size1 + 1;
            numbers[i] = 0;
            free(memory[i]);
            k++; 
        }
    }
    
    if(k == 0)
		printf(Rus("\nНазвание не действительно!"));
	else
    	printf(Rus("\nПамять освобождена по названию процесса."));
}

void table(string* processes,int* numbers,int size1, int size) {
	int i,j;
	const char *S;
	printf("%c", 218);
	for(i=0;i<16;i++)
		printf("%c", 196);  
	printf("%c", 194); 
	for(i=0;i<19;i++) 
		printf("%c", 196);  
	printf("%c", 194);
	for(i=0;i<25;i++) 
		printf("%c", 196); 
	printf("%c\n", 191);
	printf(Rus("%c Номер страницы %c Название процесса %c Количество занятых байт %c\n"), 179,179,179,179);
	for(int j=0; j<size; j++)
	{
		if(j!=size-1)
		{
			printf("%c", 195); 
			for(i=0;i<16;i++) 
				printf("%c", 196); 
			printf("%c", 197);
			for(i=0;i<19;i++) 
				printf("%c", 196); 
			printf("%c", 197); 
			for(i=0;i<25;i++) 
				printf("%c", 196); 
			printf("%c\n", 180);
			S = processes[j].c_str();
			printf(Rus("%c%8d        %c%10s         %c%15d          %c\n"), 179, j+1, 179, S, 179, numbers[j], 179);
		}
		else
		{
			printf("%c", 195);
			for(i=0;i<16;i++)
				printf("%c", 196); 
			printf("%c", 197);
			for(i=0;i<19;i++) 
				printf("%c", 196); 
			printf("%c", 197); 
			for(i=0;i<25;i++) 
				printf("%c", 196); 
			printf("%c\n", 180);
			S = processes[j].c_str();
			printf(Rus("%c%8d        %c%10s         %c%15d          %c\n"), 179, j+1, 179, S, 179, numbers[j], 179);
			
			printf("%c", 192); 
			for(i=0;i<16;i++) 
				printf("%c", 196); 
			printf("%c", 193);
			for(i=0;i<19;i++) 
				printf("%c", 196); 
			printf("%c", 193); 
			for(i=0;i<25;i++) 
				printf("%c", 196); 
			printf("%c", 217);
		}
	}
}

int main(){
	int size=0;
	int k, i;
	int check = 0;
	int call = 0, v_call = 0;
	int check_max = 0;
	
	printf(Rus("Введите объём памяти в байтах: "));
    while(size <= 0){
    	scanf("%d",&size);
		if(size <= 0)
			puts(Rus("Неверный объём памяти"));
    }
	
	int size1 = size;
	string processes[size];
	int numbers[size];	
	char* memory[size];
	
	for(int i = 0; i < size; i++) {
		processes[i] = "";
		numbers[i] = 0;
	}
	
	while(true)
    {
        menu();
        scanf("%d",&k);
        system("cls");
        switch(k)
    	{
		case 1:
			printf(Rus("Информация:\n"));
			printf(Rus("Объём памяти (в байтах): %d\n"),size);
			printf(Rus("Объём свободной памяти (в байтах): %d\n"),size1);
			
			check_max = 0;
			for(i = size - 1; i >= 0; i--)
		    {
		    	if(processes[i] == "" && numbers[i] == 0)
		    	{
		    		check++;
				}else if(processes[i] != "" && numbers[i] != 0){
					check = 0;			
				}
				if(check_max < check)
					check_max = check;
		    }
			
			printf(Rus("Размер наибольшего свободного блока (в байтах): %d\n"),check_max);
			printf(Rus("Получено запросов: %d\n"),call);
			printf(Rus("Выполнено запросов: %d\n"),v_call);
			break;
		case 2:
			add_proc(processes, numbers, size1, size, memory, v_call);
			call++;
			break;
		case 3:
			delete_process(processes, numbers, size1, size, memory);
			break;
		case 4:
			table(processes, numbers, size1, size);
			break;
		case 5:
			exit(0);
			break;
		default:
			puts(Rus("Выбран неправильный пункт меню!"));
	   }
	   printf("\n");
    }
    
    return(0);
}
