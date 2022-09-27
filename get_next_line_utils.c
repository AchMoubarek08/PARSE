#include "minishell.h"

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	if (ft_strlen_gnl(s) < start || len == 0)
		return (ft_strdup_gnl(""));
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	while (s[i])
	{
		if (j < len && i >= start)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup_gnl(s2));
	str = (char *)malloc(sizeof(char) * ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (str == 0)
		return (0);
	while (s1[i])
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	i = -1;
	while (s2[++i])
	{
		str[j] = s2[i];
		j++;
	}
	str[j] = '\0';
	return (str);
}

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup_gnl(const char *s)
{
	int		i;
	char	*m;
	int		len;

	i = 0;
	len = ft_strlen_gnl(s);
	m = (char *)malloc(sizeof(char) * len + 1);
	if (m == NULL)
		return (0);
	while (s[i])
	{
		m[i] = s[i];
		i++;
	}
	m[i] = '\0';
	return (m);
}

int	ft_int_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	if ((char)c == '\0' && s[i] == '\0')
		return (-1);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}