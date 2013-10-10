#include <stdio.h>
#include <stdlib.h>

void process(void);
void add_node(char c);
void print_list(void);
void liberate_list(void);

struct node{
	char data;
	struct node *next;
};

FILE *facts = NULL;
FILE *questions = NULL;
struct node *root;
struct node *last;
int size;

int main(int argc, char const *argv[])
{
	if(argc < 2){
		facts = stdin;
		process();
		// fprintf(stderr, "no facts file specified\n");
		// fprintf(stderr, "usage: facts fact_file.fax [question_file.q]\n");
		// exit(1);
	}
	else if(argc == 2){
		facts = fopen(argv[1], "r");
		questions = stdin;
	}
	else if(argc == 3){
		facts = fopen(argv[1], "r");
		questions = fopen(argv[2], "r");
	}
	else{
		fprintf(stderr, "too many arguments specified\n");
		fprintf(stderr, "usage: facts fact_file.fax [question_file.q]\n");
	}
	
	return 0;
}

void process(void){
	char c;

	size = 0;
	last = 0;
	root = malloc(sizeof(struct node));

	root->next = 0;
	root->data = 0;

	while((c = getc(facts)) != EOF){
		add_node(c);
	}
	print_list();
	liberate_list();
}

void add_node(char c){
	// fprintf(stdout, "add_node(%c)\n", c);

	if(last == 0){
		root->data = c;
		last = root;
	}
	else{
		last->next = malloc(sizeof(struct node));
		last = last->next;

		last->next = 0;
		last->data = c;
	}

	size++;
}

void print_list(void){
	// fprintf(stdout, "print_list()\n");

	struct node *current;
	current = root;

	if(current != 0){
		fprintf(stdout, "\nroot");
		while(current != 0){
			fprintf(stdout, " -> %c", current->data);
			current = current->next;
		}
		fprintf(stdout, "<----last\n");
	}
	else{
		fprintf(stdout, "Empty List.\n");
	}
}

void liberate_list(void){
	// fprintf(stdout, "liberate_list()\n");

	struct node *temp;

	while(root != 0){
		fprintf(stdout, "Freeing node: %c\n", root->data);
		temp = root;
		root = root->next;
		free(temp);
	}
}








