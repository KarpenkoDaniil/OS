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

void add_proc(string *processes, int *numbers, char* memory[], int col_pages, int &size, int page_size, int &free_pages, int size1) {
	string m;
    printf(Rus("Введите имя процесса: "));
    fflush(stdin);
    getline(cin, m);
    int n;
    printf(Rus("Введите количество байт, нужных процессу: "));
    scanf("%d", &n);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int ind=0;
    int check = 0;
    
    for(int i = col_pages - 1; i >= 0; i--)
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
    
    if(check == 0 || n > size)        //// n > size   ???
    {
    	printf(Rus("\nНедостаточно памяти для размещения процесса.\n"));
    	
    	int k, ind, k_max=0;
		for(int i = col_pages - 1; i >= 0; i--){
			k=0;
			for(int j= col_pages - 1; j >= 0; j--){
			    if(processes[i] == processes[j] && processes[i] != "") {
			    	k++;
				}
			}
			if(k_max < k) {
				k_max = k;
				ind = i;
			}
		}
		
		printf("%d", k_max);
		
		for(int i = 0; i < col_pages; i++)
    	{
       		if(processes[i] == processes[ind])
    	    {
    	        processes[i] = "";
    	        numbers[i] = 0;
    	        free(memory[i]);
    	        free_pages++;
    	        size = size + page_size;
    	    }
    	}	
	}
	
	for(int i = ind; i >= 0; i++)
    {
    	if(processes[i] == "" && numbers[i] == 0)
    	{
            if(free_pages > 0) //Уменьшение количесвта свободных страниц на 1
    	        free_pages--;
    		processes[i] = m;
    		if(n > 1)
    		{
    			numbers[i] = page_size;
    			memory[i] = (char*) malloc (page_size);
    			size = size - page_size;
    		}
    		else
    		{
    			int l = n % page_size; //Оставшиеся байты для процесса
    			if(l == 0)
    				l = page_size;
    			numbers[i] = l;
    			size = size - page_size;
    			memory[i] = (char*) malloc (l);
    			printf(Rus("\nПроцесс успешно добавлен в память."));
    			return;
    		}
    		n--;
		}
    }
}

void delete_process(char* memory[], string *processes, int *numbers, int col_pages, int &size, int page_size, int &free_pages) {
	string m;
    printf(Rus("Введите имя процесса, который хотите удалить: "));
    fflush(stdin);
    getline(cin, m);
    
    int k = 0;
    
    for(int i = 0; i < col_pages; i++)
    {
        if(processes[i] == m && numbers[i] != 0)
        {
            processes[i] = "";
            numbers[i] = 0;
            free(memory[i]);
            free_pages++;
            size = size + page_size;
            k++; 
        }
    }
    
    if(k == 0)
		printf(Rus("\nНазвание не действительно!"));
	else
    	printf(Rus("\nПамять освобождена по названию процесса."));
}

void table(int col_pages, string *processes, int *numbers) {
	int i;
	//Шапка
	const char *S;
	printf("%c", 218);
	for(i=0;i<16;i++) printf("%c", 196);  printf("%c", 194); for(i=0;i<19;i++) printf("%c", 196);  printf("%c", 194);
	for(i=0;i<25;i++) printf("%c", 196); printf("%c\n", 191);
	printf(Rus("%c Номер страницы %c Название процесса %c Количество занятых байт %c\n"), 179,179,179,179);
	for(int j=0; j<col_pages; j++)
	{
		if(j!=col_pages-1)
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
	int size=0;//Общий размер памяти
	int k;//Вариант меню
    int page_size = 1; // Размер одной страницы
	
	printf(Rus("Введите объём памяти в байтах: "));
    while(size <= 0)
    	scanf("%d",&size);
	
	int col_pages = size; //Количество страниц
	int free_pages = size; //Количество свободных страниц
	int size1=size;
	
	string processes[size]; //Массив имен процессов
    int numbers[size]; //Массив количества байтов процессов
	
	for(int i = 0; i < size; i++) {
		processes[i] = "";
		numbers[i] = 0;
	}
    
    char* memory[size]; //Массив памяти для процесса
	
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
			break;
		case 2:
			add_proc(processes, numbers, memory, col_pages, size1, page_size, free_pages, size1);
			break;
		case 3:
			delete_process(memory, processes, numbers, col_pages, size1, page_size, free_pages);
			break;
		case 4:
			table(col_pages, processes, numbers);
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
