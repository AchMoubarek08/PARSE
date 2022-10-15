
#include "minishell.h"

int	is_token(char c)
{
	char	*tokens;
	int		j;

	tokens = "><| ";
	j = 0;
	while (tokens[j])
	{
		if (c == tokens[j])
			return (1);
		j++;
	}
	return (0);
}
int		there_is_dollar(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
void	token_squote(t_lex *lex, t_token *tokens)
{
	char *val;
	t_token *new;

	val = ft_strdup("");
	new = NULL;
	advance_lex(lex);
	while (lex->c != '\'')
	{
		val = ft_strjoin(val, ft_strndup(&lex->c, 1));
		advance_lex(lex);
	}
	advance_lex(lex);
	new = init_token(val, SQUOTE);
	tokens = lst_add_back(tokens, new);
}

void	token_dquote(t_lex *lex, t_token *tokens)
{
	char *val;
	t_token *new;

	val = ft_strdup("");
	new = NULL;
	advance_lex(lex);
	while (lex->c != '"')
	{
		val = ft_strjoin(val, ft_strndup(&lex->c, 1));
		advance_lex(lex);
	}
	advance_lex(lex);
	new = init_token(val, DQUOTE);
	tokens = lst_add_back(tokens, new);
}

void	token_pipe(t_lex *lex, t_token *tokens)
{
	char *val;
	t_token *new;

	val = ft_strdup("|");
	new = NULL;
	advance_lex(lex);
	new = init_token(val, PIPE);
	tokens = lst_add_back(tokens, new);
}

void	end_token(t_token *tokens)
{
	t_token *new;

	new = NULL;
	new = init_token("", END);
	tokens = lst_add_back(tokens, new);
}

void	token_less(t_lex *lex, t_token *tokens)
{
	char *val;
	t_token *new;

	val = ft_strdup("");
	new = NULL;
	advance_lex(lex);
	if	(lex->cmd[lex->i] == '<')
	{
		advance_lex(lex);
		val = ft_strdup("<<");
		new = init_token(val, LESSANDLESS);
	}
	else
	{
		val = ft_strdup("<");
		new = init_token(val, LESS);
	}
	tokens = lst_add_back(tokens, new);
}

void	token_great(t_lex *lex, t_token *tokens)
{
	char *val;
	t_token *new;

	val = ft_strdup("");
	new = NULL;
	advance_lex(lex);
	if	(lex->cmd[lex->i] == '>')
	{
		advance_lex(lex);
		val = ft_strdup(">>");
		new = init_token(val, GREATANDGREAT);
	}
	else
	{
		val = ft_strdup(">");
		new = init_token(val, GREAT);
	}
	tokens = lst_add_back(tokens, new);
}

void switch_var(int *i)
{
	if(*i == 0)
		*i = 1;
	else
		*i = 0;
}

void	token_word(t_lex *lex, t_token *tokens)
{
	char *val;
	t_token *new;
	int i = 0;
	int j = 0;
	int k = 1;

	val = ft_strdup("");
	new = NULL;
	while(lex->c != '\0' && k == 1)
	{
		k = 0;
		while (!is_token(lex->c) && lex->c != '\0')
		{
			if(lex->c == 34)
				switch_var(&i);
			else if(lex->c == '\'')
				switch_var(&j);
			val = ft_strjoin(val, ft_strndup(&lex->c, 1));
			advance_lex(lex);
			if(i == 1 || j == 1)
				break;
		}
		if(i == 1)
		{
			while(lex->c != 34 && lex->c != '\0')
			{
				val = ft_strjoin(val, ft_strndup(&lex->c, 1));
				advance_lex(lex);
			}
			val = ft_strjoin(val, ft_strndup(&lex->c, 1));
			advance_lex(lex);
			switch_var(&i);
		}
		else if(j == 1)
		{
			while(lex->c != '\'' && lex->c != '\0')
			{
				val = ft_strjoin(val, ft_strndup(&lex->c, 1));
				advance_lex(lex);
			}
			val = ft_strjoin(val, ft_strndup(&lex->c, 1));
			advance_lex(lex);
			switch_var(&j);
		}
		while(lex->c != '>' && lex->c != '<' && lex->c != '|'
			&& lex->c != ' ' && lex->c != '\0')
		{
			if(lex->c == 34)
				switch_var(&i);
			else if(lex->c == '\'')
				switch_var(&j);
			val = ft_strjoin(val, ft_strndup(&lex->c, 1));
			advance_lex(lex);
			if(i == 1 || j == 1)
			{
				k=1;
				break;
			}	
		}
	}
	new = init_token(val, WORD);
	tokens = lst_add_back(tokens, new);
}
int ft_strlen(char *str)
{
	int i = 0;

	while(str[i] != '\0')
		i++;
	return (i);
}
void print_tab(int *tab)
{
	int i;
	i = 0;
	while(tab[i])
	{
		printf("%d ", tab[i]);
		i++;
	}
	printf("\n");
}
char	*remove_quotes(char *value, int *sequences)
{
	int i;
	i = 0;
	char q;
	char *result = ft_strdup("");
	while(value[i] != '\0')
	{
		if(sequences[i] != 1)
		{
			if(value[i] == 34 || value[i] == 39)
			{
				q = value[i];
				i++;
				while(value[i] && value[i] != q)
				{
					result = ft_strjoin(result, ft_strndup(&value[i], 1));
					i++;
				}
				i++;
			}
			if (value[i] != '\0' && value[i] != 34 && value[i] != 39)
			{
				result = ft_strjoin(result, ft_strndup(&value[i], 1));
				i++;
			}
		}
		else
		{
			result = ft_strjoin(result, ft_strndup(&value[i], 1));
			i++;
		}
	}
	return (result);
}

int	is_alpha(char c)
{
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int is_digit(char c)
{
	if(c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_alphanum(char c)
{
	if(is_alpha(c) || is_digit(c))
		return (1);
	return (0);
}
char *dq_content(char *value)
{
	int i;
	char *result = ft_strdup("");
	char *expnd = ft_strdup("");
	i = 0;
	while(value[i])
	{
		if(value[i] == '$' && value[i + 1] && (is_alphanum(value[i + 1]) || value[i + 1] == '?'))
		{
			i++;
			if(value[i] == '$')
			{
				result = ft_strjoin(result, "$$");
			}
			else if(value[i] == '?')
				result = ft_strjoin(result, "exit_status");
			else if((value[i] == 39 || value[i] == 34))
			{
				continue ;
			}
			else if((value[i] && !is_alpha(value[i]) && !is_digit(value[i])))
			{
				result = ft_strjoin(result, "$");
				continue ;
			}
			else
			{
				while((is_alpha(value[i]) || is_digit(value[i])))
				{
					expnd = ft_strjoin(expnd, ft_strndup(&value[i], 1));
					i++;
				}
				result = ft_strjoin(result, "X");
				i--;
			}
		}
		else
			result = ft_strjoin(result, ft_strndup(&value[i], 1));
		i++;
	}
	return (result);
}

char	*expand_dollar(char *value, int *sequences)
{
	int i = 0;
	int o = 0;
	int j = 0;
	char *expnd = ft_strdup("");
	char *result = ft_strdup("");
	char *dq = ft_strdup("");
	while(value[i] != '\0')
	{
		if(value[i] == '$')
		{	
			i++;
			if(value[i] == '$')
			{
				result = ft_strjoin(result, "$$");
				sequences[o++] = 1;
				sequences[o++] = 1;
			}
			else if(value[i] == '?')
				result = ft_strjoin(result, "0");
			else if((value[i] == 39 || value[i] == 34))
			{
				continue ;
			}
			else if((value[i] && !is_alpha(value[i]) && !is_digit(value[i])))
			{
				result = ft_strjoin(result, "$");
				continue ;
			}
			else
			{
				while((is_alpha(value[i]) || is_digit(value[i])))
				{
					expnd = ft_strjoin(expnd, ft_strndup(&value[i], 1));
					i++;
				}
				result = ft_strjoin(result, "X");
				i--;
			}
		}
		else if(value[i] == 34)
		{
			dq = ft_strdup("");
			i++;
			while(value[i] && value[i] != 34)
			{
				dq = ft_strjoin(dq, ft_strndup(&value[i], 1));
				i++;
			}
			j = 0;
			while(j < ft_strlen(dq_content(dq)))
			{
				sequences[o] = 1;
				o++;
				j++;
			}
			j = 0;
			result = ft_strjoin(result, dq_content(dq));
		}
		else if(value[i] == 39)
		{
			result = ft_strjoin(result, ft_strndup(&value[i], 1));
			i++;
			sequences[o] = 2;
			o++;
			while(value[i] != 39)
			{
				result = ft_strjoin(result, ft_strndup(&value[i], 1));
				i++;
				sequences[o] = 2;
				o++;
			}
			result = ft_strjoin(result, ft_strndup(&value[i], 1));
			sequences[o] = 2;
			o++;
		}
		else
		{
			result = ft_strjoin(result, ft_strndup(&value[i], 1));
			sequences[o] = 1;
			o++;
		}
		i++;
	}
	return(result);
}
void	print_array(char **array)
{
	int i = 0;
	while(array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}
void	fill_sequences(int len, int *sequences)
{
	int i = 0;
	while(i < len)
	{
		sequences[i] = 2;
		i++;
	}
}

void	*realloc_array(char **arg, char *str)
{
	char	**new_arg;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arg && arg[i])
		i++;
	new_arg = (char **)malloc(sizeof(char *) * (i + 2));
	while (arg && j < i)
	{
		new_arg[j] = ft_strdup(arg[j]);
		j++;
	}
	new_arg[j++] = ft_strdup(str);
	new_arg[j] = NULL;
	return (new_arg);
}
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}

void	errors(int exit_status)
{
	if(exit_status == 2)
	{
		ft_putstr_fd("Minishell : unclosed quote!", 2);
		ft_putchar_fd('\n', 2);
	}
	else if(exit_status == 258)
	{
		ft_putstr_fd("Minishell : syntax error near unexpected token", 2);
		ft_putchar_fd('\n', 2);
	}
	else if (exit_status == 3)
	{
		ft_putstr_fd("Minishell : pipe open!", 2);
		ft_putchar_fd('\n', 2);
	}
}

t_parse	*add_command(t_parse *commad)
{
	t_parse	*new;

	new = init_cmd();
	commad = add_command_back(commad, new);
	return (commad);
}

void	fill_tparse(t_token *tokens, t_parse **parse)
{
	t_parse *tmp;

	tmp = *parse;
	while(tokens)
	{
		if(tokens->e_type == WORD)
		{
			if(!tmp->cmd)
				tmp->cmd = ft_strdup(tokens->value);
			else
				tmp->argv = realloc_array(tmp->argv, tokens->value);
			tokens = tokens->next;
		}
		if(tokens->e_type == PIPE || tokens->e_type == END)
		{
			if(tokens->next && tokens->e_type == PIPE && tokens->next->e_type == END)
			{
				errors(3);
				return;
			}
			tmp = add_command(tmp);
			tmp = tmp->next;
			tokens = tokens->next;
		}
	}
}
t_token	*parsing(t_token *tokens, t_parse **parse)
{
	int i = 0;
	int *sequences;
	t_token	*tmp = tokens->next;
	tokens = tokens->next;
	while (tokens->e_type != END)
	{
		if(tokens->e_type == WORD)
		{
			sequences = malloc(sizeof(int) * 100000);
			if(there_is_dollar(tokens->value))
			{
				tokens->value = expand_dollar(tokens->value, sequences);
			}
			else
			{
				fill_sequences(ft_strlen(tokens->value), sequences);
			}
			tokens->value = remove_quotes(tokens->value, sequences);
		}
		i++;
		tokens = tokens->next;
	}
	return(tmp);
}
