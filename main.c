#include "minishell.h"
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

int	init_tokens_cmd(t_token *tokens, t_parse *parse)
{
    parse = malloc(sizeof(t_parse));
    if (!parse)
        return (0);
    parse->ags = NULL;
    parse->cmd = NULL;
    parse->next = NULL;
	return (1);
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
		init_tokens_cmd(tokens, parse);
		// create_commands(tokens, &commands);
	}
}
