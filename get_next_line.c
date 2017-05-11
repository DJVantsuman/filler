/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 16:56:42 by itsuman           #+#    #+#             */
/*   Updated: 2017/03/16 20:27:39 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_write(char **str, char **var_str, char **line)
{
	unsigned int	i;
	char			*s;

	s = *var_str;
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	*line = ft_strsub(s, 0, i);
	if (s[i] == '\0')
		i--;
	*str = ft_strsub(s, i + 1, ft_strlen(s + i + 1));
	free(*var_str);
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	char		*var_str;
	char		*str_del;
	static char	*str = "";
	size_t		ret;

	if (fd >= 0 && read(fd, buf, 0) >= 0)
	{
		var_str = ft_strdup(str);
		while (!(ft_strchr(var_str, '\n'))
				&& (ret = read(fd, &buf, BUFF_SIZE)) > 0)
		{
			str_del = var_str;
			buf[ret] = '\0';
			var_str = ft_strjoin(var_str, buf);
			ft_strdel(&str_del);
		}
		if (var_str[0] != '\0')
			return (ft_write(&str, &var_str, line));
		else
			return (0);
	}
	return (-1);
}
