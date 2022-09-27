#include "minishell.h"
void	print_lexer(t_lex *lex)
{
	printf("char : %c\n", lex->c);
	printf("indice : %i\n", lex->i);
}

int	ft_is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	advance_lex(t_lex *lex)
{
	lex->i++;
	lex->c = lex->cmd[lex->i];
}

void	create_token()
{
	while(lex->c)
	{
		if(lex->c == 32 || lex-> c == 9)
			advance_lex(lex);
		else if (lex->c == '\'')
			token_squote(lex);
		else if (lex->c == '\"')
			token_dquote(lex);
		else if
	}
}

void	*init_tokens_cmd(t_token *tokens, t_parse *parse, char *line)
{
	t_lex	*lex;
    parse = malloc(sizeof(t_parse));
	lex = malloc(sizeof(t_lex));
    if (!parse || !lex)
        return (NULL);
    parse->ags = NULL;
    parse->cmd = NULL;
    parse->next = NULL;
	lex->c = line[0];
	lex->cmd = line;
	lex->i = 0;
	create_tokens(lex, tokens);
	return (NULL);
}

int	main(int ac, char *av[], char **env)
{
	t_parse	*parse;
	t_token	*tokens;
    char    *line;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("MISSI-1.0$ ");
		if (!line)
			exit(0);
		init_tokens_cmd(tokens, parse, line);
		// create_commands(tokens, &commands);
	}
}
