//NAME : NAGAVENI L G
//SRN : PES2UG21CS315
//SEC : 6F
%{
	#include "sym_tab.c"
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#define YYSTYPE char*
    int type=-1;
    char* vval="~"; //initial declaration of value for symbol table
    int vtype=-1; //initial declaration for type checking for symbol table
    int scope=0; //initial declaration for scope

    void yyerror(char* s); // error handling function
    int yylex(); // declare the function performing lexical analysis
    extern int yylineno; // track the line number
	void yyerror(char* s); // error handling function
	int yylex(); // declare the function performing lexical analysis
	extern int yylineno; // track the line number

%}

%token T_INT T_CHAR T_DOUBLE T_WHILE  T_INC T_DEC   T_OROR T_ANDAND T_EQCOMP T_NOTEQUAL T_GREATEREQ T_LESSEREQ T_LEFTSHIFT T_RIGHTSHIFT T_PRINTLN T_STRING  T_FLOAT T_BOOLEAN T_IF T_ELSE T_STRLITERAL T_DO T_INCLUDE T_HEADER T_MAIN T_ID T_NUM

%start START


%%
START : PROG { printf("Valid syntax\n"); YYACCEPT; }	
        ;	
	  
PROG :  MAIN PROG				
	|DECLR ';' PROG 				
	| ASSGN ';' PROG 			
	| 					
	;
	 

DECLR : TYPE LISTVAR 
	;	


LISTVAR : LISTVAR ',' VAR 
	  | VAR
	  ;
VAR: T_ID '=' EXPR {
          if(check_symbol_table($1)){
              printf("Variable %s already declared\n", $1);
              yyerror($1);
          }
          insert_into_table($1, strlen($1), type, yylineno, scope);
          insert_value_to_name($1, vval, yylineno);
          vval="~"; //revert to default for checking
          type=-1;
      }
    
				
			
     | T_ID 		{
         if(check_symbol_table($1)) //if variable is in table then variable is being re-declared
         {
         printf("Variable %s already declared\n", $1);
         yyerror($1);
         }
         insert_into_table($1, strlen($1), type, yylineno, scope);
         type=-1;
				
			}	 

//assign type here to be returned to the declaration grammar
TYPE : T_INT {type=INT;}
       | T_FLOAT {type=FLOAT;}
       | T_DOUBLE {type=DOUBLE;}
       | T_CHAR {type=CHAR;}
       ;
    
/* Grammar for assignment */   
ASSGN : T_ID '=' EXPR 	{
    if(!check_symbol_table($1)) //if variable not declared then value cannot be assigned
    {
        printf("Variable %s not declared\n", $1);
        yyerror($1);
    }
    insert_value_to_name($1,vval, yylineno);
    vval="~";
    type=-1;
				
			}
	;

EXPR : EXPR REL_OP E
       | E 
       ;
	   
E : E '+' T
    | E '-' T
    | T 
    ;
	
	
T : T '*' F
    | T '/' F
    | F
    ;

F : '(' EXPR ')'
    | T_ID
    | T_NUM 
    | T_STRLITERAL 
    ;

REL_OP :   T_LESSEREQ
	   | T_GREATEREQ
	   | '<' 
	   | '>' 
	   | T_EQCOMP
	   | T_NOTEQUAL
	   ;	


/* Grammar for main function */
MAIN : TYPE T_MAIN '(' EMPTY_LISTVAR ')' '{' {scope++;} STMT '}' {scope--;};

EMPTY_LISTVAR : LISTVAR
		|	
		;

STMT : STMT_NO_BLOCK STMT
       | BLOCK STMT
       |
       ;


STMT_NO_BLOCK : DECLR ';'
       | ASSGN ';' 
       ;

BLOCK : '{' {scope++;} STMT '}' {scope--;};

WHILE_2 : '{' {scope++;} STMT '}' {scope--;}
	| ';'


COND : EXPR 
       | ASSGN
       ;


%%


/* error handling function */
void yyerror(char* s)
{
	printf("Error :%s at %d \n",s,yylineno);
}


int main(int argc, char* argv[])
{
	t = init_table();
	yyparse();
	/* display final symbol table*/
	display_symbol_table();
	return 0;

}
