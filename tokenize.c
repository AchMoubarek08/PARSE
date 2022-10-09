
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
	int i,j;
	i,j = 0;
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
		}
		else
			result = ft_strjoin(result, ft_strndup(&value[i], 1));
		i++;
	}
	return (result);
}
void	expand_all(t_token *tokens)
{
	//"ok"$zbi
	char *result = ft_strdup("");
	int i = 0;
	t_token	*tmp;
	tmp = tokens->next;
	while (tmp->e_type != END)
	{
		if(tmp->e_type == WORD)
		{
			if(!there_is_dollar(tmp->value))
				result = remove_quotes(tmp->value);
		}
		tmp = tmp->next;
	}
}