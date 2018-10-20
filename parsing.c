#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct STACKnode* link;
struct STACKnode { char item; link next; };
static link head;

link NEW(char item, link next)
{
	link x = malloc(sizeof *x);
	x->item = item;
	x->next = next;
	return x;
}

int STACKempty() { return head == NULL; }

void STACKpush(char item) { head = NEW(item, head); }

int  STACKpop()
{
	char item = head->item;
	link t = head->next;
	free(head);
	head = t;
	return item;
}

void STACKprint()
{
	link temp=head;
	while(temp!=NULL)
	{
		printf("%c",temp->item);
		temp = temp->next;
	}
	printf("\n");
}

int main()
{
   char line[100], file_name[25], option[3], tempo , tempo2, Array1[1] = "'";
   int i , flag1 = 0 , flag2 = 0 , flag3 = 0 , flag4 = 0 , j=0 , flag5 = 0 , pass = 0 ,chg = 0 , errorline = 1 , error = 0;
   FILE *fp; /*deixnei sto arxeio*/

   printf("Enter the name of file you wish to see\n");
   gets(file_name); /*pernei onoma arxeiou*/

   fp = fopen(file_name,"r"); /*entolh na diavasei to arxeio*/

   while(strcmp(option,"ON") && strcmp(option,"OFF")) {
       printf("Enter the option ON/OFF : \n");
       gets(option);
   }

   printf("\n");

   if( fp == NULL ) /*an dwsw lathos onoma*/
   {
      printf("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }

   while(fgets(line,100,fp) != NULL ) {
      for (i=0; i<strlen(line); i++) {
        tempo = line[i];
        if ((i+1) < strlen(line)) tempo2 = line[i+1]; /*elegxos an feugei apo to orio ths grammhs*/
        else tempo2 = ' ';
        if (STACKempty() && (tempo == ')' || tempo == '}' || tempo == ']' || (tempo == '*' && tempo2 == '/'))) {
            flag1 = 1;
        }
        if ((tempo != '"' && flag2 == 0) && (tempo != Array1[0] && flag3 == 0) && (!((tempo == '/' && tempo2 == '*') || (tempo == '*' && tempo2 == '/'))  && flag4 == 0) && flag1 == 0) { /*an den einai kapoios apo tous ",',/,*,kanei tis if*/
                if (tempo == '(') {
                    STACKpush(tempo);
                    chg++;
                }
                if (tempo == '{') {
                    STACKpush(tempo);
                    chg++;
                }
                if (tempo == '[') {
                    STACKpush(tempo);
                    chg++;
                }
//.....................................................................................
                if (tempo == ')' && head->item =='(') {
                    STACKpop();
                    chg++;
                }
                else if (tempo == ')' && (head->item == '{' || head->item == '[')) {
                    error = 1;
                    break;
                }
//.....................................................................................
                if (tempo == '}' && head->item =='{') {
                    STACKpop();
                    chg++;
                }
                else if (tempo == '}' && (head->item == '(' || head->item == '[')) {
                    error = 1;
                    break;
                }
//.....................................................................................
                if (tempo == ']' && head->item =='[') {
                    STACKpop();
                    chg++;
                }
                else if (tempo == ']' && (head->item == '}' || head->item == ')')) {
                    error = 1;
                    break;
                }
//.....................................................................................
        }
        else {
            if (tempo == '"' && flag3 == 0 && flag4 == 0 && error == 0 && flag1 == 0) { /*elegxei an de vriskontai mesa se kapoio sxolio h '*/
                flag2++;
                if (flag2 == 1) {
                        STACKpush(tempo);
                        chg++;
                }
                if (flag2 == 2) {
                        STACKpop();
                        chg++;
                        flag2 = 0;
                }
            }
            if (tempo == Array1[0] && flag2 == 0 && flag4 == 0 && error == 0 && flag1 == 0) { /*elegxei an to ' de vrisketai mesa se dipla h sxolia*/
                flag3++;
                if (flag3 == 1) {
                        STACKpush(tempo);
                        chg++;
                }
                if (flag3 == 2) {
                    STACKpop();
                    chg++;
                    flag3 = 0;
                }
            }
            if (tempo == '/' && flag3 == 0 && flag2 == 0 && error == 0 && flag1 == 0) { /*elegxei an einai to prwto symvolo sxoliou*/
                if (flag4 == 0){ /*an den eixe apo prin thn / */
                        flag4++;
                        j=i+1;
                        pass++;
                }

                if (flag4 == 2 && j == i) { /*an exei mpei prwta / kai amesws meta * */
                        STACKpop();
                        STACKpop();
                        chg++;
                        flag4 = 0;
                        flag5 = 0;
                        pass = 0;
                }
            }
            if (tempo == '*' && flag3 == 0 && flag2 == 0 && error == 0 && flag1 == 0) { /*elegxei an einai to deutero symvolo sxoliou*/
                flag5++;
                if (flag4 == 1 && j == i){ /*an to amesws prohgoumeno stoixeio htan h kathetos*/
                        pass = 0;
                        STACKpush('*');
                        STACKpush('/');
                        chg++;
                        j=i;
                }
                if (flag5 == 2 ) { /*vriskei deuterh fora to */
                        flag4++;
                        j=i+1;
                }
                if (flag5 > 2 ) { /*anairesh aukshshs metrhth*/
                        flag5-=1;
                        j=i+1;
                }
            }
            if (pass == 1 && tempo2 != '*') { /*an vrei thn / kai meta oxi to * tote mhdenizei pass kai flag4*/
                flag4 = 0;
                pass = 0;
            }
        }
        if (!(STACKempty()) && chg == 1 && (!strcmp(option,"ON"))) STACKprint();
        chg=0;
     }
     if (flag1 == 1 || error == 1) break; //an vrei kapoio akyro kleisimo tote vgazei lathos
     errorline++; /*metraei tis grammes ksekinontas apo to 1*/
   }
   if (STACKempty()) printf("\n");
   if (STACKempty() && flag1 == 0) printf("Parsing Complete!\n");
   else printf("Error in line %d\n", errorline);
   fclose(fp); /*kleinei to arxeio*/
   system("pause");
   return 0;
}
