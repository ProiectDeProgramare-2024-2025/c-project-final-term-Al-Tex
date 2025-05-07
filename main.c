
#include <stdio.h>

#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
//#include <ncurses.h>
//#include <unistd.h>
#include <signal.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
void ClearScreen()
{
    //suprascrie outputul precedent
    COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    printf("\r                                      \n");
    printf("\r                                      \n");
    printf("\r                                      \n");
    printf("\r                                      \n");
    printf("\r                                      \n");
    printf("\r                                      \n");
    printf("\r                                      \n");
    printf("\r                                      \n");
    printf("\r                                      \n");
    cursorPosition.X = 0;	cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
void ShowConsoleCursor(boolean showFlag)
{
    HANDLE out= GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out,&cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out,&cursorInfo);
}
void Diagnoza(int currentLine,int menu)
{
    printf("currLine:%d\n",currentLine);
    printf("currentMenu:%d\n",menu);
}
struct CV
{
    char nume[25],prenume[25],numar_telefon[12],pozitii_anterioare[150];

}v[102];
void adaugare_CV_test(int *nrOrd)
{
    int nr;
    nr = *nrOrd;
    strcpy(v[++nr].nume,"Turculet");
    strcpy(v[nr].prenume , "Alexandru");
    strcpy(v[nr].numar_telefon , "0770373420");
    strcpy(v[nr].pozitii_anterioare , "robotician,semi-cercetator");
    *nrOrd = nr;
}

void readFile(int *nrOrd)
{
    int nr=*nrOrd;
    FILE *fila;

    fila = fopen("listaCV.txt","r");
    char aux[30];

    if(fila==NULL)
    {
        printf("nu se poate deschide fisierul");
        return ;
    }
    fgets(aux,30,fila);
    while(aux!=NULL)
    {

        aux[strlen(aux)-1]=0;
        strcpy(v[++nr].nume,aux);
        fgets(aux,30,fila);
        aux[strlen(aux)-1]=0;
        strcpy(v[nr].prenume , aux);
        fgets(aux,30,fila);
        aux[strlen(aux)-1]=0;
        strcpy(v[nr].numar_telefon , aux);
        fgets(aux,30,fila);
        aux[strlen(aux)-1]=0;
        strcpy(v[nr].pozitii_anterioare , aux);
        fgets(aux,30,fila);
    }
    *nrOrd=nr;
}
char *sir(FILE *fisier,int spatiu)
{
    char *ch=(char*)calloc(spatiu,sizeof(char));
    char car;
    int nr=0;
    do
    {
        car=fgetc(fisier);
        if(car!=';' && car!='\n')
            ch[nr++]=car;
    }while(car!=';' && car!='\n');
    ch[nr]=0;
    return ch;
}
void citire(int *nrOrd)
{
    FILE *fisier;
    fisier = fopen("listaCV.txt","r");
    fscanf(fisier,"%d",nrOrd);
    getc(fisier);
    for(int i=1;i<=*nrOrd;i++)
    {
        strcpy(v[i].nume,sir(fisier,25));
        strcpy(v[i].prenume,sir(fisier,25));
        strcpy(v[i].numar_telefon,sir(fisier,12));
        strcpy(v[i].pozitii_anterioare,sir(fisier,150));

    }

}
void afisare(int nrOrd)
{
    FILE *fisier;
    fisier = fopen("listaCV.txt","w");
    fprintf(fisier,"%d\n",nrOrd);
    for(int i=1;i<=nrOrd;i++)
    {
        //printf("%s\n",v[i].nume);
        fprintf(fisier,"%s;%s;%s;%s\n",v[i].prenume,v[i].nume,v[i].numar_telefon,v[i].pozitii_anterioare);
    }
}
const char *lower(const char *str) {
    char *p=malloc(strlen(str)+1);
    for (int i = 0; str[i] != '\0'; i++) {
        p[i]=(char)tolower((int)str[i]);
    }
    return p;
}
void cautareRez(const char *keyword,int nrOrd) {
    printf("Rezultate gasite:\n");
    int ok=0,nr=0;
    for(int i=1;i<nrOrd;i++) {
        if (strstr(lower(v[i].nume),keyword) ||
            strstr(lower(v[i].prenume),keyword) ||
            strstr(v[i].numar_telefon,keyword) ||
            strstr(lower(v[i].pozitii_anterioare),keyword)) {
            ok=1;
            nr++;
            printf("%d."ANSI_COLOR_BLUE"%s"ANSI_COLOR_CYAN" %s"ANSI_COLOR_GREEN" %s"ANSI_COLOR_RESET"\n",nr,v[i].nume,v[i].prenume,v[i].numar_telefon);
            }
    }
    if (ok==0) {
        printf("Niciun rezultat gasit pt cuvantul cheie introdus");
    }
}
void menuNume(int nrOrd,int *menu,const int *menuPre,int *adancime) {
    printf("Introduceti numele: ");
    while ((getchar()) != '\n' && getchar() != EOF) {}
    fgets(v[nrOrd].nume,25,stdin);
    v[nrOrd].nume[strcspn(v[nrOrd].nume, "\n")] = '\0';
    *menu=menuPre[--(*adancime)];
    Sleep(200);
}
void menuPrenume(int nrOrd,int *menu, const int *menuPre,int *adancime) {
    printf("Introduceti prenumele: ");//scanf("%s",v[nrOrd].prenume);
    while ((getchar()) != '\n' && getchar() != EOF) {}
    fgets(v[nrOrd].prenume,25,stdin);
    v[nrOrd].prenume[strcspn(v[nrOrd].prenume, "\n")] = '\0';
    *menu=menuPre[--(*adancime)];
}
void menuTelefon(int nrOrd,int *menu, const int *menuPre,int *adancime) {
    printf("Introduceti nr telefon: ");//scanf("%s",v[nrOrd].numar_telefon);
    while ((getchar()) != '\n' && getchar() != EOF) {}
    fgets(v[nrOrd].numar_telefon,12,stdin);
    v[nrOrd].numar_telefon[strcspn(v[nrOrd].numar_telefon, "\n")] = '\0';
    *menu=menuPre[--(*adancime)];
}
void menuPozitiiAnterioare(int nrOrd,int *menu, const int *menuPre,int *adancime) {
    printf("Introduceti pozitiile anterioare: "ANSI_COLOR_RESET);
    while ((getchar()) != '\n' && getchar() != EOF) {}
    fgets(v[nrOrd].pozitii_anterioare,150,stdin);
    v[nrOrd].pozitii_anterioare[strcspn(v[nrOrd].pozitii_anterioare, "\n")] = '\0';
    *menu=menuPre[--(*adancime)];
}
int main()
{
    int currentLine=1,minn[12]={0},maxx[12],menu=0,menuPre[50]={0},nrOrd=0,adancime=0,maxName=25;
    int listaMenu[30],back=0;
    char ch[25]={' '};
    listaMenu[1]=listaMenu[2]=listaMenu[3]=listaMenu[7]=listaMenu[8]=listaMenu[9]=listaMenu[10]=listaMenu[11]=1;
    citire(&nrOrd);
    nrOrd++;
    maxx[0]=4;maxx[1]=6;maxx[2]=nrOrd;maxx[3]=2;

    ShowConsoleCursor(0);


    while(1)
    {

        //ClearScreen();
        printf("\033[H\033[J");
        system("cls"); //- pt linux

        if(menu==0){
            printf("-= Sistem retea socializare jobs =-\n");
            printf("%c1.Construire CV personal\n",ch[1]);
            printf("%c2.Lista CV-uri\n",ch[2]);
            printf("%c3.Cauta CV\n",ch[3]);
            printf("%c4.Iesire\n",ch[4]);
            //Diagnoza(currentLine,menu);

        }
        if(menu==1){
            printf("-= Construire CV personal =-            \n");
            printf("%c1.Nume:"ANSI_COLOR_BLUE"%s                           "ANSI_COLOR_RESET"\n",ch[1],v[nrOrd].nume);
            printf("%c2.Prenume:"ANSI_COLOR_RED"%s                        "ANSI_COLOR_RESET"\n",ch[2],v[nrOrd].prenume);
            printf("%c3.Numar telefon:"ANSI_COLOR_MAGENTA"%s                  "ANSI_COLOR_RESET"\n",ch[3],v[nrOrd].numar_telefon);
            printf("%c4.Pozitii anterioare(separate de virgula):%s             \n",ch[4],v[nrOrd].pozitii_anterioare);
            printf("%c5.Salvare si iesire\n",ch[5]);
            printf("%c6.Iesire                            \n",ch[6]);
            //Diagnoza(currentLine,menu);
        }
        if(menu==2){
            printf("-= Lista CV-uri =- \n");
            for(int i=1;i<nrOrd;i++)
            {
                printf("%c%d."ANSI_COLOR_BLUE"%s"ANSI_COLOR_CYAN" %s"ANSI_COLOR_GREEN" %s"ANSI_COLOR_RESET"\n",ch[i],i,v[i].nume,v[i].prenume,v[i].numar_telefon);
            }
            printf("%c%d.Iesire\n",ch[nrOrd],nrOrd);
            //Diagnoza(currentLine,menu);
        }
        if(menu==3){
            printf("-= Cauta CV =- \n");
            printf("Introdu cuvant cheie:");
            char keyword[30];
            while ((getchar()) != '\n' && getchar() != EOF) {}
            fgets(keyword,30,stdin);
            keyword[strcspn(keyword, "\n")] = '\0';
            cautareRez(keyword,nrOrd);
            //printf("%c1.Optiunea nu este implementata\n",ch[1]);
            //printf("%c2.Iesire\n",ch[2]);
        }

        if(menu==7)
        {
            menuNume(nrOrd,&menu,menuPre,&adancime);
            back=1;
            currentLine=1;
        }

        if(menu==8)
        {
            menuPrenume(nrOrd,&menu,menuPre,&adancime);
            back=1;
            currentLine=1;
        }
        if(menu==9)
        {
            menuTelefon(nrOrd,&menu,menuPre,&adancime);
            back=1;
            currentLine=1;
        }
        if(menu==10)
        {
            menuPozitiiAnterioare(nrOrd,&menu,menuPre,&adancime);
            back=1;
            currentLine=1;
        }
        if(menu==11)
        {
            afisare(nrOrd);
            nrOrd++;
            menu=menuPre[--adancime];
            menu=menuPre[--adancime];
            back=1;
            currentLine=1;
        }

        Sleep(500);

        /*if(GetAsyncKeyState(VK_DOWN))
        {

            currentLine+=1;
            if(currentLine==maxx[menu]+1)
                currentLine=1;
            Sleep(100);
        }
        if(GetAsyncKeyState(VK_UP))
        {

            currentLine-=1;
            if(currentLine==minn[menu])
                currentLine=maxx[menu];
            Sleep(100);
        }

        if(GetAsyncKeyState(VK_RETURN))
        {

            //while ((getchar()) != '\n' && getchar() != EOF);
            printf("AM IESTI");
            if(currentLine==maxx[menu])
            {
                if(menu==0)
                    return 0;
                menu=menuPre[--adancime];
                currentLine=1;
            }
            else{
                if(listaMenu[menu*6+currentLine]==1)
                {   menuPre[adancime++]=menu;
                    menu = menu*6+currentLine;
                    currentLine=1;
                }
            }


            Sleep(250);
        }
*/
        if(GetAsyncKeyState(VK_ESCAPE))
            return 0;

        if (back==0) {
            printf("Introdu optiunea dorita:");
            scanf("%d",&currentLine);    //fgets(currentLine,2,stdin);
            if(currentLine==maxx[menu])
            {
                if(menu==0)
                    return 0;
                menu=menuPre[--adancime];
                currentLine=1;
            }
            else{
                if(listaMenu[menu*6+currentLine]==1)
                {   menuPre[adancime++]=menu;
                    menu = menu*6+currentLine;
                    currentLine=1;
                }
            }
        }
        back=0;
    }
    return 0;
}
