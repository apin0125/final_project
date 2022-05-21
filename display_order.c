#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<math.h>

#define B_BLUE "\x1B[1;36m"
#define DBLUE "\x1B[0;34m"
#define GREEN "\x1B[0;32m"
#define BACK_YELLOW "\x1B[3;33m"
#define PURPLE "\x1B[0;35m"

typedef struct data{
    char name[21];
    char gender;
    char hobby[5][36];
    char phone_number[11];
    char area[16];
    char target;
    int age;
    float height;
    char zodiac[21];
    char income[11];
    char job[41];
    int index_of_area;
    char self_introduction[151];
    int score;
} Data;

int idx[1000];                                          // 排序會用到的index
Data person[1000];                                      // 移出來ㄛ
int read_file(Data *person);
void calculate_score(Data *User,int *data_amount);
int judge_mode(Data *User);                             // 回傳使用者性向狀況
void sexuality_score(Data *User,int *data_amount);
void age_score(Data *User,int *data_amount);
void area_score(Data *User,int *data_amount);
void hobby_score(Data *User,int *data_amount);
int comp(const void *p,const void *q);
void display(int *data_amount);

int main(){
    int data_amount = 0;
    data_amount = read_file(person);
    Data User[1];
    scanf("%s %c %s %s %s %s %s %s %s %c %d %f %s %s %d %s "
    , User->name
    , &User->gender
    , User->hobby[0]
    , User->hobby[1]
    , User->hobby[2]
    , User->hobby[3]
    , User->hobby[4]
    , User->phone_number
    , User->area
    , &User->target
    , &User->age
    , &User->height
    , User->zodiac
    , User->income
    , User->self_introduction
    );
    calculate_score(User,&data_amount);
    printf("calculate\n");
    qsort(idx,data_amount,sizeof(int),comp);
    printf("sort\n");
    display(&data_amount);
    // printf("%d\n", data_amount);                        // 看讀到的人數對不對
    // printf("%lf", (double)clock() / CLOCKS_PER_SEC);    // 看整個程式執行時間(/s)
}

int read_file(Data *person){
    int i = 0;                                    // 檔名要記得改自己txt的名字喔
    const char *filename = "nefertari.txt";
    FILE *input_file = fopen(filename, "r");
    if (!input_file){
        exit(EXIT_FAILURE);
    }
    while (fscanf(input_file, "%s %c %s %s %s %s %s %s %s %c %d %f %s %s %d %s "
    , person[i].name
    , &person[i].gender
    , person[i].hobby[0]
    , person[i].hobby[1]
    , person[i].hobby[2]
    , person[i].hobby[3]
    , person[i].hobby[4]
    , person[i].phone_number
    , person[i].area
    , &person[i].target
    , &person[i].age
    , &person[i].height
    , person[i].zodiac
    , person[i].income
    , &person[i].index_of_area
    , person[i].job) != EOF){
        fgets(person[i].self_introduction, 151, input_file);
        idx[i] = i;
        i++;
    }
    fclose(input_file);
    int temp_i = i;
    /*for (int i = 0; i < temp_i; i++){
        printf("%s %c %s %s %s %s %s %s %s %c %d %.1f %s %s %s %s\n"
        , person[i].name
        , person[i].gender
        , person[i].hobby[0]
        , person[i].hobby[1]
        , person[i].hobby[2]
        , person[i].hobby[3]
        , person[i].hobby[4]
        , person[i].phone_number
        , person[i].area
        , person[i].target
        , person[i].age
        , person[i].height
        , person[i].zodiac
        , person[i].income
        , person[i].job
        , person[i].index_of_area
        , person[i].self_introduction);
    }*/
    return i;
}

void calculate_score(Data *User,int *data_amount){
    sexuality_score(User,data_amount);
    age_score(User,data_amount);
    area_score(User,data_amount);
    hobby_score(User,data_amount);
}

int judge_mode(Data *User){
    if(User->gender == 'F'){
        if(User->target == 'M')
            return 1;                                          //直女回傳1
        else if(User->target == 'F')
            return 2;                                          //女同回傳2
        else if(User->target == 'B')
            return 3;                                          //女雙回傳3
    }
    else if(User->gender == 'M'){                              
        if(User->target == 'F')
            return 4;                                          //直男回傳4
        else if(User->target == 'M')
            return 5;                                          //男同回傳5
        else if(User->target == 'B')
            return 6;                                          //男雙回傳6
    }
}

void sexuality_score(Data *User,int *data_amount){     // 性向對了+500
    int mode = judge_mode(User);
    int i;
    if(mode == 1){
        for ( i = 0; i < *data_amount; i++){
           if((person + i)->gender == 'M' && (person + i)->target == 'F'){
               (person + i)->score += 500;                  
           }
           else{
               (person + i)->score = 0;
           }
        }
    }
    else if(mode == 2){
        for ( i = 0; i < *data_amount; i++){
           if((person + i)->gender == 'F'){
               if((person + i)->target == 'F' || (person + i)->target == 'B')
                   (person + i)->score += 500;
           }
           else{
               (person + i)->score = 0;
           }
        }
    }
    else if(mode == 3){
        for ( i = 0; i < *data_amount; i++){
            if((person + i)->target == 'F' || (person + i)->target == 'B')
                (person + i)->score += 500;
            else{
               (person + i)->score = 0;
            }
        }
    }
    else if(mode == 4){
        for ( i = 0; i < *data_amount; i++){
           if((person + i)->gender == 'F' && (person + i)->target == 'M'){
               (person + i)->score += 500;
           }
           else{
               (person + i)->score = 0;
           }
        }
    }
    else if(mode == 5){
        for ( i = 0; i < *data_amount; i++){
           if((person + i)->gender == 'M'){
               if((person + i)->target == 'M' || (person + i)->target == 'B')
                   (person + i)->score += 500;
           }
           else{
               (person + i)->score = 0;
           }
        }
    }
    else if(mode == 6){
        if((person + i)->target == 'M' || (person + i)->target == 'B')
                (person + i)->score += 500;
            else{
               (person + i)->score = 0;
            }
    }
}

void age_score(Data *User,int *data_amount){           // 年齡對了+100
    for(int i = 0;i < *data_amount;i++){
        if(abs(((person + i)->age)- (User->age))<=10){
            (person + i)->score += 100;
        }
    }
}

void area_score(Data *User,int *data_amount){          // 距離差0加100,差1加90,差2加80...10以上不加了
    for(int i = 0;i < *data_amount;i++){
        int ans = abs(((person + i)->index_of_area)- (User->index_of_area));
        if(ans == 0){
            (person + i)->score += 100;
        }
        else if(ans < 10){
            (person + i)->score += ((10-i)*10);
        }
    }
}

void hobby_score(Data *User,int *data_amount){         //每對一個+20
    for(int i = 0;i < 5;i++){       
        for(int j = 0;j < *data_amount;j++){
            for(int k = 0;k < 5;k++){
                if(!strcmp(User->hobby[i],(person + j)->hobby[k]))
                    (person + j)->score += 20;
            }
        }
    }    
}

int comp(const void *p,const void *q){
    return (person[*(int *)q].score) - (person[*(int *)p].score) ;
}

void display(int *data_amount){
    int j = 0;
    for(int i = 0;i < *data_amount;i++){
        // system("cls");
        if(person[idx[i]].score >= 500){
            printf("%d\n%d\n",i,person[idx[i]].score);
            printf(BACK_YELLOW"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n"); //看能不能把justify拿出來用 再修改邊幅
            int space = (80 - strlen(person[idx[i]].name))/2;
            for(int j = 0;j < space;j++){
                printf(" ");
            }
            printf(B_BLUE"%s\n",person[idx[i]].name);
            printf(DBLUE"Age: %d\n",person[idx[i]].age);
            printf(DBLUE"Area:%s\n",person[idx[i]].area);
            printf(DBLUE"Hobbies:\n  %s %s %s %s %s\n",person[idx[i]].hobby[0],person[idx[i]].hobby[1],person[idx[i]].hobby[2],person[idx[i]].hobby[3],person[idx[i]].hobby[4]);
            printf(PURPLE"Self introduction :\n  %s\n\n",person[idx[i]].self_introduction);  //justify內容?
            printf(BACK_YELLOW"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
            j++;
        }
    }
    printf("%d\n",j);
}