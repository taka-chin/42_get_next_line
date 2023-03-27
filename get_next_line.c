/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyamauch <tyamauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 11:55:18 by tyamauch          #+#    #+#             */
/*   Updated: 2023/03/27 05:13:01 by tyamauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* #include <stdio.h> */
#include "get_next_line.h"

//freeしてnullを返す
char	*ft_free(char *str)
{
	free(str);
	str = NULL;
	return (NULL);
}

//BUFFER SIZE+1文字mallocする関数
char	*make_buff(int fd)
{
	char	*buf;
	ssize_t	byte;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	byte = read(fd, buf, BUFFER_SIZE);
	if (byte <= 0)
	{
		free(buf);
		return (NULL);
	}
	buf[byte] = '\0';
	return (buf);
}

//saveを作って返す
char	*make_save(char *buf, char *save, int nflag)
{
	char	*tmp;

	if (nflag == 0)
	{
		if (save != NULL)
		{
			tmp = ft_strdup(save);
			free(save);
			save = ft_strjoin(tmp, buf);
			free(tmp);
		}
		else
			save = ft_strdup(buf);
	}
	else
	{
		tmp = ft_strdup(ft_strchr(save, '\n'));
		free(save);
		save = ft_strdup(tmp + 1);
		free(tmp);
	}
	return (save);
}

//改行したもの作る
char	*make_lines(char *save, int nflag)
{
	char	*line;
	char	*tmp;
	size_t	len;

	len = 0;
	if (nflag == 1)
	{
		while (save[len] != '\n' && save[len])
			len++;
		tmp = ft_substr(save, 0, len + 1);
		line = ft_strdup(tmp);
		free(tmp);
	}
	else
		line = ft_strdup(save);
	return (line);
}

//本体
char	*get_next_line(int fd)
{
	static char	*save;
	char		*buf;
	char		*line;
	int			nflag;

	nflag = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (save != NULL && ft_strchr(save, '\n'))
			break ;
		buf = make_buff(fd);
		if (buf == NULL)
			break ;
		save = make_save(buf, save, nflag);
		free(buf);
	}
	if (save == NULL || *save == '\0')
		return (ft_free(save));
	if (ft_strchr(save, '\n'))
		nflag = 1;
	line = make_lines(save, nflag);
	save = make_save(buf, save, nflag);
	return (line);
}

/* for use to open function*/
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
char	*buf;

/* fd = open("./sample.txt", O_RDONLY); */
/* fd = open("./files/41_no_nl", O_RDONLY); */
/* fd = open("./files/41_with_nl", O_RDONLY); */
/* fd = open("./files/42_no_nl", O_RDONLY); */
fd = open("./files/42_with_nl", O_RDONLY);
/* fd = open("./files/43_no_nl", O_RDONLY); */
/* fd = open("./files/43_with_nl", O_RDONLY); */
/* fd = open("./files/alternate_line_nl_no_nl", O_RDONLY); */
/* fd = open("./files/alternate_line_nl_with_nl", O_RDONLY); */
/* fd = open("./files/big_line_no_nl", O_RDONLY); */
/* fd = open("./files/big_line_with_nl", O_RDONLY); */
/* fd = open("./files/empty", O_RDONLY); */
/* fd = open("./files/multiple_line_no_nl", O_RDONLY); */
/* fd = open("./files/multiple_line_with_nl", O_RDONLY); */
/* fd = open("./files/multiple_nlx5", O_RDONLY); */
/* fd = open("./files/nl", O_RDONLY); */
while(1)
{
	if((buf = get_next_line(fd)) == NULL)
		break ;
	/* printf("result : %s",buf); */
printf("%s",buf);
/* printf("%d\n",BUFFER_SIZE); */
free(buf);
}
close(fd);
}

__attribute__((destructor))
static void destructor() {
    system("leaks -q a.out");
}
