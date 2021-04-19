/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwanetta <dwanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 18:28:35 by dwanetta          #+#    #+#             */
/*   Updated: 2020/11/09 19:51:06 by dwanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	words;
	int	wordstarted;

	i = 0;
	wordstarted = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			wordstarted = 1;
		else if (wordstarted == 1)
		{
			wordstarted = 0;
			words++;
		}
		i++;
	}
	if (wordstarted == 1)
		words++;
	return (words);
}

static int	ft_find_word_start(int index, char const *s, char c)
{
	while (s[index] != '\0')
	{
		if (s[index] == c)
			index++;
		else
			return (index);
	}
	return (index);
}

static int	f(int index, char const *s, char c)
{
	int	length;

	length = 0;
	while (s[index] != '\0' && s[index] != c)
	{
		length++;
		index++;
	}
	return (length);
}

char		**ft_split(char const *s, char c)
{
	char	**o;
	int		in;
	int		i;
	int		words;
	int		j;

	if (s == NULL)
		return (NULL);
	in = 0;
	i = 0;
	words = ft_count_words(s, c);
	if ((o = (char **)malloc(sizeof(char *) * (words + 1))) == NULL)
		return (NULL);
	while (s[in] != '\0' && i < words && o != NULL)
	{
		in = ft_find_word_start(in, s, c);
		if ((o[i] = (char *)malloc(sizeof(char) * (f(in, s, c) + 1))) == NULL)
			return (NULL);
		j = 0;
		while (s[in] != c && s[in] != '\0')
			o[i][j++] = s[in++];
		o[i++][j] = '\0';
	}
	o[i] = NULL;
	return (o);
}
