/*
githup repo link:

shehab mohamed ahmed moahmed        SEC:2 BN;33
john saber abdallah      SEC:1 BN:51
moustafa hisham mahmoud mohamed  SEC:4 BN:21

*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <time.h>


struct student {
    char std_name[30];
    int day;
    int std_id;
    int year;
    int month;
    int std_score;
    int index;
    struct student *next;
};

table_size=10;
struct student* hash_table_closed[10];
struct student* hash_table_open[10];
struct student* dummy;


void create_hash(){

    for(int i=0;i<table_size;i++){
        hash_table_open[i]=NULL;
        hash_table_closed[i]=NULL;
    }

}

struct student* insert(char *name,int id,int day,int month, int year,int score){

    struct student* insertion=malloc(sizeof(struct student));
    strcpy(insertion->std_name,name);
    insertion->std_id=id;
    insertion->day=day;
    insertion->month=month;
    insertion->year=year;
    insertion->std_score=score;
    insertion->next=NULL;
    return insertion;

}

//****************************************************************************************************************
//****************************************************************************************************************
//**************************************************open hashing**************************************************
//****************************************************************************************************************
//****************************************************************************************************************


int hash_func_name(char* key){

    long int value =0;
    int keylen=strlen(key);
    for(int i=0;i<keylen;i++){
        value=value+key[i];
    }
    value=value%table_size;
    return value;
}

void student_insert_open_hashing(char *name,int id,int day,int month, int year,int score){

    int index=hash_func_name(name);
    struct student* prev;
    struct student* insertion_entry=hash_table_open[index];
    if (insertion_entry==NULL){
        hash_table_open[index]=insert(name,id,day,month,year,score);
    }
    else{
        while(insertion_entry!=NULL){
            prev=insertion_entry;
            insertion_entry=prev->next;
        }
        prev->next=insert(name,id,day,month,year,score);

    }
}



struct student * student_search_open_hashing(char *name){

    int index=hash_func_name(name);
    struct student* search_entry=hash_table_open[index];
    if (search_entry==NULL){
        return NULL;
    }
    else{
        while(search_entry!=NULL){
            if (strcmp(search_entry->std_name,name)==0){
                return search_entry;
            }
            search_entry=search_entry->next;
        }
         return NULL;
    }
}

int delete_student_open(char *name){

    int index=hash_func_name(name);
    int v=0;
    struct student* temp=hash_table_open[index],*prev=hash_table_open[index],*prev1;
    if (temp != NULL && strcmp(temp->std_name,name)==0) {
        hash_table_open[index] = temp->next;
        temp=dummy;
        return 1;
    }
    if (hash_table_open[index]==NULL){
        return 0;
    }
    else{
        while(temp!=NULL){
            if (strcmp(temp->std_name,name)==0&v==1){
                hash_table_open[index]->next=temp->next;
                temp=dummy;
                return 1;
            }

            else if(strcmp(temp->std_name,name)==0&v==2){
            hash_table_open[index]->next->next=temp->next;
            temp=dummy;
            return 1;
            }
            else if(strcmp(temp->std_name,name)==0&v==3){
            hash_table_open[index]->next->next->next=temp->next;
            temp=dummy;
            return 1;
            }
            else if(strcmp(temp->std_name,name)==0&v==4){
            hash_table_open[index]->next->next->next->next=temp->next;
            temp=dummy;
            return 1;
            }
            v++;
            prev = temp;
            temp = temp->next;
        }
         return 0;
    };

}



void display_table_open() {
    int z=0;
    for (int i = 0; i < table_size; ++i) {
        struct student *entry = hash_table_open[i];

        if (entry == NULL) {
            continue;
        }

        printf("slot[%d]: ", i);

        for(;;) {
            z++;
            printf("\n\n student name : %s", entry->std_name);
            printf("\n student ID : %d",entry->std_id);
            printf("\n student birth date (day//month//year): %d",entry->day);
            printf("// %d",entry->month);
            printf("// %d", entry->year);
            printf("\n student last year score: %d", entry->std_score);
            printf("\n*******************************\n");

            if (entry->next == NULL) {
                break;
            }

            entry = entry->next;
        }
    }
    if(z==0){printf("the table is empty \n");}
}

//****************************************************************************************************************
//****************************************************************************************************************
//*************************************************closed hashing*************************************************
//****************************************************************************************************************
//****************************************************************************************************************
int hash_func_birthday(int day, int month, int year){

    long int value =0;
    value=day+month+year;
    value=value%table_size;
    return value;
}

void student_insert_closed_hashing(char *name,int id,int day,int month, int year,int score){

    int index=hash_func_birthday(day,month,year);
    struct student* insertion_entry=hash_table_closed[index];
    if (hash_table_closed[index]==NULL){
        hash_table_closed[index]=insert(name,id,day,month,year,score);
    }
    else{
        while(hash_table_closed[index]!=NULL){
            index++;
            index=index%table_size;
        }
        hash_table_closed[index]=insert(name,id,day,month,year,score);

    }
}





void student_insert_closed_hashing_quad(char *name,int id,int day,int month, int year,int score){

    int index=hash_func_birthday(day,month,year);
    int index_const=index;
    struct student* insertion_entry=hash_table_closed[index];
    if (hash_table_closed[index]==NULL){
        hash_table_closed[index]=insert(name,id,day,month,year,score);
    }
    else{
        for(int i=0;i<table_size;i++)
        if(hash_table_closed[index]!=NULL){
            index=index_const;
            index=index+i*i;
            index=index%table_size;
        }
        if (index>table_size){}
        hash_table_closed[index]=insert(name,id,day,month,year,score);

    }
}


struct student * student_search_closed_hashing(int day, int month, int year){

    int l=0;
    int index=hash_func_birthday(day,month,year);
    struct student* search_entry=hash_table_closed[index];

        while(index<table_size){
            search_entry=hash_table_closed[index];
            if(search_entry!=NULL){
            int u=search_entry->day;
            int i=search_entry->month;
            int o=search_entry->year;
            if(u==day&&i==month&&o==year){
                  return search_entry;
        }
                }
        if (index==(table_size-1)&&l==0){
            index=0;
            l++;
        }
            index++;
        }
         return NULL;
}


int delete_student_closed(int day, int month, int year){

    int l=0;
    int index=hash_func_birthday(day,month,year);
    struct student* search_entry=hash_table_closed[index];

        while(index<table_size){
            search_entry=hash_table_closed[index];
            if(search_entry!=NULL){
            int u=search_entry->day;
            int i=search_entry->month;
            int o=search_entry->year;
            if(u==day&&i==month&&o==year){
                hash_table_closed[index]=dummy;
                return 1;
        }
        }
        if (index==(table_size-1)&&l==0){
            index=0;
            l++;
        }
            index++;
        }
         return 0;
    }





void display_table_closed() {
    int z=0;
    for (int i = 0; i < table_size; i++) {
        struct student *entry = hash_table_closed[i];

        if (entry == NULL) {
            continue;
        }
        z++;
        printf("slot[%d]: ", i);
        printf("\n\n student name : %s", entry->std_name);
        printf("\n student ID : %d",entry->std_id);
        printf("\n student birth date (day//month//year): %d",entry->day);
        printf("// %d",entry->month);
        printf("// %d", entry->year);
        printf("\n student last year score: %d", entry->std_score);
        printf("\n*******************************\n");
    }
    if(z==0){printf("the table is empty \n");}
}


//****************************************************************************************************************
//****************************************************************************************************************
//**************************************************main function*************************************************
//****************************************************************************************************************
//****************************************************************************************************************

int main()
{
    char std_nameT[20];
    int std_idT;
    int yearT;
    int monthT;
    int dayT;
    int std_scoreT;
    int z,y,m,q,D;
    struct student* found_student_closed;
    struct student* found_student_open;
    struct student* hash_table_open_auto[10];
    struct student* hash_table_open_auto1[1000];
    struct student* hash_table_open_auto2[100000];
    struct student* hash_table_closed_auto[10];
    struct student* hash_table_closed_auto1[1000];
    struct student* hash_table_closed_auto2[100000];
    create_hash();
    r:
    printf("do you want to use open(1) or closed(2) hashing\n");
    scanf("%d",&y);
    if(y==1){goto p;}
    else if(y==2){goto t;}
    else {
            printf("wrong answer try again \n");
            goto r;
    }


    // open hashing
    p:
        create_hash();
    s:
    printf("do you want to insert student(1) or display table(2) or search(3) or delete(4) or return(5)\n");
    scanf("%d",&z);
    if(z==1){
        printf("\n enter student name \n");
        scanf("%s",&std_nameT);
        printf("\n enter student ID \n");
        scanf("%d",&std_idT);
        printf("\n enter student birth date day//month//year: \n");
        scanf("%d",&dayT);
        scanf("%d",&monthT);
        scanf("%d",&yearT);
        printf("\n enter student last year score:");
        scanf("%d",&std_scoreT);
        student_insert_open_hashing(std_nameT,std_idT,dayT,monthT,yearT,std_scoreT);
        goto s;
    }
   else if(z==2){
        display_table_open();
        goto s;
   }
   else if(z==3){
        printf("enter the student name \n");
        scanf("%s",&std_nameT);
        found_student_open=student_search_open_hashing(std_nameT);
        if(found_student_open!=NULL){
        printf("student KEY = %d", hash_func_name(found_student_open->std_name));
        printf("\n\n student name : %s", found_student_open->std_name);
        printf("\n student ID : %d",found_student_open->std_id);
        printf("\n student birth date (day//month//year): %d",found_student_open->day);
        printf("// %d",found_student_open->month);
        printf("// %d", found_student_open->year);
        printf("\n student last year score: %d", found_student_open->std_score);
        printf("\n*******************************\n");
        }
        else{printf("student not found \n");}
        goto s;
    }
    else if(z==4){
        printf("enter the student name \n");
        scanf("%s",&std_nameT);
        D=delete_student_open(std_nameT);
        if(D==1){printf("deleted successfully \n");}
        if(D==0){printf("not found \n");}
        goto s;

    }
    else if(z==5){goto r;}
    else {
       printf("wrong answer try again \n");
       goto s;
   }



   // closed hashing
   t:
   printf("do you want linear probing (1) or quadratic probing (2) ?\n");
   scanf("%d",&q);
   if (q!=1&&q!=2){
        printf("wrong answer try again \n");
        goto t;
   }
   create_hash();
   o:
   printf("do you want to insert student(1) or display table(2) or search(3) or delete(4) or return(5)\n");
   scanf("%d",&m);
   if(m==1){
        printf("\n enter student name \n");
        scanf("%s",&std_nameT);
        printf("\n enter student ID \n");
        scanf("%d",&std_idT);
        printf("\n enter student birth date day//month//year: \n");
        scanf("%d",&dayT);
        scanf("%d",&monthT);
        scanf("%d",&yearT);
        printf("\n enter student last year score:");
        scanf("%d",&std_scoreT);
        if(q==1){student_insert_closed_hashing(std_nameT,std_idT,dayT,monthT,yearT,std_scoreT);}
        if(q==2){student_insert_closed_hashing_quad(std_nameT,std_idT,dayT,monthT,yearT,std_scoreT);}
        goto o;
    }
    else if(m==2){
        display_table_closed();
        goto o;
    }
    else if(m==3){
        printf("\n enter student birth date day//month//year: \n");
        scanf("%d",&dayT);
        scanf("%d",&monthT);
        scanf("%d",&yearT);
        found_student_closed=student_search_closed_hashing(dayT,monthT,yearT);
        if(found_student_closed!=NULL){
        printf("\n\n student name : %s", found_student_closed->std_name);
        printf("\n student ID : %d",found_student_closed->std_id);
        printf("\n student birth date (day//month//year): %d",found_student_closed->day);
        printf("// %d",found_student_closed->month);
        printf("// %d", found_student_closed->year);
        printf("\n student last year score: %d", found_student_closed->std_score);
        printf("\n*******************************\n");
        }
        else{printf("student not found \n");}
        goto o;
    }
    else if(m==4){
        printf("\n enter student birth date day//month//year: \n");
        scanf("%d",&dayT);
        scanf("%d",&monthT);
        scanf("%d",&yearT);
        D=delete_student_closed(dayT,monthT,yearT);
        if(D==1){printf("deleted successfully \n");}
        if(D==0){printf("not found \n");}
        goto o;

    }
    else if(m==5){goto r;}
    else {
       printf("wrong answer try again \n");
       goto o;
   }


    return 0;
}
