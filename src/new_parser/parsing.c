#include "../../includes/mini.h"

#define QTERR "minishell: Unbalanced quotes in the string.\n"

//creare un nodo della lista
t_fullcmd *create_newnode(char *start, char *end)
{
	t_fullcmd *new_node;
	new_node = (t_fullcmd *)malloc(sizeof(t_fullcmd));
	new_node->line = strndup(start, end - start);
	new_node->next = NULL;
	return new_node;
}
//creato un nodo, se è il primo setta la "head" altrimenti accoda il nodo alla lista
void handle_newnode(t_fullcmd **list_head, t_fullcmd **current, char *start, char *end)
{
	t_fullcmd *new_node = create_newnode(start, end);
	if (*list_head == NULL)
	{
		*list_head = new_node;
		*current = *list_head;
	}
	else
	{
		(*current)->next = (struct s_list *)new_node;
		*current = (t_fullcmd *)(*current)->next;
	}
}

//funzione per gestire il testo tra gli apici
int handle_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
	else if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);

	return (*in_single_quote && *in_double_quote);
}

//funzione di split della stringa per " | " e creazione della lista
t_fullcmd *split_string_to_list(char *str, t_fullcmd *head)
{
	t_fullcmd	*current = head;
	int			in_single_quote = 0;
	int			in_double_quote = 0;
	char 		*start = str;
	char		*end = str;

	while (*end != '\0')
	{
		if (handle_quotes(*end, &in_single_quote, &in_double_quote))
			return (printf(QTERR), NULL);
		if (strncmp(end, " | ", 3) == 0 && !in_single_quote && !in_double_quote)
		{
			if (end > start)
				handle_newnode(&head, &current, start, end);
			start = end + 3;
		}
		end++;
	}
	if (end > start)
		handle_newnode(&head, &current, start, end);
	if (in_single_quote || in_double_quote)
		return (printf(QTERR), NULL);
	return head;
}

//freea la lista
int free_lst(t_fullcmd *list_head) {
	t_fullcmd *current = list_head;
	while (current != NULL) {
		struct s_list *next = current->next;
		free(current->line);
		free(current);
		current = (t_fullcmd *)next;
	}
	return 1;
}

//fa partire il parsing e freea la lista in caso di errore
int parsing(char *str) {
	t_fullcmd *list_head = NULL;
	list_head = split_string_to_list(str, list_head);
	if (list_head == NULL)
		return free_lst(list_head);
	return 0;
}

int main(int argc, char *argv[])
{
	t_fullcmd	*current;
	int			result;

	if (argc < 2)
	{
		printf("Utilizzo: %s <stringa_da_analizzare>\n", argv[0]);
		return 1;
	}
	result = parsing(argv[1]);
	if (result != 0)
		printf("Errore durante il parsing della stringa.\n");
	else
	{
		printf("Risultato del parsing:\n");
		current = split_string_to_list(argv[1], NULL);
		while (current != NULL)
		{
			printf("- %s\n", current->line);
			current = (t_fullcmd *)current->next;
		}
		free_lst(current);
	}
	return 0;
}

//splittare la stringa nel singolo nodo per spazzi ed inserire il contenuto in una seconda lista

//controllare se il primo comando è una buildtin (controllo su exit)

//controllare se sono presenti redirections, se presenti (devo gestire il caso dell'here_doc) se dopo ho almeno un argomento,
//se ne ho: ottengo l'fd dell'argomento (supopendo sia un file valido),
//cambio con dub2 l'fd di standard input/output (< / >) e setto quello del file, elimino il nodo della redirection e dell'argomento

//eseguo il comando con execve