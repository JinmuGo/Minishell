/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parameter_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:13:40 by jgo               #+#    #+#             */
/*   Updated: 2023/02/18 20:35:38 by jgo              ###   ########.fr       */
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
// $USER$1

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
		return (0);
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
		if (src[i] == S_QUOTE && src[tmp - 2] == S_QUOTE)
			tmp--;
	return (tmp);
}

void	double_dollar(char *dst, char *str, int *i, int *j)
{
	if (dst && str)
	{
		dst[(*j)++] = str[*i - 1];
		(*i)++;
		dst[(*j)++] = str[*i - 1];
	}
	else
	{
		(*j) += 2;
		(*i)++;
	}
}


int	try_expand_and_cal_len(char *str, int i, int tmp)
{
	const char *dst = ft_substr(str, tmp, i - tmp);
	const int	len = get_envp_elem(dst)->val_len;

	free((void *)dst);
	return (len);
}

void	quote_control(const t_deque *deque, char c)
{
	char	*tmp;

	if (c == S_QUOTE || c == D_QUOTE)
	{
		tmp = ((char *)(deque->peek_front((t_deque *)deque)));
		if (tmp == NULL || *tmp != c)
		{
			tmp = ft_malloc(sizeof(char));
			*tmp = c;
			deque->push_front((t_deque *)deque, tmp);
		}
		else
		{
			tmp = (char *)deque->pop_front((t_deque *)deque);
			if (tmp)
				free(tmp);
		}
	}
}

//  $var$var"a" 이거 문제있다. 
// 그런데 위를 고치면 $USER$SHHH이런 케이스는 expanding이 안됨. 
// echo "'$HOME'" 이거 확장되어야함. 가장 바깥에 있는 quote가 double이기 때문에 .
t_bool	dollar_control(char c, char *rear)
{
	if (c == DOLLAR)
	{
		if (rear != NULL && *rear != S_QUOTE)
			return (FT_TRUE);
		else if (rear == NULL)
			return (FT_TRUE);
	}
	return (FT_FALSE);
}

char *expand_variable(char *dst, char *str)
{
	const t_deque *deque = deque_init(ft_strlen(str));
	int	tmp;
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i++])
	{
		quote_control(deque, str[i - 1]);
		if (str[i - 1] == DOLLAR && str[i] == DOLLAR)
			double_dollar(dst, str, &i, &j);
		else if  (dollar_control(str[i - 1], (char *)deque->peek_rear(deque)))
		{
			tmp = i;
			while (is_shell_var(str[i]))
				i++;
			tmp = expand_and_dup(dst, ft_substr(str, tmp, i - tmp), j);
			if (tmp != 0)
				j = tmp;
		}
		else
			dst[j++] = str[i - 1];
	}
	dst[j] = '\0';
	dq_free(deque);
	return (dst);
}

int	cal_expand_len(char *str)
{
	const t_deque *deque = deque_init(ft_strlen(str));
	int	len;
	int	tmp;
	int	i;

	len = 0;
	i = 0;
	while (str[i++])
	{
		quote_control(deque, str[i - 1]);
		if (str[i - 1] == DOLLAR && str[i] == DOLLAR)
			double_dollar(NULL, NULL, &i, &len);
		else if (dollar_control(str[i - 1], (char *)deque->peek_rear(deque)))
		{
			tmp = i;
			while (is_shell_var(str[i]))
				i++;
			tmp = try_expand_and_cal_len(str, i, tmp);
			if (tmp > 0)
				len += tmp;
		}
		else
			len++;
	}
	dq_free(deque);
	return (len);
}


// $$
// ''
//  echo "$$SHELL>>$USER" 얘는 우리 쉘에선 $$SHELL>>jgo 이렇게 되어야함.
// 	echo "$1??$USER" 얘도 우리 쉘에선 "??jgo" $1은 expanding했지만 없기 때문에 \0이 됨.
		// 0		8
// echo "$SHELL$USER" /bin/zshjgo
// echo $USER
// $"U""S""E""R"
char *shell_param_expand(char *str)
{
	const int	expand_len = cal_expand_len(str);
	char *dst;

	dst = ft_malloc(sizeof(char) * (expand_len + 1));
	dst = expand_variable(dst, str);
	return (dst);
}