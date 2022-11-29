/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-hid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:55:33 by abel-hid          #+#    #+#             */
/*   Updated: 2022/11/20 05:23:30 by abel-hid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char **str, char **line, int new_line)
{
	*line = ft_substr(*str, 0, new_line + 1);
	*str = get_rest(str, new_line + 1);
	return (*line);
}

char	*get_rest(char **str, int new_line)
{
	char	*rest;
	int		len;

	len = ft_strlen(*str + new_line);
	rest = ft_substr(*str, new_line, len);
	free(*str);
	*str = NULL;
	return (rest);
}

int	ft_check_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*buff;
	char		*line;
	int			reader;
	int			new_line;

	if (!str[fd])
		str[fd] = ft_strdup("");
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		reader = read(fd, buff, BUFFER_SIZE);
	while (reader >= 0)
	{
		buff[reader] = '\0';
		if ((!str[fd][0] && !reader))
			break ;
		str[fd] = ft_strjoin(str[fd], buff);
		new_line = ft_check_new_line(str[fd]);
		if (new_line != 1)
			return (free(buff), ft_get_line(&str[fd], &line, new_line));
		if (!reader)
			return (free(buff), get_rest(&str[fd], 0));
		reader = read(fd, buff, BUFFER_SIZE);
	}
	return (free(str[fd]), free(buff), str[fd] = NULL, NULL);
}
