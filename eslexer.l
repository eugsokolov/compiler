%option noyywrap
%{
#include "tokens-manual.h"
#include <math.h>

int yylinenum = 1;


%}

DIG	[0-9]
LET	[a-zA-Z]
ID	[a-zA-Z][a-zA-Z0-9]*
HEXDIG	0[xX][0-9A-Fa-f]+|[\][xX][0-9A-Fa-f]+
STRING	["].*["]
CHARLIT ['].*[']

%%

auto			{keyword(yyin,yylinenum,yytext);return AUTO;}
break			{keyword(yyin,yylinenum,yytext);return BREAK;}
case			{keyword(yyin,yylinenum,yytext);return CASE;}
char			{keyword(yyin,yylinenum,yytext);return CHAR;}
continue		{keyword(yyin,yylinenum,yytext);return CONTINUE;}
default			{keyword(yyin,yylinenum,yytext);return DEFAULT;}
do			{keyword(yyin,yylinenum,yytext);return DO;}
double			{keyword(yyin,yylinenum,yytext);return DOUBLE;}
else			{keyword(yyin,yylinenum,yytext);return ELSE;}
enum			{keyword(yyin,yylinenum,yytext);return ENUM;}
extern			{keyword(yyin,yylinenum,yytext);return EXTERN;}
float			{keyword(yyin,yylinenum,yytext);return FLOAT;}
for			{keyword(yyin,yylinenum,yytext);return FOR;}
goto			{keyword(yyin,yylinenum,yytext);return GOTO;}
if			{keyword(yyin,yylinenum,yytext);return IF;}
inline			{keyword(yyin,yylinenum,yytext);return INLINE;}
int			{keyword(yyin,yylinenum,yytext);return INT;}
long			{keyword(yyin,yylinenum,yytext);return LONG;}
register		{keyword(yyin,yylinenum,yytext);return REGISTER;}
restrict		{keyword(yyin,yylinenum,yytext);return RESTRICT;}
return			{keyword(yyin,yylinenum,yytext);return RETURN;}
short			{keyword(yyin,yylinenum,yytext);return SHORT;}
signed			{keyword(yyin,yylinenum,yytext);return SIGNED;}
sizeof			{keyword(yyin,yylinenum,yytext);return SIZEOF;}
static			{keyword(yyin,yylinenum,yytext);return STATIC;}
struct			{keyword(yyin,yylinenum,yytext);return STRUCT;}
switch			{keyword(yyin,yylinenum,yytext);return SWITCH;}
typedef			{keyword(yyin,yylinenum,yytext);return TYPEDEF;}
union			{keyword(yyin,yylinenum,yytext);return UNION;}
unsigned		{keyword(yyin,yylinenum,yytext);return UNSIGNED;}
void			{keyword(yyin,yylinenum,yytext);return VOID;}
volatile		{keyword(yyin,yylinenum,yytext);return VOLATILE;}
while			{keyword(yyin,yylinenum,yytext);return WHILE;}


[++]			{printf("%s\t %d\t PLUSPLUS\n",yyin, yylinenum);}
[--]			{printf("%s\t %d\t MINUSMINUS\n",yyin, yylinenum);}

"["|"]"|"{"|"}"|"("|")"|"."|"+"|"-"|"&"|"*"|"~"|"!"|"/"|"%"|"<"|">"|"^"|"|"|"?"|":"|";"|","		{printf("%s\t %d\t %s\n",yyin, yylinenum, yytext);}

{STRING}		{printf("%s\t %d\t STRING\t %s\n",yyin, yylinenum, yytext);}
{CHARLIT}		{printf("%s\t %d\t CHARLIT\t %s\n",yyin, yylinenum, yytext);}

{DIG}+			{printf("%s\t %d\t NUMBER\t %d\n",yyin, yylinenum, atoi(yytext));}
{ID}			{printf("%s\t %d\t IDENT\t %s\n",yyin, yylinenum, yytext);}

{HEXDIG}		{printf("%s\t %d\t HEXDIG\t %s\n", yyin,yylinenum,yytext);}
{DIG}+"."{DIG}+		{printf("%s\t %d\t FLOAT\t %g\n",yyin, yylinenum, atof(yytext));}

[\n]			{yylinenum++;}
.			{fprintf(stderr,"Error: undefined token %s\n", yytext);exit(1);}
%%

keyword(char* yyin, int yylinenum, char* yytext){

char *p = yytext;
while(*p != '\0'){
 *p=toupper(*p);
 p++;
}
 printf("%s\t %d\t %s\n",yyin, yylinenum, yytext);
}

main(int argc, char *argv[]){

++argv, --argc;
if(argc > 0)
 yyin=fopen(argv[0], "r");
else
 yyin = stdin;

while(yylex())
 ;

printf("\nEOF\n");
}
