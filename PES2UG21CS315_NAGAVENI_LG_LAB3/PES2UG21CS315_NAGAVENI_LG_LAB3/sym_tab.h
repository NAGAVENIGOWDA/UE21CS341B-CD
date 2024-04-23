#define CHAR 1
#define INT 2
#define FLOAT 3
#define DOUBLE 4

typedef struct symbol		//data structure of items in the list
{
	char* name;			//identifier name
    int len;
	int type;			//identifier type
	char* val;			//value of the identifier
	int line;			//declared line number
	int scope;			//scope of the variable
	struct symbol* next;
}symbol;

typedef struct table		//keeps track of the start of the list
{
	symbol* head;
}table;

static table* t;

table* init_table();	//allocate space for start of table
// thus making a new symbol table

symbol* init_symboly(char* name, int len, int type, int lineno, int scope);
//allocates space for items in the list and initialisation

void insert_into_table(char* name, int len, int type, int lineno, int scope);	//arguments can vary based on implementation
//inserts symbols into the table when declared

void insert_value_to_name(char*name,char*v,int line);
//inserts values into the table when a variable is initialised

int check_symbol_table(char*name);
//checks symbol table whether the variable has been declared or not

void display_symbol_table();			//displays symbol table
