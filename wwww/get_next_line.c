/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagzoul <ylagzoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:13:42 by ylagzoul          #+#    #+#             */
/*   Updated: 2024/12/11 20:57:01 by ylagzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*chock_read(int fd, char *handel)
{
	char	*buffer;
	int		num;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(handel), NULL);
	num = 1;
	while (!ft_strchr(handel, '\n') && num != 0)
	{
		num = read(fd, buffer, BUFFER_SIZE);
		if (num == -1)
			return (free(buffer), free(handel), NULL);
		buffer[num] = '\0';
		handel = ft_strjoin(handel, buffer);
		if (!handel)
			return (free(handel), free(buffer), NULL);
	}
	free(buffer);
	return (handel);
}

static	char	*get_file_rest(char *buffer)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	i++;
	str = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!str)
		return (free(buffer), NULL);
	j = 0;
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = '\0';
	free(buffer);
	return (str);
}

static	char	*get_line(char *buffer)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		str[j] = buffer[j];
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*handel;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
	{
		if (handel)
		{
			free(handel);
			handel = NULL;
		}
		return (NULL);
	}
	handel = chock_read(fd, handel);
	if (!handel || !*handel)
		return (free(handel), handel = NULL, NULL);
	buffer = get_line (handel);
	if (!buffer)
		return (free(handel), handel = NULL, NULL);
	handel = get_file_rest (handel);
	return (buffer);
}
