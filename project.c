#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>
struct node{
int x;
int y;
char name[200];
int energy;
struct node *next;
};
enum blocks{
ENERGY=1,
MITOSIS,
FORBIDDEN,
NORMAL
};
struct node *list=NULL;
struct node *list2=NULL;
int n;
char map[1000][1000];
char map2[1000][1000]; //energy=yellow, split=blue ,forbidden=red, normal=green
int map3[1000][1000];
void setcolor(int ForgC){
     WORD wColor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}
void open_file(){
char s1[200];
printf("Enter the name of the file which you want to build the map from it:\n");
scanf("%s",s1);
FILE *fp=fopen(s1,"rb");
fread(&n,sizeof(int),1,fp);
int i,j;
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        fread(&map[i][j],sizeof(char),1,fp);
    }
}
fclose(fp);
}
void initialize_map(){
int i,j;
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        map2[i][j]='+';
    }

}
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        map3[i][j]=100;
    }
}
}
int main_menu(){
printf("1)Load\n2)New single player game\n3)New multiplayer game\n4)Exit\n");
int m;
scanf("%d",&m);
return m;
}
void insert_cell(){
list=(struct node *)malloc(sizeof(struct node));
struct node *current1=list;
int num,i;
time_t t=time(NULL);
srand(t);
printf("Enter the number of cells:\n");
scanf("%d",&num);
char s1[200];
for(i=0;i<num;i++){
    int x=rand()%n;
    int y=rand()%n;
    if(map[x][y]=='3' || map2[x][y]!='+'){
        i--;
    }
    else{
        current1->x=x;
        current1->y=y;
        printf("Enter the name of cell number %d:\n",i+1);
        scanf("%s",s1);
        strcpy(current1->name,s1);
        current1->energy=0;
        current1->next=(struct node *)malloc(sizeof(struct node));
        current1->next->next=NULL;
        current1=current1->next;
        map2[x][y]='o';
    }
}

}
void insert_cell_2(){
list=(struct node *)malloc(sizeof(struct node));
list2=(struct node *)malloc(sizeof(struct node));
struct node *current1=list;
struct node *current2=list2;
int num,i,num2;
time_t t=time(NULL);
srand(t);
printf("player number 1: \n");
printf("the number of cells:\n");
scanf("%d",&num);
char s1[200];
for(i=0;i<num;i++){
    int x=rand()%n;
    int y=rand()%n;
    if(map[x][y]=='3' || map2[x][y]!='+'){
        i--;
    }
    else{
        current1->x=x;
        current1->y=y;
        printf("enter the name of cell number %d:\n",i+1);
        scanf("%s",s1);
        strcpy(current1->name,s1);
        current1->energy=0;
        current1->next=(struct node *)malloc(sizeof(struct node));
        current1->next->next=NULL;
        current1=current1->next;
        map2[x][y]='o';
    }
}
printf("player number 2: \n");
printf("the number of cells:\n");
scanf("%d",&num2);
char s2[200];
for(i=0;i<num2;i++){
    int x=rand()%n;
    int y=rand()%n;
    if(map[x][y]=='3' || map2[x][y]!='+'){
        i--;
    }
    else{
        current2->x=x;
        current2->y=y;
        printf("enter the name of cell number %d:\n",i+1);
        scanf("%s",s2);
        strcpy(current2->name,s2);
        current2->energy=0;
        current2->next=(struct node *)malloc(sizeof(struct node));
        current2->next->next=NULL;
        current2=current2->next;
        map2[x][y]='x';
    }
}

}
int chooseandmain(int p){
struct node *current;
if(p==1){
   current=list;
}
if(p==2){
    current=list2;
}
int i,num;
i=0;
printf("Choose one cell:\n");
while(current->next!=NULL){
    i++;
    printf("%d)%s (%d,%d)\n",i,current->name,current->y,(n-1)-current->x);
    current=current->next;

}
scanf("%d",&num);
return num;
}
int menu(){
int m;
printf("1)Move\n2)Split a cell\n3)Boost energy\n4)Save\n5)Exit\n");
scanf("%d",&m);
return m;
}
void move(int r,int p){
int num,i;
char c;
struct node *current;
if(p==1){
    current=list;
    c='o';
}
if(p==2){
    current=list2;
    c='x';
}

for(i=1;i<r;i++){
    current=current->next;
}
int x=current->x;
int y=current->y;
printf("1)North\n2)North west\n3)North east\n4)South\n5)South west\n6)South east\n");
scanf("%d",&num);
if(num==1){
    if(map2[x-1][y]=='+' && map[x-1][y]!='3' && x-1>=0){
        current->x=x-1;
        map2[x][y]='+';
        map2[x-1][y]=c;

    }
    else{
        setcolor(4);
        printf("Moving to north is impossible for this cell!\n");
        setcolor(15);
    }
}
if(num==2){
    if(map2[x-1][y-1]=='+' && map[x-1][y-1]!='3' && y-1>=0&& x-1>=0){
        current->y=y-1;
        current->x=x-1;
        map2[x][y]='+';
        map2[x-1][y-1]=c;
    }
    else{
        setcolor(4);
        printf("Moving to north west is impossible for this cell!\n");
        setcolor(15);
    }
}
if(num==3){
    if(map2[x-1][y+1]=='+' && map[x-1][y+1]!='3' && y+1<=(n-1) && x-1>=0){
        current->y=y+1;
        current->x=x-1;
        map2[x][y]='+';
        map2[x-1][y+1]=c;
    }
    else{
        setcolor(4);
        printf("moving to north east is impossible for this cell!\n");
        setcolor(15);
    }
}
if(num==4){
    if(map2[x+1][y]=='+' && map[x+1][y]!='3' && x+1<=(n-1)){
        current->x=x+1;
        map2[x][y]='+';
        map2[x+1][y]=c;
    }
    else{
        setcolor(4);
        printf("Moving to south is impossible for this cell!\n");
        setcolor(15);
    }
}
if(num==5){
    if(map2[x+1][y-1]=='+' && map[x+1][y-1]!='3' && x+1<=(n-1) && y-1>=0){
        current->x=x+1;
        current->y=y-1;
        map2[x][y]='+';
        map2[x+1][y-1]=c;
    }
    else{
        setcolor(4);
        printf("Moving to south west is impossible for this cell!\n");
        setcolor(15);
    }
}
if(num==6){
    if(map2[x+1][y+1]=='+' && map[x+1][y+1]!='3' && x+1<=(n-1) && y+1<=(n-1)){
        current->y=y+1;
        current->x=x+1;
        map2[x][y]='+';
        map2[x+1][y+1]=c;
    }
    else{
        setcolor(4);
        printf("Moving to south east is impossible for this cell!\n");
        setcolor(15);
    }
}

}
void split(int r,int p){
time_t t=time(NULL);
srand(t);
int b=0;
struct node *current;
struct node *current2;
char c;
if(p==1){
    current=list;
    current2=list;
    c='o';
}
if(p==2){
    current=list2;
    current2=list2;
    c='x';
}
int i;
char s1[200];
char s2[200];
int a;
for(i=1;i<r;i++){
    current=current->next;
}
int x=current->x;
int y=current->y;
int z=current->energy;
if(z<80){
    setcolor(4);
    printf("The energy isn't enough for mitosis!\n");
    setcolor(15);
}
else{
   while(current2->next!=NULL){
    current2=current2->next;
   }
   for(i=1;i<2;i++){
        if(b==7){
            setcolor(4);
            printf("All of the nearby blocks are occupied or forbidden!\n");
            setcolor(15);
            return ;
        }
         a=rand()%6 + 1;
         if(a==1 && map2[x-1][y]=='+' && map[x-1][y]!='3' && x-1>=0){
            current2->next=(struct node *)malloc(sizeof(struct node));
            current2->next->next=NULL;
            map2[x-1][y]=c;
            current->energy=40;
            current2->x=x-1;
            current2->y=y;
            current2->energy=40;
            printf("Enter the name of the new cell:\n");
            scanf("%s",s1);
            printf("Enter the name of the new cell:\n");
            scanf("%s",s2);
            strcpy(current->name,s1);
            strcpy(current2->name,s2);
            return ;

         }
         if(a==2 && map2[x-1][y-1]=='+' && map[x-1][y-1]!='3' && y-1>=0&& x-1>=0){
            current2->next=(struct node *)malloc(sizeof(struct node));
            current2->next->next=NULL;
            map2[x-1][y-1]=c;
            current2->y=y-1;
            current2->x=x-1;
            current->energy=40;
            current2->energy=40;
            printf("Enter the name of the new cell:\n");
            scanf("%s",s1);
            printf("Enter the name of the new cell:\n");
            scanf("%s",s2);
            strcpy(current->name,s1);
            strcpy(current2->name,s2);
            return ;

         }
         if(a==3 && map2[x-1][y+1]=='+' && map[x-1][y+1]!='3' && y+1<=(n-1) && x-1>=0){
            current2->next=(struct node *)malloc(sizeof(struct node));
            current2->next->next=NULL;
            map2[x-1][y+1]=c;
            current2->x=x-1;
            current2->y=y+1;
            current->energy=40;
            current2->energy=40;
            printf("Enter the name of the new cell:\n");
            scanf("%s",s1);
            printf("Enter the name of the new cell:\n");
            scanf("%s",s2);
            strcpy(current->name,s1);
            strcpy(current2->name,s2);
            return ;
         }
         if(a==4 && map2[x+1][y]=='+' && map[x+1][y]!='3' && x+1<=(n-1)){
            current2->next=(struct node *)malloc(sizeof(struct node));
            current2->next->next=NULL;
            map2[x+1][y]=c;
            current2->y=y;
            current2->x=x+1;
            current->energy=40;
            current2->energy=40;
            strcpy(current->name,s1);
            strcpy(current2->name,s2);
            return ;
         }
         if(a==5 && map2[x+1][y-1]=='+' && map[x+1][y-1]!='3' && x+1<=(n-1) && y-1>=0){
            current2->next=(struct node *)malloc(sizeof(struct node));
            current2->next->next=NULL;
            map2[x+1][y-1]=c;
            current2->x=x+1;
            current2->y=y-1;
            current->energy=40;
            current2->energy=40;
            printf("Enter the name of the new cell:\n");
            scanf("%s",s1);
            printf("Enter the name of the new cell:\n");
            scanf("%s",s2);
            strcpy(current->name,s1);
            strcpy(current2->name,s2);
            return ;
         }
         if(a==6 && map2[x+1][y+1]=='+' && map[x+1][y+1]!='3' && x+1<=(n-1) && y+1<=(n-1) ){
            current2->next=(struct node *)malloc(sizeof(struct node));
            current2->next->next=NULL;
            map2[x+1][y+1]=c;
            current2->x=x+1;
            current2->y=y+1;
            current->energy=40;
            current2->energy=40;
            printf("Enter the name of the new cell:\n");
            scanf("%s",s1);
            printf("Enter the name of the new cell:\n");
            scanf("%s",s2);
            strcpy(current->name,s1);
            strcpy(current2->name,s2);
            return ;
         }
         else{
            i--;
            b++;
         }
   }
}

}
void boostenergy(int r,int p){
int i;
struct node *current;
if(p==1){
    current=list;
}
if(p==2){
    current=list2;
}
for(i=1;i<r;i++){
    current=current->next;
}
int x=current->x;
int y=current->y;
if(current->energy==100){
    setcolor(4);
    printf("The cell has the maximum energy and cannot boost energy!\n");
    setcolor(15);
    return ;
}
if(map3[x][y]==0){
    setcolor(4);
    printf("Their isn't any energy in this block!\n");
    setcolor(15);
    return ;
}
if(map3[x][y]>=15 && current->energy<100){
    current->energy+=15;
    map3[x][y]-=15;
    return ;
}
if(map3[x][y]<15 && map3[x][y]>0 && current->energy<100){
    current->energy+=map3[x][y];
    map3[x][y]=0;
    return ;
}
}
void save(){
int i,j;
struct node *current=list;
FILE *fp;
int k=1;
int num=0;
char s2[200];
printf("Enter the name of the file you want to save data in it:\n");
scanf("%s",s2);
fp=fopen(s2,"wb");
fwrite(&k,sizeof(int),1,fp);
fwrite(&n,sizeof(int),1,fp);
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        fwrite(&map[i][j],sizeof(char),1,fp);
    }
}
while(current->next!=NULL){
    current=current->next;
    num++;
}
fwrite(&num,sizeof(int),1,fp);
current=list;
while(current->next!=NULL){
    fwrite(&current->x,sizeof(int),1,fp);
    fwrite(&current->y,sizeof(int),1,fp);
    fwrite(current->name,sizeof(char),200,fp);
    fwrite(&current->energy,sizeof(int),1,fp);
    current=current->next;
}
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        fwrite(&map3[i][j],sizeof(int),1,fp);
    }
}
fclose(fp);
}
void save_2(){
int i,j;
int k=2;
int num1=0;
int num2=0;
struct node *current=list;
struct node *current2=list2;
FILE *fp;
char s2[200];
printf("Enter the name of the file you want to save data in it:\n");
scanf("%s",s2);
fp=fopen(s2,"wb");
fwrite(&k,sizeof(int),1,fp);
fwrite(&n,sizeof(int),1,fp);
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        fwrite(&map[i][j],sizeof(char),1,fp);
    }
}
while(current->next!=NULL){
    current=current->next;
    num1++;
}
fwrite(&num1,sizeof(int),1,fp);
current=list;
while(current->next!=NULL){
    fwrite(&current->x,sizeof(int),1,fp);
    fwrite(&current->y,sizeof(int),1,fp);
    fwrite(current->name,sizeof(char),200,fp);
    fwrite(&current->energy,sizeof(int),1,fp);
    current=current->next;
}
while(current2->next!=NULL){
    current2=current2->next;
    num2++;
}
fwrite(&num2,sizeof(int),1,fp);
current2=list2;
while(current2->next!=NULL){
    fwrite(&current2->x,sizeof(int),1,fp);
    fwrite(&current2->y,sizeof(int),1,fp);
    fwrite(current2->name,sizeof(char),200,fp);
    fwrite(&current2->energy,sizeof(int),1,fp);
    current2=current2->next;
}
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        fwrite(&map3[i][j],sizeof(int),1,fp);
    }
}
fclose(fp);
}
int load(){
int k,i,j;
int num,num2;
int x1,y1,en,x2,y2,en2;
char name1[200];
char name2[200];
list=NULL;
list2=NULL;
FILE *fp;
printf("Enter the name of the file you want to load data from it:\n");
char s2[200];
scanf("%s",s2);
fp=fopen(s2,"rb");
fread(&k,sizeof(int),1,fp);
if(k==1){
    fread(&n,sizeof(int),1,fp);
    initialize_map();
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            fread(&map[i][j],sizeof(char),1,fp);
    }
}
fread(&num,sizeof(int),1,fp);
list=(struct node *)malloc(sizeof(struct node));
struct node *current=list;
for(i=0;i<num;i++){
    fread(&x1,sizeof(int),1,fp);
    fread(&y1,sizeof(int),1,fp);
    fread(name1,sizeof(char),200,fp);
    fread(&en,sizeof(int),1,fp);
    current->x=x1;
    current->y=y1;
    strcpy(current->name,name1);
    current->energy=en;
    current->next=(struct node *)malloc(sizeof(struct node));
    current->next->next=NULL;
    current=current->next;
    map2[x1][y1]='o';
}

}
if(k==2){
    fread(&n,sizeof(int),1,fp);
    initialize_map();
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            fread(&map[i][j],sizeof(char),1,fp);
    }
}
    fread(&num,sizeof(int),1,fp);
    list=(struct node *)malloc(sizeof(struct node));
    struct node *current=list;
    for(i=0;i<num;i++){
        fread(&x1,sizeof(int),1,fp);
        fread(&y1,sizeof(int),1,fp);
        fread(name1,sizeof(char),200,fp);
        fread(&en,sizeof(int),1,fp);
        current->x=x1;
        current->y=y1;
        strcpy(current->name,name1);
        current->energy=en;
        current->next=(struct node *)malloc(sizeof(struct node));
        current->next->next=NULL;
        current=current->next;
        map2[x1][y1]='o';
}
    fread(&num2,sizeof(int),1,fp);
    list2=(struct node *)malloc(sizeof(struct node));
    struct node *current2=list2;
    for(i=0;i<num2;i++){
        fread(&x2,sizeof(int),1,fp);
        fread(&y2,sizeof(int),1,fp);
        fread(name2,sizeof(char),200,fp);
        fread(&en2,sizeof(int),1,fp);
        current2->x=x2;
        current2->y=y2;
        strcpy(current2->name,name2);
        current2->energy=en2;
        current2->next=(struct node *)malloc(sizeof(struct node));
        current2->next->next=NULL;
        current2=current2->next;
        map2[x2][y2]='x';
}

}
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        fread(&map3[i][j],sizeof(int),1,fp);
    }
}
return k;
}
void print(){
int i,j;
for(i=0;i<n;i++){
    for(j=0;j<n;j++){
        if(map[i][j]=='1'){
            setcolor(14);
            printf("%c  ",map2[i][j]);
            setcolor(15);
        }
        if(map[i][j]=='2'){
            setcolor(1);
            printf("%c  ",map2[i][j]);
            setcolor(15);
        }
        if(map[i][j]=='3'){
            setcolor(4);
            printf("%c  ",map2[i][j]);
            setcolor(15);
        }
        if(map[i][j]=='4'){
            setcolor(2);
            printf("%c  ",map2[i][j]);
            setcolor(15);
        }

    }
    printf("\n");
}

}
void singleplayer(){
while(1){
    int res1=chooseandmain(1);
    int m=menu();
    if(m==5){
        break;
    }
    if(m==1){
        move(res1,1);
        print();
    }
    if(m==2){
        int i;
        struct node *current=list;
        for(i=1;i<res1;i++){
            current=current->next;
        }
        int x=current->x;
        int y=current->y;
        if(map[x][y]=='2'){
            split(res1,1);
            print();
        }
        else{
            setcolor(4);
            printf("Cannot split!\n");
            setcolor(15);

        }

    }
    if(m==3){
        int i;
        struct node *current=list;
        for(i=1;i<res1;i++){
            current=current->next;
        }
        int x=current->x;
        int y=current->y;
        if(map[x][y]=='1'){
            boostenergy(res1,1);
            print();
        }
        else{
            setcolor(4);
            printf("Cannot boost energy!\n");
            setcolor(15);
        }
    }
    if(m==4){
        save();
        printf("The game has been saved successfully!\n");
    }
 }
return ;
}
void multiplayer(){
while(1){
    printf("Player number 1: \n");
    int res1=chooseandmain(1);
    int m=menu();
    if(m==5){
        break;
    }
    if(m==1){
        move(res1,1);
        print();
    }
    if(m==2){
        int i;
        struct node *current=list;
        for(i=1;i<res1;i++){
            current=current->next;
        }
        int x=current->x;
        int y=current->y;
        if(map[x][y]=='2'){
            split(res1,1);
            print();
        }
        else{
            setcolor(4);
            printf("Cannot split!\n");
            setcolor(15);
        }

    }
    if(m==3){
        int i;
        struct node *current=list;
        for(i=1;i<res1;i++){
            current=current->next;
        }
        int x=current->x;
        int y=current->y;
        if(map[x][y]=='1'){
            boostenergy(res1,1);
            print();
        }
        else{
            setcolor(4);
            printf("Cannot boost energy!\n");
            setcolor(15);
        }
    }
    if(m==4){
        save_2();
        printf("The game has been saved successfully!\n");
    }
    printf("Player number 2: \n");
    int res2=chooseandmain(2);
    m=menu();
    if(m==5){
        break;
    }
    if(m==1){
        move(res2,2);
        print();
    }
    if(m==2){
        int i;
        struct node *current=list2;
        for(i=1;i<res2;i++){
            current=current->next;
        }
        int x=current->x;
        int y=current->y;
        if(map[x][y]=='2'){
            split(res2,2);
            print();
        }
        else{
            setcolor(4);
            printf("Cannot split!\n");
            setcolor(15);
        }

    }
    if(m==3){
        int i;
        struct node *current=list2;
        for(i=1;i<res2;i++){
            current=current->next;
        }
        int x=current->x;
        int y=current->y;
        if(map[x][y]=='1'){
            boostenergy(res2,2);
            print();
        }
        else{
            setcolor(4);
            printf("Cannot boost energy!\n");
            setcolor(15);
        }
    }
    if(m==4){
        save_2();
        printf("The game has been saved successfully!\n");
    }
    }
return ;

}
int grades(int p){
int sum=0;
struct node *current;
if(p==1){
    current=list;
}
if(p==2){
    current=list2;
}
while(current->next!=NULL){
    sum+=current->energy;
    current=current->next;
}
return sum;
}
int main(){
while(1){
 int x1=main_menu();
 if(x1==1){
    int k=load();
    print();
    if(k==1){
        singleplayer();
        int grades1=grades(1);
        printf("The total grades of player number 1 is: %d\n",grades1);
    }
    if(k==2){
        multiplayer();
        int grades1=grades(1);
        printf("The total grades of player number 1 is: %d\n",grades1);
        int grades2=grades(2);
        printf("The total grades of player number 2 is: %d\n",grades2);
    }

 }
 if(x1==2){
    open_file();
    initialize_map();
    insert_cell();
    print();
    singleplayer();
    int grades1=grades(1);
    printf("The total grades of player number 1 is: %d\n",grades1);
 }

 if(x1==3){
    open_file();
    initialize_map();
    insert_cell_2(n);
    print();
    multiplayer();
    int grades1=grades(1);
    printf("The total grades of player number 1 is: %d\n",grades1);
    int grades2=grades(2);
    printf("The total grades of player number 2 is: %d\n",grades2);

}
 if(x1==4){
    break;
 }
}
return 0;
}

