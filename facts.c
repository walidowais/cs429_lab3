// Walid Owais
// EID: wo783
// Section #: 53845

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fax(void);
void qux(void);
int add_node(char *p_name, char *p_prop, char *p_val);
void find_node(char *p_name, char *p_prop);
void print_list(void);
void liberate_list(void);
char trim_before(char c, FILE *input);
int trim_after(char *s, int size);

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
		fprintf(stderr, "No files provided\n");
		exit(1);
	}
	else if(argc == 2){
		facts = fopen(argv[1], "r");
		if(facts == NULL){
			fprintf(stderr, "Error opening facts file: %s\n", argv[1]);
			exit(1);
		}
		
		questions = stdin;
		
		fax();
		qux();

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

		fax();
		qux();

		fclose(facts);
		fclose(questions);
	}

	liberate_list();
	return 0;
}

void fax(void){
	int c;
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
		c = trim_before(c, facts);
		if(c != 'F'){
			while((c != '\n') && (c != EOF)){
				c = getc(facts);
			}
		}
		else{
			// name
			c = getc(facts);
			c = trim_before(c, facts);
			str_max = 8;
			str_name = malloc(str_max * sizeof(char));
			if(str_name == NULL){
				fprintf(stderr, "Out of memory.\n");
				exit(1);
			}
			str_size = 0;

			while(c != ':'){
				// fprintf(stderr, "loop ':'\n");
				if(str_size >= str_max){
					str_max += 8;
					str_name = realloc(str_name, str_max*sizeof(char));
					if(str_name == NULL){
						fprintf(stderr, "Out of memory.\n");
						exit(1);
					}
				}

				str_name[str_size] = c;
				str_size++;

				c = getc(facts);
			}

			str_size = trim_after(str_name, str_size);
			str_name = realloc(str_name, str_size*sizeof(char));
			if(str_name == NULL){
				fprintf(stderr, "Out of memory.\n");
				exit(1);
			}
			str_name[str_size] = '\0';

			// property
			c = getc(facts);
			c = trim_before(c, facts);
			str_max = 8;
			str_prop = malloc(str_max * sizeof(char));
			if(str_prop == NULL){
				fprintf(stderr, "Out of memory.\n");
				exit(1);
			}
			str_size = 0;

			while(c != '='){
				// fprintf(stderr, "loop '='\n");
				if(str_size >= str_max){
					str_max += 8;
					str_prop = realloc(str_prop, str_max * sizeof(char));
					if(str_prop == NULL){
						fprintf(stderr, "Out of memory.\n");
						exit(1);
					}
				}

				str_prop[str_size] = c;
				str_size++;

				c = getc(facts);
			}

			str_size = trim_after(str_prop, str_size);
			str_prop = realloc(str_prop, str_size * sizeof(char));
			if(str_prop == NULL){
				fprintf(stderr, "Out of memory.\n");
				exit(1);
			}
			str_prop[str_size] = '\0';

			// value
			c = getc(facts);
			c = trim_before(c, facts);
			str_max = 8;
			str_val = malloc(str_max * sizeof(char));
			if(str_val == NULL){
				fprintf(stderr, "Out of memory.\n");
				exit(1);
			}
			str_size = 0;

			while((c != '\n') && (c != EOF)){
				// fprintf(stderr, "loop '\\n'\n");
				if(str_size >= str_max){
					str_max += 8;
					str_val = realloc(str_val, str_max * sizeof(char));
					if(str_val == NULL){
						fprintf(stderr, "Out of memory.\n");
						exit(1);
					}
				}

				str_val[str_size] = c;
				str_size++;

				c = getc(facts);
			}

			str_size = trim_after(str_val, str_size);
			str_val = realloc(str_val, str_size*sizeof(char));
			if(str_val == NULL){
				fprintf(stderr, "Out of memory.\n");
				exit(1);
			}
			str_val[str_size] = '\0';
			
			// add to list
			add_node(str_name, str_prop, str_val);
		}

		c = getc(facts);
	}
}

void qux(void){
	int c;
	char *str_name;
	char *str_prop;
	int str_size;
	int str_max;

	c = getc(questions);
	while(c != EOF){
		c = trim_before(c, questions);
		if(c != 'Q'){
			while((c != '\n') && (c != EOF)){
				c = getc(questions);
			}
		}
		else{
			// name
			c = getc(questions);
			c = trim_before(c, questions);
			str_max = 8;
			str_name = malloc(str_max * sizeof(char));
			if(str_name == NULL){
				fprintf(stderr, "Out of memory.\n");
				exit(1);
			}
			str_size = 0;

			while(c != ':'){
				// fprintf(stderr, "loop ':'\n");
				if(str_size >= str_max){
					str_max += 8;
					str_name = realloc(str_name, str_max * sizeof(char));
					if(str_name == NULL){
						fprintf(stderr, "Out of memory.\n");
						exit(1);
					}
				}

				str_name[str_size] = c;
				str_size++;

				c = getc(questions);
			}

			str_size = trim_after(str_name, str_size);
			str_name = realloc(str_name, str_size * sizeof(char));
			if(str_name == NULL){
				fprintf(stderr, "Out of memory.\n");
				exit(1);
			}
			str_name[str_size] = '\0';

			// property
			c = getc(questions);
			c = trim_before(c, questions);
			str_max = 8;
			str_prop = malloc(str_max * sizeof(char));
			if(str_prop == NULL){
				fprintf(stderr, "Out of memory.\n");
				exit(1);
			}
			str_size = 0;

			while((c != '\n') && (c != EOF)){
				// fprintf(stderr, "loop '\\n'\n");
				if(str_size >= str_max){
					str_max += 8;
					str_prop = realloc(str_prop, str_max * sizeof(char));
					if(str_prop == NULL){
						fprintf(stderr, "Out of memory.\n");
						exit(1);
					}
				}

				str_prop[str_size] = c;
				str_size++;

				c = getc(questions);
			}

			str_size = trim_after(str_prop, str_size);
			str_prop = realloc(str_prop, str_size * sizeof(char));
			if(str_prop == NULL){
				fprintf(stderr, "Out of memory.\n");
				exit(1);
			}
			str_prop[str_size] = '\0';

			// search list
			find_node(str_name, str_prop);
		}
	}
}

int add_node(char *p_name, char *p_prop, char *p_val){
	// fprintf(stdout, "add_node(%s)\n", s);
	struct node *current;
	current = root;

	if(current == 0){
		current = malloc(sizeof(struct node));
		if(current == NULL){
			fprintf(stderr, "Out of memory.\n");
			exit(1);
		}
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
				// fprintf(stdout, "%s replaces %s\n", p_val, current->value);
				free(p_name);
				free(p_prop);
				free(current->value);
				current->value = p_val;
				return 0;
			}

			current = current->next;
		}

		if((strcmp(current->name, p_name) == 0) && 
		(strcmp(current->property, p_prop) == 0) ){
				// fprintf(stdout, "%s replaces %s\n", p_val, current->value);
				free(p_name);
				free(p_prop);
				free(current->value);
				current->value = p_val;
				return 0;
			}

		current->next = malloc(sizeof(struct node));
		if(current->next == NULL){
			fprintf(stderr, "Out of memory.\n");
			exit(1);
		}
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

void find_node(char *p_name, char *p_prop){
	int found;
	struct node *current;
	current = root;
	found = 0;
	
	while((current != 0) && (found == 0)){
		if((strcmp(current->name, p_name) == 0) && 
		(strcmp(current->property, p_prop) == 0)){
			fprintf(stdout, "F %s: %s=%s\n", 
				current->name, current->property, current->value);
			found = 1;
		}
		current = current->next;
	}

	if(found == 0){
		fprintf(stdout, "F %s: %s=unknown\n", 
			p_name, p_prop);
	}

	free(p_name);
	free(p_prop);
}

void print_list(void){
	// fprintf(stdout, "print_list()\n");

	struct node *current;
	current = root;

	if(current != 0){
		while(current != 0){
			fprintf(stdout, "%s : %s = %s\n", 
				current->name, current->property, current->value);
			current = current->next;
		}
	}
	else{
		fprintf(stdout, "Empty List.\n");
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

char trim_before(char c, FILE *input){
	while((c == ' ') || (c == '\t') || (c == '\n')){
			c = getc(input);
	}

	return c;
}

int trim_after(char *s, int size){
	while(s[size-1] == ' ' || s[size-1] == '\t'){
		size--;
	}

	return size;
}




