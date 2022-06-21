#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <math.h>
#include <direct.h>
struct memBlock
{
    int next;
    bool isFree;
    bool isDir;
    bool isStart;
    char *data;
    char name[16];
    char path[256];
};

int col_file = 0;

char Jinfo[1000][100];
char Jname[1000][100];
int Jind = 0;
int j = 0;

char bufRus[256]; 
char* Rus(const char* text) 
{ 
    CharToOem(text, bufRus); 
    return bufRus; 
}

int scanInt(const char* dispStr)
{
    int bufInt, check;
    do
    {
        printf(Rus(dispStr));
        fflush(stdin);
        check = scanf("%d", &bufInt);
        fflush(stdin);
        if ( check != 1 || bufInt <=0)
        {
            printf(Rus("Ошибка. Введите целое число не равное нулю\n"));
        }
    }
    while ( check != 1 || bufInt <= 0);
    return bufInt;
}

memBlock* freeMem(memBlock *memory, int total_blocks)
{
    for (int i = 0; i < total_blocks; i++)
    {
        delete[] memory[i].data;
    }
    delete[] memory;
    return memory;
}

int menu(char *path)
{
    int key;

    system("cls");
    printf("----------------------------------\n");
    printf(Rus("|              МЕНЮ              |\n"));
    printf("----------------------------------\n");
    printf(Rus("| 1) Создать файл                |\n"));
    printf(Rus("| 2) Редактировать текстовый файл|\n"));
    printf(Rus("| 3) Удалить файл                |\n"));
    printf(Rus("| 4) Найти файл                  |\n"));
    printf(Rus("| 5) Перейти в каталог           |\n"));
    printf(Rus("| 6) Выйти из каталога           |\n"));
    printf(Rus("| 7) Информация                  |\n"));
    printf(Rus("| 8) Загрузить файл с диска      |\n"));
    printf(Rus("| 9) Создать структуру на диске  |\n"));
    printf(Rus("| 10)Форматировать               |\n"));
    printf(Rus("| 11)Рекластeризация             |\n"));
    printf(Rus("| 12)Журнал                      |\n"));
    printf(Rus("| 13)Выход                       |\n"));
    printf("----------------------------------\n");
    printf(Rus(" Путь: %s  \n"),path);
    printf("----------------------------------\n");

    fflush(stdin);
    scanf("%d", &key);
    return key;
}

memBlock* format(memBlock *memory, int *total_mem, int *total_blocks, int *block_size, int *free_size, char* path)
{
    int i, j;
    bool flag;

	system("cls");
    do
    {
        flag = false;
        
        *total_mem = scanInt("Введите количество памяти (до 10001): ");
        *total_blocks = scanInt("Введите количество блоков: ");
        
        if ( *total_mem < 1 || *total_blocks < 1 || *total_mem % *total_blocks != 0 || *total_mem >10000)
        {
            printf(Rus("Некорректное количество памяти/блоков.\n"));
            flag = true;
        }
    }
    while ( flag );

    path[0] = '\\';
    for (i = 1; i < 256; i++)
    {
        path[i] = '\0';
    }
    *block_size = *total_mem / *total_blocks;
    *free_size = *block_size * *total_blocks;
    memory = new memBlock[*total_blocks];

    for (i = 0; i < *total_blocks; i++)
    {
        memory[i].data = new char[*block_size];
        memory[i].isFree = true;
        memory[i].next = -2;
        memory[i].isDir = false;
        memory[i].isStart = false;
        for (j = 0; j < 16; j++)
        {
            memory[i].name[j] = '\0';
        }
        for (j = 0; j < 256; j++)
        {
            memory[i].path[j] = '\0';
        }
    }

    return memory;
}

memBlock* reclustorization(memBlock *memory, int *total_mem, int *total_blocks, int *block_size, int *free_size, char* path)
{
    memBlock *new_memory;
    int i, j, k, l, total_files, new_total_blocks, new_block_size, new_free_size, index, new_index, buf, max;
    bool flag;

	system("cls");
	strcpy(Jinfo[Jind], Rus("Была проведена рекластеризация"));
	Jind++;
    do
    {
        flag = false;

        new_total_blocks = scanInt("Введите новое количество блоков: ");

        if ( new_total_blocks < 1 || *total_mem % new_total_blocks != 0)
        {
            printf(Rus("Некорректное количество блоков.\n"));
            flag = true;
        } else if (new_total_blocks < col_file) {
        	puts(Rus("Число файлов не может быть больше числа блоков"));
        	flag = true;
		}
    }
    while ( flag );
    
    if ( new_total_blocks < *total_blocks )
    {
        for (i = 0, total_files = 0, max = 0; i < *total_blocks; i++)
        {
            if ( memory[i].isStart )
            {
                total_files++;
                index = i;
                buf = 1;
                while ( memory[index].next >= 0 )
                {
                    index = memory[index].next;
                    buf++;
                }
                if ( buf > max )
                {
                    max = buf;
                }
            }
        }
        if ( max >= floor( (float)*total_blocks / (float)total_files ) )
        {
            printf(Rus("С данным количеством блоков рекластeризацию без потери данных провести невозможно.\n"));
            system("pause");
            return memory;
        }
    }

    path[0] = '\\';
    for (i = 1; i < 256; i++)
    {
        path[i] = '\0';
    }
    new_block_size = *total_mem / new_total_blocks;
    new_free_size = new_block_size * new_total_blocks;
    new_memory = new memBlock[new_total_blocks];

    for (i = 0; i < new_total_blocks; i++)
    {
        new_memory[i].data = new char[*block_size];
        new_memory[i].isFree = true;
        new_memory[i].next = -2;
        new_memory[i].isDir = false;
        new_memory[i].isStart = false;
        for (j = 0; j < 16; j++)
        {
            new_memory[i].name[j] = '\0';
        }
        for (j = 0; j < 256; j++)
        {
            new_memory[i].path[j] = '\0';
        }
    }

    for (i = 0; i < *total_blocks; i++)
    {
        if ( !memory[i].isStart )
        {
            continue;
        }

        if ( memory[i].isDir )
        {
            for (j = 0; j < new_total_blocks; j++)
            {
                if ( new_memory[j].isFree )
                {
                    break;
                }
            }
            index = j;

            new_memory[index].isFree = false;
            new_memory[index].next = -1;
            new_memory[index].isDir = true;
            new_memory[index].isStart = true;
            for (j = 0; j < 16; j++)
            {
                new_memory[index].name[j] = memory[i].name[j];
            }
            for (j = 0; j < 256; j++)
            {
                new_memory[index].path[j] = memory[i].path[j];
            }

            continue;
        }

        for (new_index = 0; new_index < new_total_blocks; new_index++)
        {
            if ( new_memory[new_index].isFree )
            {
                break;
            }
        }
        new_memory[new_index].isFree = false;
        new_memory[new_index].next = -1;
        new_memory[new_index].isDir = false;
        new_memory[new_index].isStart = true;
        for (j = 0; j < 16; j++)
        {
            new_memory[new_index].name[j] = memory[i].name[j];
        }
        for (j = 0; j < 256; j++)
        {
            new_memory[new_index].path[j] = memory[i].path[j];
        }

        index = i;
        k = 0;
        while ( index >= 0 )
        {
            for (j = 0; j < *block_size; j++)
            {
                new_memory[new_index].data[k] = memory[index].data[j];

                if ( memory[index].data[j] == '\0' )
                {
                    break;
                }

                k++;
                if ( k >= new_block_size )
                {
                    k = 0;
                    buf = new_index;
                    for (new_index = 0; new_index < new_total_blocks; new_index++)
                    {
                        if ( new_memory[new_index].isFree )
                        {
                            break;
                        }
                    }
                    new_memory[new_index].isFree = false;
                    new_memory[new_index].next = -1;
                    new_memory[new_index].isDir = false;
                    new_memory[new_index].isStart = false;
                    for (l = 0; l < 16; l++)
                    {
                        new_memory[new_index].name[l] = memory[i].name[l];
                    }
                    for (l = 0; l < 256; l++)
                    {
                        new_memory[new_index].path[l] = memory[i].path[l];
                    }
                    new_memory[buf].next = new_index;
                }
            }

            index = memory[index].next;
        }
    }

    for (i = 0, new_free_size = 0; i < new_total_blocks; i++)
    {
        if ( new_memory[i].isFree )
        {
            new_free_size += new_block_size;
        }
    }

    memory = freeMem(memory, *total_blocks);
    *total_blocks = new_total_blocks;
    *block_size = new_block_size;
    *free_size = new_free_size;
    return new_memory;
}

void delBlock(memBlock *memory, int index, int *free_size, int block_size)
{
    int i;

	if(col_file != 0)
			col_file--;

    *free_size = *free_size + block_size;
    memory[index].isDir = false;
    memory[index].isStart = false;
    memory[index].isFree = true;
    memory[index].next = -2;
    for (i = 0; i < 16; i++)
    {
        memory[index].name[i] = '\0';
    }
    for (i = 0; i < 256; i++)
    {
        memory[index].path[i] = '\0';
    }
}

int deleteFile(memBlock *memory, int total_blocks, char *path, int *free_size, int block_size)
{
    int i, j, index;
    char name[16];

    system("cls");
    printf(Rus("Введите имя файла: "));
    fflush(stdin);
    gets(name);

    for (i = 0, index = -2; i < total_blocks && index == -2; i++)
    {
        if ( strcmp(memory[i].path, path) == 0 && strcmp(memory[i].name, name) == 0 && memory[i].isStart )
        {
            index = i;
            strcpy(Jinfo[Jind],Rus("Был удалён файл/каталог"));
            strcpy(Jname[Jind], name);
			Jind++;
        }
    }
    if ( index == -2 )
    {
        printf(Rus("Файл с таким именем в директории не найден.\n"));
        strcpy(Jinfo[Jind],Rus("Попытка удаления несуществующего файла"));
		strcpy(Jname[Jind],name);
		Jind++;
        system("pause");
        return 1;
    }

    while ( index >= 0 )
    {
        i = index;
        index = memory[i].next;
        delBlock(memory, i, free_size, block_size);
    }

    return 0;
}

int createFile(memBlock *memory, int total_blocks, int block_size, int *free_size, char *path)
{
    int i, index;
    char check;
    char name[16];
    bool flag;

    system("cls");

    for (i = 0, flag = true; i < total_blocks && flag; i++)
    {
        if ( memory[i].isFree )
        {
            index = i;
            flag = false;
        }
    }
    if ( flag )
    {
        printf(Rus("Для создания файла нет свободных блоков памяти.\n"));
        system("pause");
        return 1;
    }
    
    printf(Rus("Введите тип файла (d - каталог / другое - текстовый файл): "));
    fflush(stdin);
    scanf("%c", &check);
    printf(Rus("Введите имя файла (до 16 символов): "));
    fflush(stdin);
    gets(name);
    i = 0;
    while ( name[i] != '\0' && i < 16)
    {
        if ( name[i] == '\\' || name[i] == '/' || name[i] == ':' || name[i] == '*' || name[i] == '?' || name[i] == '.' || name[i] == '\"' || name[i] == '<' || name[i] == '>' || name[i] == '|' )
        {
            printf(Rus("В имени файла нельзя использовать символы \\, /, :, *, ?, ., \", <, >, |.\n"));
            system("pause");
            return 1;
        }
        i++;
    }

    for (i = 0, flag = true; i < total_blocks && flag; i++)
    {
        if ( strcmp(memory[i].path, path) == 0 && strcmp(memory[i].name, name) == 0 && memory[i].isStart )
        {
            flag = false;
        }
    }
    if ( !flag )
    {
        printf(Rus("Файл с таким именем уже существует.\n"));
        system("pause");
        return 1;
    }

    *free_size = *free_size - block_size;
    for (i = 0; i < 16; i++)
    {
        memory[index].name[i] = name[i];
    }
    for (i = 0; i < 256; i++)
    {
        memory[index].path[i] = path[i];
    }
    for (i = 0; i < block_size; i++)
    {
        memory[index].data[i] = '\0';
    }
    memory[index].isDir = ( check == 'd' ) ? true : false;
    memory[index].next = -1;
    memory[index].isFree = false;
    memory[index].isStart = true;
	
	if( memory[index].isDir ){
		strcpy(Jinfo[Jind],Rus("Был создан каталог"));
	    strcpy(Jname[Jind], name);
		Jind++;
		col_file++;
	} else {
		strcpy(Jinfo[Jind],Rus("Был создан файл"));
    	strcpy(Jname[Jind], name);
		Jind++;
		col_file++;
	}

    return 0;
}

void searchFile(memBlock *memory, int total_blocks)
{
    int i;
    char name[16];

    system("cls");
    printf(Rus("Введите имя файла: "));
    fflush(stdin);
    gets(name);

	strcpy(Jinfo[Jind],Rus("Поиск файла"));
    strcpy(Jname[Jind], name);
	Jind++;

    printf(Rus("Список найденных файлов:\n"));
    for (i = 0; i < total_blocks; i++)
    {
        if ( memory[i].isStart && strcmp(memory[i].name, name) == 0 )
        {
            printf("%s%s\n", memory[i].path, memory[i].name);
        }
    }
    system("pause");
}

int editFile(memBlock *memory, int total_blocks, int block_size, int *free_size, char *path)
{
    int i, j, k, l, index;
    char name[16];
    char str[256];

    system("cls");
    printf(Rus("Введите имя файла: "));
    fflush(stdin);
    gets(name);

	strcpy(Jinfo[Jind],Rus("Запрос на редактирование файла"));
    strcpy(Jname[Jind], name);
	Jind++;

    for (i = 0, index = -2; i < total_blocks && index == -2; i++)
    {
        if ( strcmp(memory[i].path, path) == 0 && strcmp(memory[i].name, name) == 0 && memory[i].isStart && !memory[i].isDir )
        {
            index = i;
        }
    }
    if ( index == -2 )
    {
        printf(Rus("Файл с таким именем в директории не найден.\n"));
        system("pause");
        return 1;
    }

    printf(Rus("Старый текст файла:\n%s"), strncpy(str, memory[index].data, block_size));
    i = memory[index].next;
    memory[index].next = -1;
    while ( i >= 0 )
    {
        j = i;
        printf("%s", strncpy(str, memory[j].data, block_size));
        i = memory[j].next;
        delBlock(memory, j, free_size, block_size);
    }
    
    printf(Rus("\nВведите новый текст файла:\n"));
    fflush(stdin);
    gets(str);

    l = strlen(str) + 1;

    if ( l > *free_size + block_size )
    {
        printf(Rus("Ошибка. Недостаточно свободного пространства для записи строки.\n"));
        system("pause");
        return 1;
    }
    for (i = 0, l = ceil((float) l / (float) block_size); i < l; i++)
    {
        strncpy(memory[index].data, &(str[i*block_size]), block_size);

        for (j = 0; j < total_blocks; j++)
        {
            if ( memory[j].isFree )
            {
                break;
            }
        }

        if ( i + 1 == l )
        {
            break;
        }
        
        *free_size = *free_size - block_size;
        for (k = 0; k < 16; k++)
        {
            memory[j].name[k] = memory[index].name[k];
        }
        for (k = 0; k < 256; k++)
        {
            memory[j].path[k] = memory[index].path[k];
        }
        for (k = 0; k < block_size; k++)
        {
            memory[j].data[k] = '\0';
        }
        memory[j].next = -1;
        memory[j].isDir = false;
        memory[j].isFree = false;
        memory[j].isStart = false;
        memory[index].next = j;
        index = j;
    }

    return 0;
}

int toDir(memBlock *memory, int total_blocks, char *path)
{
    int i, index;
    char name[16];

    system("cls");
    printf(Rus("Введите имя директории: "));
    fflush(stdin);
    gets(name);
	
	strcpy(Jinfo[Jind],Rus("Запрос перехода в каталог"));
    strcpy(Jname[Jind], name);
	Jind++;
	
    for (i = 0, index = -2; i < total_blocks && index == -2; i++)
    {
        if ( strcmp(memory[i].path, path) == 0 && strcmp(memory[i].name, name) == 0 && memory[i].isStart && memory[i].isDir )
        {
            index = i;
        }
    }
    if ( index == -2 )
    {
        printf(Rus("Директория с таким именем не найдена.\n"));
        system("pause");
        return 1;
    }

    strcpy(&(path[strlen(path)]), memory[index].name);
    path[strlen(path)] = '\\';

    return 0;
}

void exitDir(char *path)
{
    int i;

	strcpy(Jinfo[Jind],Rus("Запрос выхода из каталога"));
	Jind++;

    i = strlen(path) - 1;
    if ( i > 0 )
    {
        path[i--] = '\0';
        while( path[i] != '\\' )
        {
            path[i--] = '\0';
        }
    }
}

void showInfo(memBlock *memory, int total_mem, int total_blocks, int block_size, int free_size)
{
    int i;
    char str[256];
    char buf[5];

	strcpy(Jinfo[Jind],Rus("Была показана информация о системе"));
	Jind++;

    system("cls");
    printf(Rus("Всего памяти: %d\nСвободно памяти: %d\nВсего блоков: %d\nСвободно блоков: %d\nПамяти в блоке: %d\n"), total_mem, free_size, total_blocks, free_size/block_size, block_size);
    printf("\xC9\xC4\xC4\xC4\xC4\xC4\xCB\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xCB\xC4\xC4\xC4\xC4\xC4\xBB\n\xB3  N  \xB3           ");
    printf(Rus("Имя"));
    printf("           \xB3");
    printf(Rus(" Тип "));
    printf("\xB3\n");
    for (i = 0; i < total_blocks; i++)
    {
        strcpy(str, memory[i].path);
        strcpy(&(str[strlen(str)]), memory[i].name);
        printf("\xCC\xC4\xC4\xC4\xC4\xC4\xCE\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xCE\xC4\xC4\xC4\xC4\xC4\xB9\n\xB3%5d\xB3%-25s\xB3 %c   \xB3\n", i+1, str, memory[i].isFree ? ' ' : memory[i].isDir ? 'D' : 'F');
    }
    printf("\xC8\xC4\xC4\xC4\xC4\xC4\xCA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xCA\xC4\xC4\xC4\xC4\xC4\xBC\n");
    system("pause");
}

int createStruct(memBlock *memory, int total_blocks, int block_size)
{
    int i, j, index, dlen, errs;
    char** dirs;
    char path[32], fpath[304], str[256];
    FILE* f;
    
    system("cls");
    printf(Rus("Введите путь и название директории, где будет создана структура (D:\\test): "));
    fflush(stdin);
    gets(path);
    
    strcpy(Jinfo[Jind],Rus("Запрос на создание структуры по адресу:"));
    strcpy(Jname[Jind], path);
	Jind++;
    
    if ( path[0] == '\0' )
    {
        strcpy(path, "D:\\test");
    }

    if ( mkdir(path) )
    {
        printf(Rus("Не удалось создать каталог %s\n"), path);
        system("pause");
        return 1;
    }

    for (i = 0, dlen = 0; i < total_blocks; i++)
    {
        if ( memory[i].isDir && memory[i].isStart )
        {
            dlen++;
        }
    }

    dirs = new char*[dlen];
    for (i = 0; i < dlen; i++)
    {
        dirs[i] = new char[304];
    }

    for (i = 0, dlen = 0; i < total_blocks; i++)
    {
        if ( memory[i].isDir && memory[i].isStart )
        {
            strcpy(dirs[dlen], path);
            strcpy(&(dirs[dlen][strlen(dirs[dlen])]), memory[i].path);
            strcpy(&(dirs[dlen][strlen(dirs[dlen])]), memory[i].name);
            dlen++;
        }
    }

    do
    {
        for (i = 0, errs = 0; i < dlen; i++)
        {
            errs += mkdir(dirs[i]);
        }
    }
    while ( dlen + errs );

    for (i = 0; i < total_blocks; i++)
    {
        if ( !memory[i].isDir && memory[i].isStart )
        {
            strcpy(fpath, path);
            strcpy(&(fpath[strlen(fpath)]), memory[i].path);
            strcpy(&(fpath[strlen(fpath)]), memory[i].name);
            strcpy(&(fpath[strlen(fpath)]), ".txt");
            f = fopen(fpath, "w");
            index = i;
            str[block_size] = '\0';
            while ( index >= 0 )
            {
                fprintf(f, "%s", strncpy(str, memory[index].data, block_size));
                index = memory[index].next;
            }
            fclose(f);
        }
    }
    system("pause");

    for (i = 0; i < dlen; i++)
    {
        delete[] dirs[i];
    }
    delete[] dirs;
    return 0;
}

int loadFromDisc(memBlock *memory, int total_blocks, int block_size, int *free_size, char *path)
{
    FILE* f;
    char fpath[32];
    char name[16];
    char *data;
    int i, j, k, fsize, index;
    bool flag;

    system("cls");
    printf(Rus("Введите путь к текстовому файлу, который нужно загрузить (D:\\test.txt): "));
    fflush(stdin);
    gets(fpath);
    
    strcpy(Jinfo[Jind],Rus("Запрос на загрузку файла с диска"));
    strcpy(Jname[Jind], fpath);
	Jind++;
    
    if ( fpath[0] == '\0' )
    {
        strcpy(fpath, "D:\\test.txt");
    }

    f = fopen(fpath, "r");

    if ( !f )
    {
        printf(Rus("Не удалось открыть файл %s.\n"), fpath);
        system("pause");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    fsize = ftell(f) + 1;
    fseek(f, 0, SEEK_SET);
    if ( fsize > *free_size )
    {
        printf(Rus("Файл слишком большой.\n"));
        system("pause");
        return 1;
    }

    printf(Rus("Придумайте, как будет называться файл в виртуальном файле: "));
    fflush(stdin);
    gets(name);
    i = 0;
    while ( name[i] != '\0' && i < 16 )
    {
        if ( name[i] == '\\' || name[i] == '/' || name[i] == ':' || name[i] == '*' || name[i] == '?' || name[i] == '.' || name[i] == '\"' || name[i] == '<' || name[i] == '>' || name[i] == '|' )
        {
            printf(Rus("В имени файла нельзя использовать символы \\, /, :, *, ?, ., \", <, >, |.\n"));
            system("pause");
            return 1;
        }
        i++;
    }
    for (i = 0, flag = true; i < total_blocks && flag; i++)
    {
        if ( strcmp(memory[i].path, path) == 0 && strcmp(memory[i].name, name) == 0 && memory[i].isStart )
        {
            flag = false;
        }
    }
    if ( !flag )
    {
        printf(Rus("Файл с таким именем уже существует.\n"));
        system("pause");
        return 1;
    }
    
    data = new char[fsize];
    fread(data, sizeof(char), fsize-1, f);
    data[fsize-1] = '\0';

    for (index = 0; index < total_blocks; index++)
    {
        if ( memory[index].isFree )
        {
            break;
        }
    }
    *free_size = *free_size - block_size;
    for (k = 0; k < 16; k++)
    {
        memory[index].name[k] = name[k];
    }
    for (k = 0; k < 256; k++)
    {
        memory[index].path[k] = path[k];
    }
    for (k = 0; k < block_size; k++)
    {
        memory[index].data[k] = '\0';
    }
    memory[index].next = -1;
    memory[index].isDir = false;
    memory[index].isFree = false;
    memory[index].isStart = true;

    for (i = 0, fsize = ceil((float) fsize / (float) block_size); i < fsize; i++)
    {
        strncpy(memory[index].data, &(data[i*block_size]), block_size);

        for (j = 0; j < total_blocks; j++)
        {
            if ( memory[j].isFree )
            {
                break;
            }
        }

        if ( i + 1 == fsize )
        {
            break;
        }
        
        *free_size = *free_size - block_size;
        for (k = 0; k < 16; k++)
        {
            memory[j].name[k] = name[k];
        }
        for (k = 0; k < 256; k++)
        {
            memory[j].path[k] = path[k];
        }
        for (k = 0; k < block_size; k++)
        {
            memory[j].data[k] = '\0';
        }
        memory[j].next = -1;
        memory[j].isDir = false;
        memory[j].isFree = false;
        memory[j].isStart = false;
        memory[index].next = j;
        index = j;
    }

    fclose(f);
    delete[] data;
    return 0;
}

int main()
{
	memBlock *memory;
    int key, total_mem, total_blocks, block_size, free_size;
    char path[256];
    
    memory = format(memory, &total_mem, &total_blocks, &block_size, &free_size, path);

    do
    {
        key = menu(path);

        switch (key)
        {
        case 1:
            // Создать файл, запретить ввод неподходящих символов
            createFile(memory, total_blocks, block_size, &free_size, path);
            break;
        case 2:
            // Редактировать текстовый файл
            editFile(memory, total_blocks, block_size, &free_size, path);
            break;
        case 3:
            // Удалить файл
            deleteFile(memory, total_blocks, path, &free_size, block_size);
            break;
        case 4:
            // Найти файл
            searchFile(memory, total_blocks);
            break;
        case 5:
            // Перейти в каталог
            toDir(memory, total_blocks, path);
            break;
        case 6:
            // Выйти из каталога
            exitDir(path);
            break;
        case 7:
            // Информация
            showInfo(memory, total_mem, total_blocks, block_size, free_size);
            break;
        case 8:
            // Загрузить файл с диска
            loadFromDisc(memory, total_blocks, block_size, &free_size, path);
            break;
        case 9:
            // Создать структуру на диске
            createStruct(memory, total_blocks, block_size);
            break;
        case 10:
            // Форматировать
            memory = freeMem(memory, total_blocks);
            memory = format(memory, &total_mem, &total_blocks, &block_size, &free_size, path);
            Jind = 0;
            col_file = 0;
            break;
        case 11:
            // Рекласторизация
            memory = reclustorization(memory, &total_mem, &total_blocks, &block_size, &free_size, path);
            break;
        case 12:
            // Вывод журнала
            system("cls");
            
            for(j = 0; j < Jind; j++){
            	printf(Rus("%d. %s %s\n"),j+1, Jinfo[j], Jname[j]);
			}
			
            system("pause");
            break;
        }
    }
    while ( key != 13 );
    
    freeMem(memory, total_blocks);
    return 0;
}
