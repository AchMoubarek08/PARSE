
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

char	*remove_quotes(char *value)
{
	int i;
	i = 0;
	char q;
	char *result = ft_strdup("");
	while(value[i] != '\0')
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
char	*expand_dollar(char *value, int *flag)
{
	int i = 0;
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
		else if(value[i] == 34)
		{
			dq = ft_strdup("");
			i++;
			while(value[i] && value[i] != 34)
			{
				if (value[i] == 39)
					*flag = 1;
				dq = ft_strjoin(dq, ft_strndup(&value[i], 1));
				i++;
			}
			result = ft_strjoin(result, dq_content(dq));
		}
		else if(value[i] == 39)
		{

			result = ft_strjoin(result, ft_strndup(&value[i], 1));
			i++;
			while(value[i] != 39)
			{
				result = ft_strjoin(result, ft_strndup(&value[i], 1));
				i++;
			}
			result = ft_strjoin(result, ft_strndup(&value[i], 1));
		}
		else
			result = ft_strjoin(result, ft_strndup(&value[i], 1));
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
t_token	*expand_all(t_token *tokens)
{
	char *result = ft_strdup("");
	int i = 0;
	int flag = 0;
	t_token	*tmp;
	char **arr = malloc(sizeof(char *) * 100);
	tokens = tokens->next;
	while (tokens->e_type != END)
	{
		flag = 0;
		if(tokens->e_type == WORD)
		{
			if(there_is_dollar(tokens->value))
			{
				tokens->value = expand_dollar(tokens->value, &flag);
			}
			if(flag == 0)
				result = remove_quotes(tokens->value);
			else
				result = tokens->value;
		}
		arr[i] = ft_strdup(result);
		i++;
		tokens = tokens->next;
	}
	arr[i] = NULL;
	print_array(arr);
	return(tmp);
}
