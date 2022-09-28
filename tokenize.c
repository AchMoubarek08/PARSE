
#include "minishell.h"

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
		val = ft_strdup(">");
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

void	token_dollar(t_lex *lex, t_token *tokens)
{
	char *val;
	t_token *new;

	val = ft_strdup("$");
	new = NULL;
	advance_lex(lex);
	if (lex->c == '0' || !ft_isdigit(lex->c))
	{
		if (lex->c == 32 || lex->c == '$' || lex->c == '?')
			val = ft_strjoin(val, ft_strndup(&lex->c, 1));
	}
	new = init_token(val, DOLLAR);
	tokens = lst_add_back(tokens, new);
}
