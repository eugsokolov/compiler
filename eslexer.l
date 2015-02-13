%option noyywrap
%{
//EUGENE SOKOLOV
//COMPILERS ECE466
//LEXICAL ANALYSIS: lex.l

#include "tokens-manual.h"
#include "yylval.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

YYSTYPE yylval;

unsigned int lineno = 1;
unsigned int string_length = 0;
char filename[MAX_STRING_LENGTH];
char *tmp_ptr;
char tmp_string[MAX_STRING_LENGTH];
%}

%x IN_CHAR IN_STRING IN_FILE

DIG	[1-9]+[0-9]*
OCT	0[0-7]*
HEX	[\\0][xX][0-9A-Fa-f]+
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

"++"		{printf("%s\t %d\t PLUSPLUS\n",filename,lineno);return PLUSPLUS;}
"--"		{printf("%s\t %d\t MINUSMINUS\n",filename,lineno);return MINUSMINUS;}
"..."		{printf("%s\t %d\t ELLIPSIS\n",filename, lineno);return ELLIPSIS;}
"!="		{printf("%s\t %d\t NOTEQ\n",filename, lineno);return NOTEQ;}
"+="		{printf("%s\t %d\t PLUSEQ\n",filename, lineno);return PLUSEQ;}
"-="		{printf("%s\t %d\t MINUSEQ\n",filename, lineno);return MINUSEQ;}
"/="		{printf("%s\t %d\t DIVEQ\n",filename, lineno);return DIVEQ;}
"*="		{printf("%s\t %d\t TIMESEQ\n",filename, lineno);return TIMESEQ;}
"^="		{printf("%s\t %d\t XOREQ\n",filename, lineno);return XOREQ;}
"|="		{printf("%s\t %d\t OREQ\n",filename, lineno);return OREQ;}
"&="		{printf("%s\t %d\t ANDEQ\n",filename, lineno);return ANDEQ;}
"%="		{printf("%s\t %d\t MODEQ\n",filename, lineno);return MODEQ;}
"->"		{printf("%s\t %d\t INDSEL\n",filename, lineno);return INDSEL;}
"&&"		{printf("%s\t %d\t LOGAND\n",filename, lineno);return LOGAND;}
"||"		{printf("%s\t %d\t LOGOR\n",filename, lineno);return LOGOR;}
"<="		{printf("%s\t %d\t LTEQ\n",filename, lineno);return LTEQ;}
">="		{printf("%s\t %d\t GTEQ\n",filename, lineno);return GTEQ;}
"<<="		{printf("%s\t %d\t SHLEQ\n",filename, lineno);return SHLEQ;}
"<<"		{printf("%s\t %d\t SHL\n",filename, lineno);return SHL;}
">>="		{printf("%s\t %d\t SHREQ\n",filename, lineno);return SHREQ;}
">>"		{printf("%s\t %d\t SHR\n",filename, lineno);return SHR;}
"=="		{printf("%s\t %d\t EQEQ\n",filename, lineno);return EQEQ;}
"["|"]"|"{"|"}"|"("|")"|"."|"+"|"-"|"&"|"*"|"~"|"!"|"/"|"%"|"<"|">"|"^"|"|"|"?"|":"|";"|","|"=" 	{printf("%s\t %d\t %s\n",filename, lineno, yytext);}
[\n]		{lineno++;}

[a-zA-Z][a-zA-Z0-9]*	{
	yylval.word.yystring=strdup(yytext);
	yylval.word.yystring_size=strlen(yytext);
	return IDENT;
}

\' 	{tmp_ptr=tmp_string;string_length=0;BEGIN(IN_CHAR);}
\" 	{tmp_ptr=tmp_string;string_length=0;BEGIN(IN_STRING);}

<IN_CHAR>{
\'	{
	BEGIN(INITIAL); 
	*tmp_ptr = '\0'; 
	yylval.word.yychar = tmp_string[0]; 
	return CHARLIT;
	}
\n 	{fprintf(stderr, "%s:%d:Error:Unterminated string constant\n", filename, lineno);exit(1);}
\\0 	{*tmp_ptr='\0';tmp_ptr++;}
\\a 	{*tmp_ptr='\a';tmp_ptr++;}
\\b 	{*tmp_ptr='\b';tmp_ptr++;}
\\f 	{*tmp_ptr='\f';tmp_ptr++;}
\\n 	{*tmp_ptr='\n';tmp_ptr++;}
\\r 	{*tmp_ptr='\r';tmp_ptr++;}
\\t 	{*tmp_ptr='\t';tmp_ptr++;}
\\v 	{*tmp_ptr='\v';tmp_ptr++;}
\\\" 	{*tmp_ptr='\"';tmp_ptr++;}
\\\\ 	{*tmp_ptr='\\';tmp_ptr++;}
\\\' 	{*tmp_ptr='\'';tmp_ptr++;}
\\[0-7]{1,3} {
        int tmp;
        sscanf(yytext+1, "%o", &tmp);
        if (tmp > 0xff){
            fprintf(stderr, "%s:%d:Warning:Octal escape sequence %s out of range", filename, lineno, yytext);
            tmp = '\377';
        }
        *tmp_ptr=tmp;
	tmp_ptr++;
    }
\\x[0-9a-fA-F]+ {
        int tmp;
        sscanf(yytext+2, "%x", &tmp);
        if (tmp > 0xff){
            fprintf(stderr, "%s:%d:Warning:Hex escape sequence %s out of range", filename, lineno, yytext);
            tmp = '\377';
        }
        *tmp_ptr=tmp;
	tmp_ptr++;
    }
\\(.|\n) 	{*tmp_ptr=yytext[1];tmp_ptr++;}
[^\\\'\n]* 	{
	char *yptr = yytext;
        while (*yptr){
		*tmp_ptr = *yptr++;
		tmp_ptr++;
	}
    }
}

<IN_STRING>{
\" 	{
	BEGIN(INITIAL); 
	*tmp_ptr = '\0'; 
	yylval.word.yystring = tmp_string; 
	return STRING;
	}
\n 	{fprintf(stderr, "%s:%d:Error:Unterminated string constant\n", filename, lineno);exit(1);}
\\0 	{*tmp_ptr='\0';tmp_ptr++;}
\\a 	{*tmp_ptr='\a';tmp_ptr++;}
\\b 	{*tmp_ptr='\b';tmp_ptr++;}
\\f 	{*tmp_ptr='\f';tmp_ptr++;}
\\n 	{*tmp_ptr='\n';tmp_ptr++;}
\\r 	{*tmp_ptr='\r';tmp_ptr++;}
\\t 	{*tmp_ptr='\t';tmp_ptr++;}
\\v 	{*tmp_ptr='\v';tmp_ptr++;}
\\\" 	{*tmp_ptr='\"';tmp_ptr++;}
\\\\ 	{*tmp_ptr='\\';tmp_ptr++;}
\\\' 	{*tmp_ptr='\'';tmp_ptr++;}
\\[0-7]{1,3} {
        int tmp;
        sscanf(yytext+1, "%o", &tmp);
        if (tmp > 0xff){
            fprintf(stderr, "%s:%d:Warning:Octal escape sequence %s out of range\n", filename, lineno, yytext);
            tmp = '\377';
        }
        *tmp_ptr=tmp;
	tmp_ptr++;
    }
\\x[0-9a-fA-F]+ {
        int tmp;
        sscanf(yytext+2, "%x", &tmp);
        if (tmp > 0xff){
            fprintf(stderr, "%s:%d:Warning:Hex escape sequence %s out of range\n", filename, lineno, yytext);
            tmp = '\377';
        }
        *tmp_ptr=tmp;
	tmp_ptr++;
    }
\\(.|\n) 	{*tmp_ptr=yytext[1];tmp_ptr++;}
[^\\\"\n]* 	{
        char *yptr = yytext;
        while (*yptr){
		*tmp_ptr=*yptr++;
		*tmp_ptr++;
	}
    }
}

{DIG}	{
	yylval.number.yyint=atoi(yytext);
	yylval.number.num_type=TYPE_INT;
	yylval.number.num_sign=TYPE_SIGNED;
	return NUMBER;
}
{DIG}"U"	{
	yytext[yyleng-1] = '\0';
	yylval.number.yyint=atoi(yytext);
	yylval.number.num_type=TYPE_INT;
	yylval.number.num_sign=TYPE_UNSIGNED;
	return NUMBER;
}

{DIG}"L"	{
	yytext[yyleng-1] = '\0';
	yylval.number.yyint=atoi(yytext);
	yylval.number.num_type=TYPE_LONG;
	yylval.number.num_sign=TYPE_SIGNED;
	return NUMBER;
}
{DIG}"LL"	{	
	yytext[yyleng-2] = '\0';
	yylval.number.yyint=atoi(yytext);
	yylval.number.num_type=TYPE_LONGLONG;
	yylval.number.num_sign=TYPE_SIGNED;
	return NUMBER;
}
{DIG}"LLU"	{
	yytext[yyleng-3] = '\0';
	yylval.number.yyint=atoi(yytext);
	yylval.number.num_type=TYPE_LONGLONG;
	yylval.number.num_sign=TYPE_UNSIGNED;
	return NUMBER;
}

{OCT}	{
	sscanf(yytext, "%llo", &yylval.number.yyint);
	yylval.number.num_type=TYPE_INT;
	yylval.number.num_sign=TYPE_SIGNED;
	return NUMBER;
}
{OCT}"U"	{
	yytext[yyleng-1] = '\0';
	sscanf(yytext, "%llo", &yylval.number.yyint);
	yylval.number.num_type=TYPE_INT;
	yylval.number.num_sign=TYPE_UNSIGNED;
	return NUMBER;
}
{OCT}"L"	{
	yytext[yyleng-1] = '\0';
	sscanf(yytext, "%llo", &yylval.number.yyint);
	yylval.number.num_type=TYPE_LONG;
	yylval.number.num_sign=TYPE_SIGNED;
	return NUMBER;
}
{OCT}"LL"	{
	yytext[yyleng-2] = '\0';
	sscanf(yytext, "%llo", &yylval.number.yyint);
	yylval.number.num_type=TYPE_LONGLONG;
	yylval.number.num_sign=TYPE_SIGNED;
	return NUMBER;
}
{OCT}"LLU"	{
	yytext[yyleng-3] = '\0';
	sscanf(yytext, "%llo", &yylval.number.yyint);
	yylval.number.num_type=TYPE_LONGLONG;
	yylval.number.num_sign=TYPE_UNSIGNED;
	return NUMBER;
}

{HEX}	{
	sscanf(yytext, "%llx", &yylval.number.yyint);
	yylval.number.num_type=TYPE_INT;
	yylval.number.num_sign=TYPE_SIGNED;
	return NUMBER;
}
{HEX}"U"	{
	yytext[yyleng-1] = '\0';
	sscanf(yytext, "%llx", &yylval.number.yyint);
	yylval.number.num_type=TYPE_INT;
	yylval.number.num_sign=TYPE_UNSIGNED;
	return NUMBER;
}
{HEX}"L"	{
	yytext[yyleng-1] = '\0';
	sscanf(yytext, "%llx", &yylval.number.yyint);
	yylval.number.num_type=TYPE_LONG;
	yylval.number.num_sign=TYPE_SIGNED;
	return NUMBER;
}
{HEX}"LL"	{
	yytext[yyleng-2] = '\0';
	sscanf(yytext, "%llx", &yylval.number.yyint);
	yylval.number.num_type=TYPE_LONGLONG;
	yylval.number.num_sign=TYPE_SIGNED;
	return NUMBER;
}
{HEX}"LLU"	{
	yytext[yyleng-3] = '\0';
	sscanf(yytext, "%llx", &yylval.number.yyint);
	yylval.number.num_type=TYPE_LONGLONG;
	yylval.number.num_sign=TYPE_UNSIGNED;
	return NUMBER;
}

[0-9]*\.[0-9]*		{
	sscanf(yytext, "%Lf", &yylval.number.yydouble);
	yylval.number.num_type=TYPE_DOUBLE;
	yylval.number.num_sign=TYPE_SIGNED;
	return NUMBER;
}
[0-9]*\.[0-9]*"L"	{
	yytext[yyleng-1] = '\0';
	sscanf(yytext, "%Lf", &yylval.number.yydouble);
	yylval.number.num_type=TYPE_LONGDOUBLE;
	yylval.number.num_sign=TYPE_SIGNED;
	return NUMBER;
}

({DIG}|{OCT})+{EXP}		{
	sscanf(yytext, "%Lf", &yylval.number.yydouble);
	yylval.number.num_type=TYPE_DOUBLE;
	yylval.number.num_sign=TYPE_SIGNED;
	return NUMBER;
}
({DIG}|{OCT}|{HEX})+{MANT}		{
	sscanf(yytext, "%Lf", &yylval.number.yydouble);
	yylval.number.num_type=TYPE_DOUBLE;
	yylval.number.num_sign=TYPE_SIGNED;
	return NUMBER;
}

{DIG}+{EXP}"f"		{
	yytext[yyleng-1] = '\0';
	sscanf(yytext, "%Lf", &yylval.number.yydouble);
	yylval.number.num_type=TYPE_FLOAT;
	yylval.number.num_sign=TYPE_SIGNED;
	return NUMBER;
}

#				{BEGIN(IN_FILE);}
<IN_FILE>{
	\n			{BEGIN(INITIAL);}
	[0-9]+ 			{}
	\"(\\.|[^\\\"])*\" 	{strncpy(filename, yytext+1, strlen(yytext)-2);filename[strlen(yytext)-2]='\0';}
	.			{}
}

.			{fprintf(stderr,"Error: undefined token %s\n", yytext);exit(1);}

%%


printchars(char *str, char *end){
	while (str != end){
		switch (*str){
		    case '\0':
		        printf("\\0");
		    case '\a':
		        printf("\\a");
		        break;
		    case '\b':
		        printf("\\b");
		        break;
		    case '\f':
		        printf("\\f");
		        break;
		    case '\n':
		        printf("\\n");
		        break;
		    case '\r':
		        printf("\\r");
		        break;
		    case '\t':
		        printf("\\t");
		        break;
		    case '\v':
		        printf("\\v");
		        break;
		    case '\"':
		        printf("\\\"");
		        break;
		        break;
		    case '\\':
		        printf("\\\\");
		        break;
		    case '\'':
		        printf("\\\'");
		        break;
		    default:
		        if (*str > 126 || *str < 32){
		            printf("\\%03o", (unsigned char)*str);
		        } else {
		            printf("%c", *str);
		        }
		        break;
		}
		str++;
    	}
	printf("\n");
}

keyword(int lineno, char* yytext){

	char *p = yytext;
	while(*p != '\0'){
		*p=toupper(*p);
 		p++;
	}
 	printf("%s\t %d\t %s\n",filename, lineno, yytext);
}

int main(){
   int token;
   while(token=yylex()){
	switch(token){
		case IDENT:
			printf("%s\t %d\t IDENT\t %s\n",filename, lineno, yylval.word.yystring);
			break;
		case STRING:
			printf("%s\t %d\t STRING\t ",filename, lineno);
			printchars(tmp_string, tmp_ptr);	
			break;
		case CHARLIT:
			printf("%s\t %d\t CHARLIT\t ",filename, lineno);
			printchars(tmp_string, tmp_string+1);	
			break;
		case NUMBER:
			printf("%s\t %d\t NUMBER\t",filename,lineno);
			if(yylval.number.num_type==TYPE_INT || yylval.number.num_type==TYPE_LONG)
				printf("INTEGER\t %lld\t", yylval.number.yyint);
			else
				printf("REAL\t %Lg\t", yylval.number.yydouble);
			if(yylval.number.num_sign==TYPE_UNSIGNED)
				printf("UNSIGNED,");
			switch(yylval.number.num_type){
				case TYPE_INT:	printf("INT\n");break;
				case TYPE_LONG:	printf("LONG\n");break;
				case TYPE_LONGLONG: printf("LONGLONG\n");break;
				case TYPE_LONGDOUBLE: printf("LONGDOUBLE\n");break;
				case TYPE_DOUBLE: printf("DOUBLE\n");break;
				case TYPE_FLOAT: printf("FLOAT\n");break;
				default: printf("error\n");break;
			}
			break;
		default:
			break;

	}

   }
}
