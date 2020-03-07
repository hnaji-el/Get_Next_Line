/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <hnaji-el@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 02:14:17 by hnaji-el          #+#    #+#             */
/*   Updated: 2020/03/07 18:41:58 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		eof_neof(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		myfree(char **fr)
{
	if (*fr != NULL)
	{
		free(*fr);
		*fr = NULL;
	}
	return (-1);
}

int		ft_len(char *str, int len)
{
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	return (len);
}

int		read_join(char **str, int fd, int r)
{
	char	*buffer;
	char	*fr;

	if ((buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
		return (myfree(str));
	if (!eof_neof(*str))
	{
		while (r > 0)
		{
			r = read(fd, buffer, BUFFER_SIZE);
			buffer[r] = '\0';
			fr = *str;
			if ((*str = ft_strjoin(*str, buffer)) == NULL)
			{
				myfree(&fr);
				return (myfree(&buffer));
			}
			myfree(&fr);
			if (eof_neof(*str))
				break ;
		}
	}
	myfree(&buffer);
	return (r);
}

int		get_next_line(int fd, char **line)
{
	static char	*str[OPEN_MAX];
	char		*fr;
	int			r;
	int			len;

	if (BUFFER_SIZE <= 0 || fd < 0 || line == NULL || read(fd, NULL, 0) != 0)
		return (-1);
	if (str[fd] == NULL)
	{
		if ((str[fd] = ft_strdup("")) == NULL)
			return (-1);
	}
	if ((r = read_join(&str[fd], fd, 1)) == -1)
		return (-1);
	len = ft_len(str[fd], 0);
	if ((*line = ft_substr(str[fd], 0, len)) == NULL)
		return (myfree(&str[fd]));
	fr = str[fd];
	str[fd] = (r == 0) ? NULL : ft_strdup(str[fd] + len + 1);
	if ((r != 0) && str[fd] == NULL)
		return (myfree(&fr));
	myfree(&fr);
	return (r == 0 ? 0 : 1);
}
