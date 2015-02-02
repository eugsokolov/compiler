%option noyywrap
%{
//EUGENE SOKOLOV
//COMPILERS ECE466
//LEXICAL ANALYSIS: lex.l

#include "tokens-manual.h"
#include <math.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int lineno = 1;
char filename[256];
char tmp[4095];

%}

%x IN_CHAR
%x IN_STRING
%x IN_FILE

DIG	[1-9][0-9]
OCTAL	0[0-7]
HEXDIG	[0-9A-Fa-f]

%%

auto		{keyword(yyin,lineno,yytext);return AUTO;}
break		{keyword(yyin,lineno,yytext);return BREAK;}
case		{keyword(yyin,lineno,yytext);return CASE;}
char		{keyword(yyin,lineno,yytext);return CHAR;}
const		{keyword(yyin,lineno,yytext);return CONST;}
continue	{keyword(yyin,lineno,yytext);return CONTINUE;}
default		{keyword(yyin,lineno,yytext);return DEFAULT;}
do		{keyword(yyin,lineno,yytext);return DO;}
double		{keyword(yyin,lineno,yytext);return DOUBLE;}
else		{keyword(yyin,lineno,yytext);return ELSE;}
enum		{keyword(yyin,lineno,yytext);return ENUM;}
extern		{keyword(yyin,lineno,yytext);return EXTERN;}
float		{keyword(yyin,lineno,yytext);return FLOAT;}
for		{keyword(yyin,lineno,yytext);return FOR;}
goto		{keyword(yyin,lineno,yytext);return GOTO;}
if		{keyword(yyin,lineno,yytext);return IF;}
inline		{keyword(yyin,lineno,yytext);return INLINE;}
int		{keyword(yyin,lineno,yytext);return INT;}
long		{keyword(yyin,lineno,yytext);return LONG;}
register	{keyword(yyin,lineno,yytext);return REGISTER;}
restrict	{keyword(yyin,lineno,yytext);return RESTRICT;}
return		{keyword(yyin,lineno,yytext);return RETURN;}
short		{keyword(yyin,lineno,yytext);return SHORT;}
signed		{keyword(yyin,lineno,yytext);return SIGNED;}
sizeof		{keyword(yyin,lineno,yytext);return SIZEOF;}
static		{keyword(yyin,lineno,yytext);return STATIC;}
struct		{keyword(yyin,lineno,yytext);return STRUCT;}
switch		{keyword(yyin,lineno,yytext);return SWITCH;}
typedef		{keyword(yyin,lineno,yytext);return TYPEDEF;}
union		{keyword(yyin,lineno,yytext);return UNION;}
unsigned	{keyword(yyin,lineno,yytext);return UNSIGNED;}
void		{keyword(yyin,lineno,yytext);return VOID;}
volatile	{keyword(yyin,lineno,yytext);return VOLATILE;}
while		{keyword(yyin,lineno,yytext);return WHILE;}
_Bool		{keyword(yyin,lineno,yytext);return _BOOL;}
_Complex	{keyword(yyin,lineno,yytext);return _COMPLEX;}
_Imaginary	{keyword(yyin,lineno,yytext);return _IMAGINARY;}

"++"		{printf("%s\t %d\t PLUSPLUS\n",yyin,lineno);}
"--"		{printf("%s\t %d\t MINUSMINUS\n",yyin,lineno);}
"..."		{printf("%s\t %d\t ELLIPSIS\n",yyin, lineno);}
"!="		{printf("%s\t %d\t NOTEQ\n",yyin, lineno);}
"+="		{printf("%s\t %d\t PLUSEQ\n",yyin, lineno);}
"-="		{printf("%s\t %d\t MINUSEQ\n",yyin, lineno);}
"/="		{printf("%s\t %d\t DIVEQ\n",yyin, lineno);}
"*="		{printf("%s\t %d\t TIMESEQ\n",yyin, lineno);}
"^="		{printf("%s\t %d\t XOREQ\n",yyin, lineno);}
"|="		{printf("%s\t %d\t OREQ\n",yyin, lineno);}
"&="		{printf("%s\t %d\t ANDEQ\n",yyin, lineno);}
"%="		{printf("%s\t %d\t MODEQ\n",yyin, lineno);}
"->"		{printf("%s\t %d\t INDSEL\n",yyin, lineno);}
"&&"		{printf("%s\t %d\t LOGAND\n",yyin, lineno);}
"||"		{printf("%s\t %d\t LOGOR\n",yyin, lineno);}
"<="		{printf("%s\t %d\t SHLEQ\n",yyin, lineno);}
">="		{printf("%s\t %d\t SHREQ\n",yyin, lineno);}
"<<="		{printf("%s\t %d\t SHLEQ\n",yyin, lineno);}
"<<"		{printf("%s\t %d\t SHL\n",yyin, lineno);}
">>="		{printf("%s\t %d\t SHREQ\n",yyin, lineno);}
">>"		{printf("%s\t %d\t SHR\n",yyin, lineno);}
"="		{printf("%s\t %d\t EQ\n",yyin, lineno);}
"["|"]"|"{"|"}"|"("|")"|"."|"+"|"-"|"&"|"*"|"~"|"!"|"/"|"%"|"<"|">"|"^"|"|"|"?"|":"|";"|","		{printf("%s\t %d\t %s\n",yyin, lineno, yytext);}
[\n]		{lineno++;}

[a-zA-Z][a-zA-Z0-9]*		{printf("%s\t %d\t IDENT\t %s\n",yyin, lineno, yytext);}

<INITIAL>\'			{BEGIN(IN_CHAR);}
<IN_CHAR>\' 			{BEGIN(INITIAL);     return CHARLIT;}
<IN_CHAR>\\['"?\\]		{}
<IN_CHAR>\\[abfnrtv]		{}
<IN_CHAR>\\[0-7]{1,3}		{}
<IN_CHAR>[\\0][xX][0-9A-Fa-f]+	{}
<IN_CHAR>[^\'\n\\]		{}

<INITIAL>\"			{BEGIN(IN_STRING);}
<IN_STRING>\" 			{BEGIN(INITIAL);    return STRING;}
<IN_STRING>\\['"?\\]		{}
<IN_STRING>\\[abfnrtv]		{}
<IN_STRING>\\[0-7]{1,3}		{}
<IN_STRING>[\\0][xX]{HEXDIG}+	{}
<IN_STRING>[^\"\n\\]		{}


{DIG}			{printf("%s\t %d\t NUMBER\t INTEGER %d\t INT\n",yyin, lineno, atoi(yytext));}
{DIG}[uU]		{printf("%s\t %d\t NUMBER\t INTEGER %u\t UNSIGNED,INT\n",yyin, lineno, atoi(yytext));}
{DIG}[lL]		{printf("%s\t %d\t NUMBER\t INTEGER %ld\t LONG\n",yyin, lineno, atol(yytext));}
{DIG}(ll|LL)		{printf("%s\t %d\t NUMBER\t INTEGER %lld\t LONGLONG\n",yyin, lineno, atoll(yytext));}
{DIG}([lL][uU])|([uU][lL])		{
	printf("%s\t %d\t NUMBER\t INTEGER %lu\t UNSIGNED,LONG\n",yyin, lineno, atol(yytext));}
{DIG}((ll|LL)[uU])|([uU](ll|LL))	{
	printf("%s\t %d\t NUMBER\t INTEGER %llu\t UNSIGNED,LONGLONG\n",yyin, lineno, atoll(yytext));}

{OCTAL}			{printf("%s\t %d\t NUMBER\t INTEGER %o\t INT\n",yyin, lineno, atoi(yytext));}
{OCTAL}[uU]		{printf("%s\t %d\t NUMBER\t INTEGER %o\t UNSIGNED,INT\n",yyin, lineno, atoi(yytext));}
{OCTAL}[lL]		{printf("%s\t %d\t NUMBER\t INTEGER %lo\t LONG\n",yyin, lineno, atol(yytext));}
{OCTAL}(ll|LL)		{printf("%s\t %d\t NUMBER\t INTEGER %llo\t LONGLONG\n",yyin, lineno, atoll(yytext));}
{OCTAL}([lL][uU])|([uU][lL])			{
	printf("%s\t %d\t NUMBER\t INTEGER %lo\t UNSIGNED,LONG\n",yyin, lineno, atol(yytext));}
{OCTAL}((ll|LL)[uU])|([uU](ll|LL))		{
	printf("%s\t %d\t NUMBER\t INTEGER %llo\t UNSIGNED,LONGLONG\n",yyin, lineno, atoll(yytext));}

\\[xX]{HEXDIG}		{printf("%s\t %d\t NUMBER\t INTEGER %x\t INT\n", yyin,lineno,yytext);}
0[xX]{HEXDIG}		{printf("%s\t %d\t NUMBER\t INTEGER %x\t INT\n", yyin,lineno,yytext);}
\\[xX]{HEXDIG}[uU]	{printf("%s\t %d\t NUMBER\t INTEGER %x\t INT\n", yyin,lineno,yytext);}
0[xX]{HEXDIG}[uU]	{printf("%s\t %d\t NUMBER\t INTEGER %x\t INT\n", yyin,lineno,yytext);}
\\[xX]{HEXDIG}[lL]	{printf("%s\t %d\t NUMBER\t INTEGER %llx\t LONG\n", yyin,lineno,yytext);}
0[xX]{HEXDIG}[lL]	{printf("%s\t %d\t NUMBER\t INTEGER %llx\t LONG\n", yyin,lineno,yytext);}
\\[xX]{HEXDIG}(LL|ll)	{printf("%s\t %d\t NUMBER\t INTEGER %llx\t LONGLONG\n", yyin,lineno,yytext);}
0[xX]{HEXDIG}(LL|ll)	{printf("%s\t %d\t NUMBER\t INTEGER %llx\t LONGLONG\n", yyin,lineno,yytext);}
\\[xX]{HEXDIG}([lL][uU])|([uU][lL])	{
	printf("%s\t %d\t NUMBER\t INTEGER %lx\t LONG\n", yyin,lineno,yytext);}
0[xX]{HEXDIG}([lL][uU])|([uU][lL])		{
	printf("%s\t %d\t NUMBER\t INTEGER %lx\t LONG\n", yyin,lineno,yytext);}
\\[xX]{HEXDIG}((ll|LL)[uU])|([uU](ll|LL))	{
	printf("%s\t %d\t NUMBER\t INTEGER %llx\t LONGLONG\n", yyin,lineno,yytext);}
0[xX]{HEXDIG}((ll|LL)[uU])|([uU](ll|LL))		{
	printf("%s\t %d\t NUMBER\t INTEGER %llx\t LONGLONG\n", yyin,lineno,yytext);}

{DIG}*\.{DIG}+		{printf("%s\t %d\t NUMBER\t REAL\t %g\t DOUBLE\n",yyin, lineno, atof(yytext));}
{DIG}|{OCTAL}|{HEXDIG}+"e"{DIG}+		{printf("%s\t %d\t NUMBER\t REAL\t %g\t DOUBLE\n",yyin, lineno, atof(yytext));}
{DIG}|{OCTAL}|{HEXDIG}+"e+"{DIG}+		{printf("%s\t %d\t NUMBER\t REAL\t %g\t DOUBLE\n",yyin, lineno, atof(yytext));}
{DIG}*\.{DIG}*"L"	{printf("%s\t %d\t NUMBER\t REAL\t %g\t LONGDOUBLE\n",yyin, lineno, atof(yytext));}
{DIG}+[eE][\+\-]?{DIG}+	{printf("%s\t %d\t NUMBER\t REAL\t %g\t FLOAT\n",yyin, lineno, atof(yytext));}
{DIG}+[eE][\+\-]?{DIG}+[fF]	{printf("%s\t %d\t NUMBER\t REAL\t %g\t FLOAT\n",yyin, lineno, atof(yytext));}


"\#"			{printf("pound\n");BEGIN(IN_FILE);}
<IN_FILE>{
"\n"			{BEGIN(0);}
[0-9]+ 			{lineno=atoi(yytext);}
L?\"(\\.|[^\\\"])*\" 	{strncpy(filename, yytext+1, strlen(yytext)-2);filename[strlen(yytext)-2]='\0';}
.			{}
}

.			{fprintf(stderr,"Error: undefined token %s\n", yytext);exit(1);}

%%

keyword(char* yyin, int lineno, char* yytext){

char *p = yytext;
while(*p != '\0'){
 *p=toupper(*p);
 p++;
}
 printf("%s\t %d\t %s\n",filename, lineno, yytext);
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
