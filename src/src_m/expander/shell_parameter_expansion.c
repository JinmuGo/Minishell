/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parameter_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:13:40 by jgo               #+#    #+#             */
/*   Updated: 2023/02/13 14:58:09 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "data_structure.h"
#include "envp_command.h"
#include "expander.h"

// 확장 부분.
// echo "\"$USER\"\"SHELL\""
// 확장된 문자와 $이후의 문자의 len차이만큼 return 한다. 
// valid 체크는 export에서 한다. 여기서는 envp에 있는지만 판단하고 없으면 \0을 리턴한다. 
// echo "$USERk$SHELL" ???
// echo "$USER=$SHELL"
// echo "$1" positional parameter도 확장한다. export 할때 envp에 넣지만 않으면됨. 
// jgo=/bin/zsh

int	expand_and_dup(char *dst, char *key, int j)
{
	int	i;
	char	*expanded;

	if (key[0] == DOLLAR)
		expanded = ft_strdup(key);
	else
		expanded = get_envp_elem(key)->val;
	free(key);
	if (expanded == NULL)
		return (1);
	i = 0;
	while (expanded[i])
		dst[j++] = expanded[i++];
	if (key[0] == DOLLAR)
		free(expanded);
	return (j);
}

int		expand_start_check(int tmp, char *src, int i)
{
	if (tmp > 1)
		if (src[i] == '\'' && src[tmp - 2] == '\'')
			tmp--;
	return (tmp);
}

char *expand_variable(char *dst, char *str)
{
	int	tmp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		i++;
		if  (str[i - 1] == DOLLAR && is_shell_var(str[i]))
		{
			tmp = i;
			while (is_shell_var(str[i]))
				i++;
			tmp = expand_start_check(tmp, str, i);
			j += expand_and_dup(dst, ft_substr(str, tmp, i - tmp), j);
		}
		else
			dst[j++] = str[i - 1];
	}
	dst[j] = '\0';
	return (dst);
}

int	try_expand_and_cal_len(char *str, int i, int tmp)
{
	const char *dst = ft_substr(str, tmp, i - tmp);
	const int	len = get_envp_elem(dst)->val_len;

	free((void *)dst);
	return (len);
}

int	cal_expand_len(char *str)
{
	int	len;
	int	tmp;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		i++;
		if (str[i - 1] == DOLLAR && is_shell_var(str[i]))
		{
			tmp = i;
			while (is_shell_var(str[i]))
				i++;
			len += try_expand_and_cal_len(str, i, tmp);			
		}
		else
			len++;
	}
	return (len);
}

// $$
// ''
//  echo "$$SHELL>>$USER" 얘는 우리 쉘에선 $$SHELL>>jgo 이렇게 되어야함.
// 	echo "$1??$USER" 얘도 우리 쉘에선 "??jgo" $1은 expanding했지만 없기 때문에 \0이 됨.
// 확장된 문자와 $이후의 문자의 len차이만큼 return 한다. 
// ft_strtrim 사용. // 아마 quote_removal을 말하는거겠지?
// $$ <- 하지않음.
		// 0		8
// echo "$SHELL$USER" /bin/zshjgo
// echo $USER
char *shell_param_expand(char *str)
{
	const int	expand_len = cal_expand_len(str);
	char *dst;

	dst = ft_malloc(sizeof(char) * (expand_len + 1));
	dst = expand_variable(dst, str);
	return (dst);
}