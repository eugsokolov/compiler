%option noyywrap
%{
//EUGENE SOKOLOV
//COMPILERS ECE466
//LEXICAL ANALYSIS: lex.l

#include "tokens-manual.h"
#include "yylval.h"
#include <math.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

YYSTYPE yylval;

unsigned int lineno = 1;
char filename[MAX_STRING_LENGTH];
char *tmp_ptr;
char tmp_string[MAX_STRING_LENGTH];
%}

%x IN_CHAR IN_STRING IN_FILE

DIG	[1-9][0-9]
OCTAL	[0-7]
HEXDIG	[0-9A-Fa-f]+
EXP 	[eE][+-]?{DIG}+
MANT 	[pP][+-]?{DIG}+

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

[a-zA-Z][a-zA-Z0-9]*		{yylval.yystring=strdup(yytext); yylval.yystring_size = strlen(yytext); printf("%s\t %d\t IDENT\t %s\n",filename, lineno, yytext); return IDENT;}

\'		{BEGIN(IN_CHAR);}
<IN_CHAR>{
	\' 			{BEGIN(INITIAL);yylval.yychar=tmp_ptr;return CHARLIT;}
	\\[\'\"\?\\]		{*tmp_ptr++=(char*)yytext;}
	\\[abfnrtv]		{*tmp_ptr++=(char*)yytext;}
	\\[xX]{HEXDIG}+	{
		int result;
		sscanf(yytext+2, "%x", &result);
		if(result > 0xFF){
			fprintf(stderr, "%s: %d: Warning: Hex escape sequence %s out of range", filename, lineno, yytext);
			result='\0';
		}
		*tmp_ptr++=result;
	}
	[^\'\n\\]		{}
}

\"		{BEGIN(IN_STRING);}
<IN_STRING>{
	\" 			{BEGIN(INITIAL);yylval.yystring=strdup(tmp_string); yylval.yystring_size=strlen(tmp_string); return STRING;}
	\\[\'\"\?\\]		{*tmp_ptr++=(char*)yytext;}
	\\[abfnrtv]		{*tmp_ptr++=(char*)yytext;}
	\\[xX]{HEXDIG}+	{
		int result;
		sscanf(yytext+2, "%x", &result);
		if(result > 0xFF){
			fprintf(stderr, "%s: %d: Warning: Hex escape sequence %s out of range", filename, lineno, yytext);
			result='\0';
		}
		*tmp_ptr++=result;
	}
	[^\"\n\\]		{}
}

[1-9]+[0-9]*	{
	yylval.yyint=atoi(yytext);
	yylval.num_type=SIZE_INT;
	yylval.num_sign=SIZE_SIGNED;
	printf("%s\t %d\t NUMBER\t INTEGER %llu\t INT\n",filename, lineno, atoi(yytext));
	return NUMBER;
}
{DIG}+[uU]	{
	yylval.yyint=atoi(yytext);
	yylval.num_type=SIZE_INT;
	yylval.num_sign=SIZE_UNSIGNED;
	printf("%s\t %d\t NUMBER\t INTEGER %llu\t UNSIGNED,INT\n",filename, lineno, atoi(yytext));
	return NUMBER;
}
{DIG}+[lL]	{
	yylval.yyint=atol(yytext);
	yylval.num_type=SIZE_LONG;
	yylval.num_sign=SIZE_SIGNED;
	printf("%s\t %d\t NUMBER\t INTEGER %ld\t LONG\n",filename, lineno, atol(yytext));
	return NUMBER;
}
{DIG}+(ll|LL)	{
	yylval.yyint=atoll(yytext);
	yylval.num_type=SIZE_LONGLONG;
	yylval.num_sign=SIZE_SIGNED;
	printf("%s\t %d\t NUMBER\t INTEGER %lld\t LONGLONG\n",filename, lineno, atoll(yytext));
	return NUMBER;
}
{DIG}*"LU"	{
	yylval.yyint=atol(yytext);
	yylval.num_type=SIZE_LONG;
	yylval.num_sign=SIZE_UNSIGNED;
	printf("%s\t %d\t NUMBER\t INTEGER %lu\t UNSIGNED,LONG\n",filename, lineno, atol(yytext));
	return NUMBER;
}
{DIG}+((ll|LL)[uU])|([uU](ll|LL)) {
	yylval.yyint=atoll(yytext);
	yylval.num_type=SIZE_LONGLONG;
	yylval.num_sign=SIZE_UNSIGNED;
	printf("%s\t %d\t NUMBER\t INTEGER %llu\t UNSIGNED,LONGLONG\n",filename, lineno, atoll(yytext));
	return NUMBER;
}

0{OCTAL}*	{
	yylval.num_type=SIZE_INT;
	yylval.num_sign=SIZE_SIGNED;
	printf("%s\t %llo\t NUMBER\t INTEGER %o\t INT\n",filename, lineno, atoi(yytext));
	return NUMBER;
}
0{OCTAL}+[uU]	{
	yylval.num_type=SIZE_INT;
	yylval.num_sign=SIZE_UNSIGNED;
	printf("%s\t %llo\t NUMBER\t INTEGER %o\t UNSIGNED,INT\n",filename, lineno, atoi(yytext));
	return NUMBER;
}
0{OCTAL}*[lL]	{
	yylval.num_type=SIZE_LONG;
	yylval.num_sign=SIZE_SIGNED;
	printf("%s\t %llo\t NUMBER\t INTEGER %lo\t LONG\n",filename, lineno, atol(yytext));
	return NUMBER;
}
0{OCTAL}+(ll|LL){
	yylval.num_type=SIZE_LONGLONG;
	yylval.num_sign=SIZE_SIGNED;
	printf("%s\t %llo\t NUMBER\t INTEGER %llo\t LONGLONG\n",filename, lineno, atoll(yytext));
	return NUMBER;
}
0{OCTAL}+([lL][uU])|([uU][lL])	{
	yylval.num_type=SIZE_LONG;
	yylval.num_sign=SIZE_UNSIGNED;
	printf("%s\t %d\t NUMBER\t INTEGER %llo\t UNSIGNED,LONG\n",filename, lineno, atol(yytext));
	return NUMBER;}
0{OCTAL}+((ll|LL)[uU])|([uU](ll|LL)){
	yylval.num_type=SIZE_LONGLONG;
	yylval.num_sign=SIZE_UNSIGNED;
	printf("%s\t %d\t NUMBER\t INTEGER %llo\t UNSIGNED,LONGLONG\n",filename, lineno, atoll(yytext));
	return NUMBER;
}

[\\0][xX]{HEXDIG}		{
	yylval.num_type=SIZE_INT;
	yylval.num_sign=SIZE_SIGNED;
	printf("%s\t %llx\t NUMBER\t INTEGER %x\t INT\n", filename,lineno,yytext);
	return NUMBER;
}
[\\0][xX]{HEXDIG}[uU]		{
	yylval.num_type=SIZE_INT;
	yylval.num_sign=SIZE_UNSIGNED;
	printf("%s\t %llx\t NUMBER\t INTEGER %x\t INT\n", filename,lineno,yytext);
	return NUMBER;
}
[\\0][xX]{HEXDIG}[lL]		{
	yylval.num_type=SIZE_LONG;
	yylval.num_sign=SIZE_SIGNED;
	printf("%s\t %llx\t NUMBER\t INTEGER %llx\t LONG\n", filename,lineno,yytext);
	return NUMBER;
}
[\\0][xX]{HEXDIG}(LL|ll)	{
	yylval.num_type=SIZE_LONGLONG;
	yylval.num_sign=SIZE_SIGNED;
	printf("%s\t %llx\t NUMBER\t INTEGER %llx\t LONGLONG\n", filename,lineno,yytext);
	return NUMBER;
}
[\\0][xX]{HEXDIG}([lL][uU])|([uU][lL])	{
	yylval.num_type=SIZE_LONG;
	yylval.num_sign=SIZE_UNSIGNED;
	printf("%s\t %d\t NUMBER\t INTEGER %llx\t LONG\n", filename,lineno,yytext);
	return NUMBER;
}
[\\0][xX]{HEXDIG}((ll|LL)[uU])|([uU](ll|LL)){
	yylval.num_type=SIZE_LONGLONG;
	yylval.num_sign=SIZE_UNSIGNED;
	printf("%s\t %d\t NUMBER\t INTEGER %llx\t LONGLONG\n", filename,lineno,yytext);
	return NUMBER;
}


{DIG}*\.{DIG}+		{
	yylval.yydouble=atof(yytext);
	yylval.num_type=SIZE_DOUBLE;
	yylval.num_sign=SIZE_SIGNED;
	printf("%s\t %d\t NUMBER\t REAL\t %Lg\t DOUBLE\n",filename, lineno, atof(yytext));
	return NUMBER;
}
{DIG}|{OCTAL}|{HEXDIG}+{EXP}{
	yylval.yydouble=atof(yytext);
	yylval.num_type=SIZE_DOUBLE;
	yylval.num_sign=SIZE_SIGNED;
	printf("%s\t %d\t NUMBER\t REAL\t %Lg\t DOUBLE\n",filename, lineno, atof(yytext));
	return NUMBER;
}

{DIG}*\.{DIG}*"L"	{
	yylval.yydouble=atof(yytext);
	yylval.num_type=SIZE_LONGDOUBLE;
	yylval.num_sign=SIZE_SIGNED;
	printf("%s\t %d\t NUMBER\t REAL\t %Lg\t LONGDOUBLE\n",filename, lineno, atof(yytext));
	return NUMBER;
}
{DIG}+{EXP}	{
	yylval.yydouble=atof(yytext);
	yylval.num_type=SIZE_DOUBLE;
	yylval.num_sign=SIZE_SIGNED;
	printf("%s\t %d\t NUMBER\t REAL\t %Lg\t FLOAT\n",filename, lineno, atof(yytext));
	return NUMBER;
}
{DIG}+{MANT}	{
	yylval.yydouble=atof(yytext);
	yylval.num_type=SIZE_FLOAT;
	yylval.num_sign=SIZE_SIGNED;
	printf("%s\t %d\t NUMBER\t REAL\t %Lg\t FLOAT\n",filename, lineno, atof(yytext));
	return NUMBER;
}
{DIG}+{EXP}[fF]	{
	yylval.yydouble=atof(yytext);
	yylval.num_type=SIZE_FLOAT;
	yylval.num_sign=SIZE_SIGNED;
	printf("%s\t %d\t NUMBER\t REAL\t %Lg\t FLOAT\n",filename, lineno, atof(yytext));
	return NUMBER;
}


#			{printf("pound\n");BEGIN(IN_FILE);}
<IN_FILE>{
\\n			{BEGIN(INITIAL);}
[0-9]+ 			{lineno=atoi(yytext);}
\"(\\.|[^\\\"])*\" 	{strncpy(filename, yytext+1, strlen(yytext)-2);filename[strlen(yytext)-2]='\0';}
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
