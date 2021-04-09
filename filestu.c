#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

void insert(FILE *fp);
void del(FILE *fp);
void modify(FILE *fp);
void display(FILE *fp);
int search(FILE *fp, char *name);
void list(FILE *fp);

struct
{
    char name[80];
    char id[50];
    long int rollno;

}student;

int main(void)
{
    int choice;
    FILE *fp;
    fp = fopen("studentrecord1", "rb+");
    if(fp==NULL)
    {
        fp = fopen("studentrecord1", "wb+");
        if(fp==NULL)
        {
            puts("Error in opening file\n");
            exit(1);
        }
    }
    while(1)
    {
        printf("1:Insert a new record\n");
        printf("2:Delete a record\n");
        printf("3:Display record of a student\n");
        printf("4:Modify an existing student\n");
        printf("5:List of all student\n");
        printf("6:Exit\n");
        printf("Enter your choice: \n");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            insert(fp);
            break;
        case 2:
            del(fp);
            break;
        case 3:
            display(fp);
            break;
        case 4:
            modify(fp);
            break;
        case 5:
            list(fp);
            break;
        case 6:
            fclose(fp);
            exit(1);
        default:
            printf("Wrong choice\n");
        }//End of switch//
    }//End of while//
}//End of main()//

void insert(FILE *fp)
{
    fseek(fp,0,2);
    fflush(stdin);
    printf("Name: \n");
    gets(student.name);
    printf("ID: \n");
    scanf("%s",student.id);
    printf("Roll No: \n");
    scanf("%lld",&student.rollno);
    fwrite(&student,sizeof(student),1,fp);
}//End of insert//

void del(FILE *fp)
{
    FILE *fptmp;
    char name[50];
    printf("Enter the name of student to be deleted from database: \n");
    gets(name);

    if(search(fp,name)==0)
        return;
    fptmp = fopen("tempfile","wb+");
    rewind(fp);
    while(fread(&student,sizeof(student),1,fp) == 1)
    {
        if(strcmp(name,student.name) != 0)
            fwrite(&student,sizeof(student),1,fptmp);
    }
    fclose(fp);
    fclose(fptmp);
    remove("studentrecord1");
    rename("tempfile1","studentrecord1");
    printf("\nRecord deleted..........\n\n");
    fp=fopen("studentrecord1", "rb+");
}

void modify(FILE *fp)
{
    char name[50];
    long long size=sizeof(student);
    printf("Enter the name of the student to be modified  : ");
    fflush(stdin);
    gets(name);
    if(search(fp,name) == 1)
    {
        printf("Enter new data.....\n\n");
        printf("Name: \n");
        fflush(stdin);
        gets(student.name);
        printf("ID: \n");
        scanf("%s",student.id);
        printf("Roll No: \n");
        scanf("%lld",student.rollno);
        fseek(fp,-size,1);
        fwrite(&student,sizeof(student),1,fp);
        printf("\nRecord successfully modified\n\n");
    }
}

void display(FILE *fp)
{
    char name[50];
    printf("Enter the name of student : \n");
    gets(name);
    if(search(fp,name) == 1)
    {
        printf("\nName\t%s\n",student.name);
        printf("ID\t%s\n",student.id);
        printf("Roll No\t%d\n\n",student.rollno);
    }
}

int search(FILE *fp, char *name)
{
    unsigned flag=0;
    rewind(fp);
    while(fread(&student, sizeof(student),1,fp)==1)
    {
        if(strcmp(name,student.name)==0)
        {
            flag=1;
            break;
        }
    }
    if(flag == 0)
        printf("\nName not found in file\n\n");
    return flag;
}

void list(FILE *fp)
{
    rewind(fp);
    printf("\nName\t\tID\t\t\tRoll No\n\n");
    while(fread(&student, sizeof(student),1,fp)==1)
    {
        printf("%s\t\t",student.name);
        printf("%s\t\t",student.id);
        printf("%d\n",student.rollno);
    }
    printf("\n");
}
