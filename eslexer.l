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

auto		{keyword(lineno,yytext);return AUTO;}
break		{keyword(lineno,yytext);return BREAK;}
case		{keyword(lineno,yytext);return CASE;}
char		{keyword(lineno,yytext);return CHAR;}
const		{keyword(lineno,yytext);return CONST;}
continue	{keyword(lineno,yytext);return CONTINUE;}
default		{keyword(lineno,yytext);return DEFAULT;}
do		{keyword(lineno,yytext);return DO;}
double		{keyword(lineno,yytext);return DOUBLE;}
else		{keyword(lineno,yytext);return ELSE;}
enum		{keyword(lineno,yytext);return ENUM;}
extern		{keyword(lineno,yytext);return EXTERN;}
float		{keyword(lineno,yytext);return FLOAT;}
for		{keyword(lineno,yytext);return FOR;}
goto		{keyword(lineno,yytext);return GOTO;}
if		{keyword(lineno,yytext);return IF;}
inline		{keyword(lineno,yytext);return INLINE;}
int		{keyword(lineno,yytext);return INT;}
long		{keyword(lineno,yytext);return LONG;}
register	{keyword(lineno,yytext);return REGISTER;}
restrict	{keyword(lineno,yytext);return RESTRICT;}
return		{keyword(lineno,yytext);return RETURN;}
short		{keyword(lineno,yytext);return SHORT;}
signed		{keyword(lineno,yytext);return SIGNED;}
sizeof		{keyword(lineno,yytext);return SIZEOF;}
static		{keyword(lineno,yytext);return STATIC;}
struct		{keyword(lineno,yytext);return STRUCT;}
switch		{keyword(lineno,yytext);return SWITCH;}
typedef		{keyword(lineno,yytext);return TYPEDEF;}
union		{keyword(lineno,yytext);return UNION;}
unsigned	{keyword(lineno,yytext);return UNSIGNED;}
void		{keyword(lineno,yytext);return VOID;}
volatile	{keyword(lineno,yytext);return VOLATILE;}
while		{keyword(lineno,yytext);return WHILE;}
_Bool		{keyword(lineno,yytext);return _BOOL;}
_Complex	{keyword(lineno,yytext);return _COMPLEX;}
_Imaginary	{keyword(lineno,yytext);return _IMAGINARY;}

"++"		{printf("%s\t %d\t PLUSPLUS\n",filename,lineno);}
"--"		{printf("%s\t %d\t MINUSMINUS\n",filename,lineno);}
"..."		{printf("%s\t %d\t ELLIPSIS\n",filename, lineno);}
"!="		{printf("%s\t %d\t NOTEQ\n",filename, lineno);}
"+="		{printf("%s\t %d\t PLUSEQ\n",filename, lineno);}
"-="		{printf("%s\t %d\t MINUSEQ\n",filename, lineno);}
"/="		{printf("%s\t %d\t DIVEQ\n",filename, lineno);}
"*="		{printf("%s\t %d\t TIMESEQ\n",filename, lineno);}
"^="		{printf("%s\t %d\t XOREQ\n",filename, lineno);}
"|="		{printf("%s\t %d\t OREQ\n",filename, lineno);}
"&="		{printf("%s\t %d\t ANDEQ\n",filename, lineno);}
"%="		{printf("%s\t %d\t MODEQ\n",filename, lineno);}
"->"		{printf("%s\t %d\t INDSEL\n",filename, lineno);}
"&&"		{printf("%s\t %d\t LOGAND\n",filename, lineno);}
"||"		{printf("%s\t %d\t LOGOR\n",filename, lineno);}
"<="		{printf("%s\t %d\t SHLEQ\n",filename, lineno);}
">="		{printf("%s\t %d\t SHREQ\n",filename, lineno);}
"<<="		{printf("%s\t %d\t SHLEQ\n",filename, lineno);}
"<<"		{printf("%s\t %d\t SHL\n",filename, lineno);}
">>="		{printf("%s\t %d\t SHREQ\n",filename, lineno);}
">>"		{printf("%s\t %d\t SHR\n",filename, lineno);}
"="		{printf("%s\t %d\t EQ\n",filename, lineno);}
"["|"]"|"{"|"}"|"("|")"|"."|"+"|"-"|"&"|"*"|"~"|"!"|"/"|"%"|"<"|">"|"^"|"|"|"?"|":"|";"|","		{printf("%s\t %d\t %s\n",yyin, lineno, yytext);}
[\n]		{lineno++;}

[a-zA-Z][a-zA-Z0-9]*		{printf("%s\t %d\t IDENT\t %s\n",filename, lineno, yytext);}

/* Single character */
/* http://stackoverflow.com/questions/5403103/hex-to-ascii-string-conversion */
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
<IN_STRING>[\\0][xX]{HEXDIG}+	{} /* strtol with radix 16 or sscanf*/
<IN_STRING>[^\"\n\\]		{}


{DIG}			{printf("%s\t %d\t NUMBER\t INTEGER %d\t INT\n",filename, lineno, atoi(yytext));}
{DIG}[uU]		{printf("%s\t %d\t NUMBER\t INTEGER %u\t UNSIGNED,INT\n",filename, lineno, atoi(yytext));}
{DIG}[lL]		{printf("%s\t %d\t NUMBER\t INTEGER %ld\t LONG\n",filename, lineno, atol(yytext));}
{DIG}(ll|LL)		{printf("%s\t %d\t NUMBER\t INTEGER %lld\t LONGLONG\n",filename, lineno, atoll(yytext));}
{DIG}([lL][uU])|([uU][lL])		{
	printf("%s\t %d\t NUMBER\t INTEGER %lu\t UNSIGNED,LONG\n",filename, lineno, atol(yytext));}
{DIG}((ll|LL)[uU])|([uU](ll|LL))	{
	printf("%s\t %d\t NUMBER\t INTEGER %llu\t UNSIGNED,LONGLONG\n",filename, lineno, atoll(yytext));}

{OCTAL}			{printf("%s\t %llo\t NUMBER\t INTEGER %o\t INT\n",filename, lineno, atoi(yytext));}
{OCTAL}[uU]		{printf("%s\t %llo\t NUMBER\t INTEGER %o\t UNSIGNED,INT\n",filename, lineno, atoi(yytext));}
{OCTAL}[lL]		{printf("%s\t %llo\t NUMBER\t INTEGER %lo\t LONG\n",filename, lineno, atol(yytext));}
{OCTAL}(ll|LL)		{printf("%s\t %llo\t NUMBER\t INTEGER %llo\t LONGLONG\n",filename, lineno, atoll(yytext));}
{OCTAL}([lL][uU])|([uU][lL])			{
	printf("%s\t %d\t NUMBER\t INTEGER %llo\t UNSIGNED,LONG\n",filename, lineno, atol(yytext));}
{OCTAL}((ll|LL)[uU])|([uU](ll|LL))		{
	printf("%s\t %d\t NUMBER\t INTEGER %llo\t UNSIGNED,LONGLONG\n",filename, lineno, atoll(yytext));}

\\[xX]{HEXDIG}		{printf("%s\t %llx\t NUMBER\t INTEGER %x\t INT\n", filename,lineno,yytext);}
0[xX]{HEXDIG}		{printf("%s\t %llx\t NUMBER\t INTEGER %x\t INT\n", filename,lineno,yytext);}
\\[xX]{HEXDIG}[uU]	{printf("%s\t %llx\t NUMBER\t INTEGER %x\t INT\n", filename,lineno,yytext);}
0[xX]{HEXDIG}[uU]	{printf("%s\t %llx\t NUMBER\t INTEGER %x\t INT\n", filename,lineno,yytext);}
\\[xX]{HEXDIG}[lL]	{printf("%s\t %llx\t NUMBER\t INTEGER %llx\t LONG\n", filename,lineno,yytext);}
0[xX]{HEXDIG}[lL]	{printf("%s\t %llx\t NUMBER\t INTEGER %llx\t LONG\n", filename,lineno,yytext);}
\\[xX]{HEXDIG}(LL|ll)	{printf("%s\t %llx\t NUMBER\t INTEGER %llx\t LONGLONG\n", filename,lineno,yytext);}
0[xX]{HEXDIG}(LL|ll)	{printf("%s\t %llx\t NUMBER\t INTEGER %llx\t LONGLONG\n", filename,lineno,yytext);}
\\[xX]{HEXDIG}([lL][uU])|([uU][lL])	{
	printf("%s\t %d\t NUMBER\t INTEGER %llx\t LONG\n", filename,lineno,yytext);}
0[xX]{HEXDIG}([lL][uU])|([uU][lL])		{
	printf("%s\t %d\t NUMBER\t INTEGER %llx\t LONG\n", filename,lineno,yytext);}
\\[xX]{HEXDIG}((ll|LL)[uU])|([uU](ll|LL))	{
	printf("%s\t %d\t NUMBER\t INTEGER %llx\t LONGLONG\n", filename,lineno,yytext);}
0[xX]{HEXDIG}((ll|LL)[uU])|([uU](ll|LL))		{
	printf("%s\t %d\t NUMBER\t INTEGER %llx\t LONGLONG\n", filename,lineno,yytext);}

{DIG}*\.{DIG}+		{printf("%s\t %d\t NUMBER\t REAL\t %g\t DOUBLE\n",filename, lineno, atof(yytext));}
{DIG}|{OCTAL}|{HEXDIG}+"e"{DIG}+		{printf("%s\t %d\t NUMBER\t REAL\t %g\t DOUBLE\n",filename, lineno, atof(yytext));}
{DIG}|{OCTAL}|{HEXDIG}+"e+"{DIG}+		{printf("%s\t %d\t NUMBER\t REAL\t %g\t DOUBLE\n",filename, lineno, atof(yytext));}
{DIG}*\.{DIG}*"L"	{printf("%s\t %d\t NUMBER\t REAL\t %Lg\t LONGDOUBLE\n",filename, lineno, atof(yytext));}
{DIG}+[eE][\+\-]?{DIG}+	{printf("%s\t %d\t NUMBER\t REAL\t %g\t FLOAT\n",filename, lineno, atof(yytext));}
{DIG}+[eE][\+\-]?{DIG}+[fF]	{printf("%s\t %d\t NUMBER\t REAL\t %g\t FLOAT\n",filename, lineno, atof(yytext));}


"\#"			{printf("pound\n");BEGIN(IN_FILE);}
<IN_FILE>{
"\n"			{BEGIN(0);}
[0-9]+ 			{lineno=atoi(yytext);}
L?\"(\\.|[^\\\"])*\" 	{strncpy(filename, yytext+1, strlen(yytext)-2);filename[strlen(yytext)-2]='\0';}
.			{}
}

.			{fprintf(stderr,"Error: undefined token %s\n", yytext);exit(1);}

%%

keyword(int lineno, char* yytext){

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
