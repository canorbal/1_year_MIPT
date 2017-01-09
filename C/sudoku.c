#include <stdio.h>

void Input(int *a);
void enter(int *a);
void delet(int* a, int* array, int i, int j);
int check(int* a);
int posibility(int* array);

int A[9][9];

int main(int argc, const char * argv[])
{
    int a[9][9];
    int i,j;

    Input(A);  //ввод двумерного массива
    for (i=0; i<9; i++)
    {
        for (j=0; j<9; j++)
        {
            a[i][j]=A[i][j];
        }
    }
    
    enter(a);
    fprintf(stdout, "\n");
    for (i=0; i<9; i++)
    {
        for (j=0; j<9; j++)
        {
            fprintf(stdout, "%d ", A[i][j]);
        }
        fprintf(stdout, "\n");
    }
    return 0;
}


void Input(int* a)
{
    int i,j;
    for (i=0; i<9; i++)
    {
        for (j=0; j<9; j++)
        {
            if(fscanf(stdin, "%d", &a[i*9+j])!=1)
            {
                fprintf(stdout, "Wrong input");
            }
        }
    }
}

void enter(int* a)
{
    int i=0;
    int j=0;
    
    static int count_of_enter=0;
    count_of_enter++;
    
    if (count_of_enter==19)
    {
        int adfasdfasdf=0;
    }
   
    int end=check(a);  //проверка заполнен ли
    if (end==1)
    {
        //A - глобальный массив - переприсваеваем с локального d[][] и выходим из всех рекурсий
        int i;
        int j;
        for (i=0; i<9; i++)
        {
            for (j=0; j<9; j++)
            {
                A[i][j]=a[i*9+j];
            }
        }
        return ;
    }    
    int k=0;
    int array[81][9];  //для числа во 2-ой строке третий слева array[11][]
    for (i=0; i<9; i++)
    {
        for (j=0; j<9; j++)
        {
            if (a[i*9+j])
            {
                int k;
                for (k=0; k<9; k++)
                {
                    array[i*9+j][k]=-1;
                }
            }
            else
            {
                for (k=1; k<=9; k++)
                {
                    array[i*9+j][k-1]=k;
                }
            }
        }
    }
    
    for (i=0; i<9; i++)  //удаление уже стоящих символов из массива возможных по строкам
    {
        for (j=0; j<9; j++)
        {
            if (a[i*9+j])
            {
                int k=0;
                for (k=0; k<9; k++)
                {
                    array[i*9+k][a[i*9+j]-1]=-1;
                }
            }
        }
    }
    
    for (j=0; j<9; j++) //удаление уже стоящих символов из массива возможных по столбцам
    {
        for (i=0; i<9; i++)
        {
            if (a[i*9+j])
            {
                int k=0;
                for (k=0; k<9; k++)
                {
                    array[k*9+j][a[i*9+j]-1]=-1;
                }
            }
        }
    }
    
    delet(a, array, 0, 0);
    delet(a, array, 0, 3);
    delet(a, array, 0, 6);
    delet(a, array, 3, 0);
    delet(a, array, 3, 3);
    delet(a, array, 3, 6);
    delet(a, array, 6, 0);
    delet(a, array, 6, 3);
    delet(a, array, 6, 6);
    
    //проверка на возможность заполнения ////
    int flag_possible=1;
    int count=0;
    
    for (i=0; i<81; i++)
    {
        int x=0;
        if (a[i])
        {
            continue;
        }
        for (j=0; j<9; j++)
        {
            if (array[i][j]==-1)
            {
                x++;
            }
        }
        if (x==9)
        {
            flag_possible=0;
        }
        if (flag_possible==0)
        {
            break;
        }
    }
    
    if (flag_possible==0)
    {
        //fprintf(stdout,  "\n ^ невозможно заполнять массив в ячейке %d \n", i);
        if (check(a))
        {
            int i;
            int j;
            for (i=0; i<9; i++)
            {
                for (j=0; j<9; j++)
                {
                    A[i][j]=a[i*9+j];
                }
            }
            return ;
        }
        
        return;
    }
    ///  закончилась проверка на возможность заполнения
    
    for (i=0; i<9; i++)  //удаление уже стоящих символов из массива возможных по строкам
    {
        for (j=0; j<9; j++)
        {
            if (a[i*9+j])
            {
                int k=0;
                for (k=0; k<9; k++)
                {
                    array[i*9+k][a[i*9+j]-1]=-1;
                }
            }
        }
    }
    
    for (j=0; j<9; j++) //удаление уже стоящих символов из массива возможных по столбцам
    {
        for (i=0; i<9; i++)
        {
            if (a[i*9+j])
            {
                int k=0;
                for (k=0; k<9; k++)
                {
                    array[k*9+j][a[i*9+j]-1]=-1;
                }
            }
        }
    }
    
    delet(a, array, 0, 0);
    delet(a, array, 0, 3);
    delet(a, array, 0, 6);
    delet(a, array, 3, 0);
    delet(a, array, 3, 3);
    delet(a, array, 3, 6);
    delet(a, array, 6, 0);
    delet(a, array, 6, 3);
    delet(a, array, 6, 6);

    
    int flag=0;

    
    for (count=0; count<81; count++)
    {
        
        for (i=0; i<9; i++)  //удаление уже стоящих символов из массива возможных по строкам
        {
            for (j=0; j<9; j++)
            {
                if (a[i*9+j])
                {
                    int k=0;
                    for (k=0; k<9; k++)
                    {
                        array[i*9+k][a[i*9+j]-1]=-1;
                    }
                }
            }
        }
        
        for (j=0; j<9; j++) //удаление уже стоящих символов из массива возможных по столбцам
        {
            for (i=0; i<9; i++)
            {
                if (a[i*9+j])
                {
                    int k=0;
                    for (k=0; k<9; k++)
                    {
                        array[k*9+j][a[i*9+j]-1]=-1;
                    }
                }
            }
        }
        
        delet(a, array, 0, 0);
        delet(a, array, 0, 3);
        delet(a, array, 0, 6);
        delet(a, array, 3, 0);
        delet(a, array, 3, 3);
        delet(a, array, 3, 6);
        delet(a, array, 6, 0);
        delet(a, array, 6, 3);
        delet(a, array, 6, 6);

        
        int k;
        int variants_count=0;
        int tmp=0;
        
        for (k=0; k<9; k++)
        {
            if (array[count][k]!=0 && array[count][k]!=-1)
            {
                variants_count++;
                tmp=array[count][k];
            }
        }
        
        if (variants_count==1)
        {
            flag=1;
            //fprintf(stdout, "цифру %d в ячейку %d", tmp, count);
            a[count]=tmp;
            enter(a);
        }
    }
    
    if (flag==0)
    {
        int min_of_variants=10000;
        int number=0;
        for (count=0; count<81; count++)
        {
            int k;
            int variants_count=0;
            for (k=0; k<9; k++)
            {
                if (array[count][k]!=0 && array[count][k]!=-1)
                {
                    variants_count++;
                }
            }
            if (variants_count<min_of_variants && variants_count!=0)
            {
                min_of_variants=variants_count;
                number=count;
            }
        }

        
        if (min_of_variants==10000)
        {
            return;
        }
        for (i=0; i<9; i++)
        {
            if (array[number][i]!=0 && array[number][i]!=-1)
            {
                int b[9][9];
                int x,z;
                for (x=0; x<9; x++)
                {
                    for (z=0; z<9; z++)
                    {
                        b[x][z]=a[x*9+z];
                    }
                }
                b[number/9][number%9]=array[number][i]; //b
                //fprintf(stdout, "несколько вариантов: цифра %d в ячейку %d", array[number][i], number);
                enter(b); // b

            }
        }
    }
    
    for (i=0; i<9; i++)  //удаление уже стоящих символов из массива возможных по строкам
    {
        for (j=0; j<9; j++)
        {
            if (a[i*9+j])
            {
                int k=0;
                for (k=0; k<9; k++)
                {
                    array[i*9+k][a[i*9+j]-1]=-1;
                }
            }
        }
    }
    
    for (j=0; j<9; j++) //удаление уже стоящих символов из массива возможных по столбцам
    {
        for (i=0; i<9; i++)
        {
            if (a[i*9+j])
            {
                int k=0;
                for (k=0; k<9; k++)
                {
                    array[k*9+j][a[i*9+j]-1]=-1;
                }
            }
        }
    }
    
    delet(a, array, 0, 0);
    delet(a, array, 0, 3);
    delet(a, array, 0, 6);
    delet(a, array, 3, 0);
    delet(a, array, 3, 3);
    delet(a, array, 3, 6);
    delet(a, array, 6, 0);
    delet(a, array, 6, 3);
    delet(a, array, 6, 6);
    
    
    
}

void delet(int* a, int* array, int i, int j)
{
    int boolean[9]={1,1,1,1,1,1,1,1,1};
    int CountI;
    int CountJ;
    for (CountI=i; CountI<i+3; CountI++)
    {
        for (CountJ=j; CountJ<j+3; CountJ++)
        {
            if (a[CountI*9+CountJ])
            {
                boolean[a[CountI*9+CountJ]-1]=0;
            }
        }
    }
    
    /*int count=0;
     for (count=0; count<10*9; count++)
     {
     fprintf(stdout, "array[%d] = %d\n", count, array[count]);
     } */
    
    for (CountI=i; CountI<i+3; CountI++)
    {
        for (CountJ=j; CountJ<j+3; CountJ++)
        {
            int k;
            for (k=0; k<9; k++)
            {
                if (boolean[k]==0)
                {
                    array[(CountI*9+CountJ)*9+k]=-1;
                }
            }
        }
    }
    return;
}

int check(int* a)
{
    int j;
    int i;
    int x=1;
    for (i=0; i<9; i++)
    {
        for (j=0; j<9; j++)
        {
            if (a[i*9+j]==0)
            {
                x=0;
                break;
            }
        }
        if (x==0)
        {
            break;
        }
    }
    return x;
}
