#include "minishell.h"

void	nadi(char **stock, char **ligne)
{
	char	*temp;
	int		x;

	x = ft_int_strchr_gnl(*stock, '\n') + 1;
	*ligne = ft_substr_gnl(*stock, 0, x);
	temp = *stock;
	*stock = ft_substr_gnl(*stock, x, ft_strlen_gnl(*stock));
	free(temp);
}

char	*ft_free(char **lost)
{
	if (*lost)
		free(*lost);
	*lost = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	int			i;
	char		buff[8 + 1];
	char		*ligne;
	static char	*stock;
	char		*temp;

	while (ft_int_strchr_gnl(stock, '\n') == -1)
	{
		i = read(fd, buff, 8);
		if (i == 0 || i == -1)
		{
			if (stock && stock[0] == '\0')
				ft_free(&stock);
			ligne = stock;
			stock = NULL;
			return (ligne);
		}
		buff[i] = '\0';
		temp = stock;
		stock = ft_strjoin_gnl(stock, buff);
		ft_free(&temp);
	}
	nadi(&stock, &ligne);
	return (ligne);
}