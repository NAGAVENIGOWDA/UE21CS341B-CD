#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sym_tab.h"

table* init_table()	
{
    table* t=(table*)malloc(sizeof(table));
    t->head=NULL;
    return t;
	
    
}

symbol* init_symbol(char* name, int len, int type, int lineno, int scope)
{
    symbol* s=(symbol*)malloc(sizeof(symbol));
    s->name=(char*)malloc(sizeof(char)*(len+1));
    strcpy(s->name,name);
    s->len=len;
    s->type=type;
    s->line=lineno;
    s->val=(char*)malloc(sizeof(char)*10);
    strcpy(s->val,"~");
    s->next=NULL;
    s->scope=scope;
    return s;
    
	
}

void insert_into_table(char * name,int len,int type,int lineno,int scope)
{
    symbol* s=init_symbol(name,len,type,lineno,scope);
    if(t->head==NULL){
        t->head=s;
        return;
    }else {
        symbol* curr = t->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = s;
    }
}

int check_symbol_table(char* name)
{
    if(t->head==NULL){
        return 0;
    }
    symbol *curr=t->head;
    while(curr!=NULL){
        if(strcmp(curr->name,name)==0){
            return 1;
        }
        curr=curr->next;
    }
    return 0;
    
}

void insert_value_to_name(char*name,char*v,int line)
{
    if(strcmp(v, "~") == 0){
        return;
    }
    if(t->head==NULL){
        return;
    }
    symbol* curr=t->head;
    while(curr!=NULL){
        if(strcmp(curr->name,name)==0){
            strcpy(curr->val,v);
            curr->line=line;
            return;
        }
        curr=curr->next;
    }
}

void display_symbol_table()
{
    symbol*curr=t->head;
    if(curr==NULL){
        return;
        
    }
    printf("Name\tlen\ttype\tlineno\tscope\tvalue\n");
    while(curr!=NULL){
        int len=0;
        if (curr->type == INT) {
            len= sizeof(int);
        } else if (curr->type == FLOAT) {
            len = sizeof(float);
        } else if (curr->type == DOUBLE) {
            len = sizeof(double);
        } else if (curr->type == CHAR) {
            len = sizeof(char);
        }
        printf("%s\t%d\t%d\t%d\t%d\t%s\n",curr->name,len,curr->type,curr->line,curr->scope,curr->val);
        curr=curr->next;
    }
}
int type_check(char* value) //checks the type from the value string
{
    char *s=strchr(value, '\"');
    if(s!=NULL)
        return 1;
    char *f=strchr(value,'.');
    if(f!=NULL)
        return 3;
    return 2;
}
