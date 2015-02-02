%option noyywrap
%{
#include "tokens-manual.h"
#include <math.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
extern FILE *yyin;
int yylinenum = 1;
char **files;
int file_num;
int file_num_max;
extern int errno;
%}

DIG	[0-9]
LET	[a-zA-Z]
ID	[a-zA-Z][a-zA-Z0-9]*
HEXDIG	0[xX][0-9A-Fa-f]+
STRING	["].*["]
CHARLIT ['].*[']

%%

auto			{keyword(yyin,yylinenum,yytext);return AUTO;}
break			{keyword(yyin,yylinenum,yytext);return BREAK;}
case			{keyword(yyin,yylinenum,yytext);return CASE;}
char			{keyword(yyin,yylinenum,yytext);return CHAR;}
const			{keyword(yyin,yylinenum,yytext);return CONST;}
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
_Bool			{keyword(yyin,yylinenum,yytext);return _BOOL;}
_Complex		{keyword(yyin,yylinenum,yytext);return _COMPLEX;}
_Imaginary		{keyword(yyin,yylinenum,yytext);return _IMAGINARY;}


"++"			{printf("%s\t %d\t PLUSPLUS\n",yyin,yylinenum);}
"--"			{printf("%s\t %d\t MINUSMINUS\n",yyin,yylinenum);}
"..."			{printf("%s\t %d\t ELLIPSIS\n",yyin, yylinenum);}
"!="			{printf("%s\t %d\t NOTEQ\n",yyin, yylinenum);}
"+="			{printf("%s\t %d\t PLUSEQ\n",yyin, yylinenum);}
"-="			{printf("%s\t %d\t MINUSEQ\n",yyin, yylinenum);}
"/="			{printf("%s\t %d\t DIVEQ\n",yyin, yylinenum);}
"*="			{printf("%s\t %d\t TIMESEQ\n",yyin, yylinenum);}
"^="			{printf("%s\t %d\t XOREQ\n",yyin, yylinenum);}
"|="			{printf("%s\t %d\t OREQ\n",yyin, yylinenum);}
"&="			{printf("%s\t %d\t ANDEQ\n",yyin, yylinenum);}
"%="			{printf("%s\t %d\t MODEQ\n",yyin, yylinenum);}
"->"			{printf("%s\t %d\t INDSEL\n",yyin, yylinenum);}
"&&"			{printf("%s\t %d\t LOGAND\n",yyin, yylinenum);}
"||"			{printf("%s\t %d\t LOGOR\n",yyin, yylinenum);}
"<="			{printf("%s\t %d\t SHLEQ\n",yyin, yylinenum);}
">="			{printf("%s\t %d\t SHREQ\n",yyin, yylinenum);}
"<<="			{printf("%s\t %d\t SHLEQ\n",yyin, yylinenum);}
"<<"			{printf("%s\t %d\t SHL\n",yyin, yylinenum);}
">>="			{printf("%s\t %d\t SHREQ\n",yyin, yylinenum);}
">>"			{printf("%s\t %d\t SHR\n",yyin, yylinenum);}
"="			{printf("%s\t %d\t EQ\n",yyin, yylinenum);}

"["|"]"|"{"|"}"|"("|")"|"."|"+"|"-"|"&"|"*"|"~"|"!"|"/"|"%"|"<"|">"|"^"|"|"|"?"|":"|";"|","		{printf("%s\t %d\t %s\n",yyin, yylinenum, yytext);}

{STRING}		{printf("%s\t %d\t STRING\t %s\n",yyin, yylinenum, yytext);}
{CHARLIT}		{printf("%s\t %d\t CHARLIT %s\n",yyin, yylinenum, yytext);}

{DIG}+"."{DIG}*"L"	{printf("%s\t %d\t NUMBER\t REAL\t %g\t LONGDOUBLE\n",yyin, yylinenum, atof(yytext));}
{DIG}+"."{DIG}+		{printf("%s\t %d\t NUMBER\t REAL\t %g\t DOUBLE\n",yyin, yylinenum, atof(yytext));}
{DIG}+"e"{DIG}+"f"	{printf("%s\t %d\t NUMBER\t REAL\t %g\t FLOAT\n",yyin, yylinenum, atof(yytext));}
{DIG}+"e+"{DIG}+"f"	{printf("%s\t %d\t NUMBER\t REAL\t %g\t FLOAT\n",yyin, yylinenum, atof(yytext));}
{DIG}+"e"{DIG}+		{printf("%s\t %d\t NUMBER\t REAL\t %g\t DOUBLE\n",yyin, yylinenum, atof(yytext));}
{DIG}+"e+"{DIG}+	{printf("%s\t %d\t NUMBER\t REAL\t %g\t DOUBLE\n",yyin, yylinenum, atof(yytext));}

{DIG}+"LLU"		{printf("%s\t %d\t NUMBER\t INTEGER %lld\t UNSIGNED,LONGLONG\n",yyin, yylinenum, atol(yytext));}
{DIG}+"L"		{printf("%s\t %d\t NUMBER\t INTEGER %ld\t LONG\n",yyin, yylinenum, atol(yytext));}
{DIG}+"U"		{printf("%s\t %d\t NUMBER\t INTEGER %d\t UNSIGNED,INT\n",yyin, yylinenum, atoi(yytext));}

{HEXDIG}"L"		{printf("%s\t %d\t NUMBER\t INTEGER %s\t LONG\n", yyin,yylinenum,yytext);}

{DIG}+			{printf("%s\t %d\t NUMBER\t INTEGER %d\t INT\n",yyin, yylinenum, atoi(yytext));}
{HEXDIG}		{printf("%s\t %d\t NUMBER\t INTEGER %s\t INT\n", yyin,yylinenum,yytext);}
{ID}			{printf("%s\t %d\t IDENT\t %s\n",yyin, yylinenum, yytext);}


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


/*
file_num=1;
file_num_max=argc;
files=argv;
if(argc>1){
 if( (yyin = fopen(argv[file_num],"r"))== 0){
  perror(files[file_num]);
  exit(1);
 }
}
*/

while(yylex())
 ;

printf("\nEOF\n");
fclose(yyin);
}
