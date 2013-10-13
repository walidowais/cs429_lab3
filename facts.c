// Walid Owais
// EID: wo783
// Section #: 53845

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process(void);
int add_node(char *p_name, char *p_prop, char *p_val);
void print_list(void);
void liberate_list(void);
char trim_white(char c, FILE *input);

struct node{
	char *name;
	char *property;
	char *value;
	struct node *next;
};

FILE *facts = NULL;
FILE *questions = NULL;
struct node *root;
struct node *last;
int lst_size;

int main(int argc, char const *argv[])
{
	if(argc < 2){
		facts = stdin;
		process();
	}
	else if(argc == 2){
		facts = fopen(argv[1], "r");
		if(facts == NULL){
			fprintf(stderr, "Error opening facts file: %s\n", argv[1]);
			exit(1);
		}
		
		questions = stdin;
		
		process();

		fclose(facts);
	}
	else{
		if(argc > 3){
			fprintf(stderr, "Too many arguments.\n");
		}

		facts = fopen(argv[1], "r");
		if(facts == NULL){
			fprintf(stderr, "Error opening facts file: %s\n", argv[1]);
			exit(1);
		}

		questions = fopen(argv[2], "r");
		if(questions == NULL){
			fprintf(stderr, "Error opening questions file: %s\n", argv[2]);
			exit(1);
		}

		process();

		fclose(facts);
		fclose(questions);
	}
	
	return 0;
}

void process(void){
	char c;
	char *str_name;
	char *str_prop;
	char *str_val;
	int str_size;
	int str_max;

	lst_size = 0;
	last = 0;
	root = 0;

	c = getc(facts);
	while(c != EOF){

		c = trim_white(c, facts);
		if(c != 'F'){
			while((c != '\n') && (c != EOF)){
				// fprintf(stdout, "%c", c);
				c = getc(facts);
			}
		}
		else{
			c = getc(facts);
			c = trim_white(c, facts);

			str_max = 8;
			str_name = malloc(str_max * sizeof(char));
			str_size = 0;

			while((c != ':') ){
				// fprintf(stdout, "%c", c);

				if(str_size >= str_max){
					str_max += 8;
					str_name = realloc(str_name, str_max*sizeof(char));
				}
				str_name[str_size] = c;
				str_size++;

				c = getc(facts);
			}
			if(str_size >= str_max){
				str_max += 8;
				str_name = realloc(str_name, str_max*sizeof(char));
			}
			str_name[str_size] = '\0';
			str_size++;
			// fprintf(stdout, "\n");

			c = getc(facts);
			c = trim_white(c, facts);

			str_max = 8;
			str_prop = malloc(str_max * sizeof(char));
			str_size = 0;

			while((c != '=') ){
				fprintf(stdout, "%c", c);

				if(str_size >= str_max){
					str_max += 8;
					str_prop = realloc(str_prop, str_max*sizeof(char));
				}
				str_prop[str_size] = c;
				str_size++;

				c = getc(facts);
			}
			if(str_size >= str_max){
				str_max += 8;
				str_prop = realloc(str_prop, str_max*sizeof(char));
			}
			str_prop[str_size] = '\0';
			str_size++;
			// fprintf(stdout, "\n");

			c = getc(facts);
			c = trim_white(c, facts);

			str_max = 8;
			str_val = malloc(str_max * sizeof(char));
			str_size = 0;

			while((c != '\n') ){
				// fprintf(stdout, "%c", c);
				if(str_size >= str_max){
					str_max += 8;
					str_val = realloc(str_val, str_max*sizeof(char));
				}
				str_val[str_size] = c;
				str_size++;

				c = getc(facts);
			}
			if(str_size >= str_max){
				str_max += 8;
				str_val = realloc(str_val, str_max*sizeof(char));
			}
			str_val[str_size] = '\0';
			str_size++;
			
			add_node(str_name, str_prop, str_val);
		}

		// add_node(c);
		// fprintf(stdout, "%c", c);
		c = getc(facts);
	}
	print_list();
	liberate_list();
}

int add_node(char *p_name, char *p_prop, char *p_val){
	// fprintf(stdout, "add_node(%s)\n", s);
	struct node *current;
	current = root;

	if(current == 0){
		current = malloc(sizeof(struct node));
		current->next = 0;
		current->name = p_name;
		current->property = p_prop;
		current->value = p_val;
		root = current;
		last = root;
		lst_size++;
	}
	else{
		while((current->next) != 0){
			// fprintf(stderr, "strcmp(%s, %s) = %d  &&  strcmp(%s, %s) = %d\n", 
			// 	current->name, p_name, strcmp(current->name, p_name), 
			// 	current->property, p_prop, strcmp(current->property, p_prop));
			
			if((strcmp(current->name, p_name) == 0) && 
			(strcmp(current->property, p_prop) == 0) ){
				current->value = p_val;
				free(p_name);
				free(p_prop);
				free(p_val);
				fprintf(stderr, "ERORE\n");
				return 0;
			}

			current = current->next;
		}

		current->next = malloc(sizeof(struct node));
		current = current->next;
		current->next = 0;
		current->name = p_name;
		current->property = p_prop;
		current->value = p_val;
		last = current;
		lst_size++;
	}

	return 0;
}

void print_list(void){
	// fprintf(stdout, "print_list()\n");

	struct node *current;
	current = root;

	if(current != 0){
		// fprintf(stdout, "\nroot");
		while(current != 0){
			fprintf(stdout, "%s : %s = %s\n", current->name, current->property, current->value);
			current = current->next;
		}
		// fprintf(stdout, "<----last\n");
	}
	else{
		// fprintf(stdout, "Empty List.\n");
	}
}

void liberate_list(void){
	// fprintf(stdout, "LIBERATION! free() the people.\n");

	struct node *temp;

	while(root != 0){
		// fprintf(stdout, "Freeing node: %c\n", root->data);
		temp = root;
		root = root->next;
		free(temp->name);
		free(temp->property);
		free(temp->value);
		free(temp);
	}
}

char trim_white(char c, FILE *input){
	while((c == ' ') || (c == '\t') || (c == '\n')){
			c = getc(facts);
	}
	return c;
}






