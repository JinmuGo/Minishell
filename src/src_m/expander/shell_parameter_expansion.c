/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parameter_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:13:40 by jgo               #+#    #+#             */
/*   Updated: 2023/02/12 18:55:02 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "data_structure.h"
#include "envp_command.h"

// 확장 부분.
// echo "\"$USER\"\"SHELL\""
// 확장된 문자와 $이후의 문자의 len차이만큼 return 한다. 
// valid 체크는 export에서 한다. 여기서는 envp에 있는지만 판단하고 없으면 \0을 리턴한다. 
// echo "$USERk$SHELL" ???
// echo "$USER=$SHELL"
// echo "$1" positional parameter도 확장한다. export 할때 envp에 넣지만 않으면됨. 
// jgo=/bin/zsh
int	expand_variable(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = -1;
	while (str[++i])
	{
		
	}
	
}

// $$
// ''
//  echo "$$SHELL>>$USER" 얘는 우리 쉘에선 $$SHELL>>jgo 이렇게 되어야함.
// 	echo "$1??$USER" 얘도 우리 쉘에선 "??jgo" $1은 expanding했지만 없기 때문에 \0이 됨.
// 확장된 문자와 $이후의 문자의 len차이만큼 return 한다. 
int	dollar_control(char *str, char c)
{
	if (c == S_QUOTE || !str[1]) // '$USER' $\0
		return (0);
	// if (str[1] == '?')
		// confirm_last_return_val(); // $?
	expand_variable(str);
}

// ft_strtrim 사용. // 아마 quote_removal을 말하는거겠지?
// $$ <- 하지않음.
		// 0		8
// echo "$SHELL$USER" /bin/zshjgo
// echo $USER
t_bool	shell_param_expand(char *str)
{
	const int	len = ft_strlen(str);
	const t_deque *dq = deque_init(len);
	char *tmp; // 이 변수에 expand된 문자열을 할당하고 매개변수로 들어온 str에 대입한다.
	// quote가 있으면 tmp에 넣어두고 만약 stack의 짝을 찾으면 expand를 진행한다.
	int	i;

	if (str == NULL)
		return (FALSE);
	i = 0;
	while (str[i])
	{
		if (str[i] == DOLLAR)
			i += dollar_control(&str[i], str[*(int *)dq->peek_rear(dq)]);
		if (str[i] == S_QUOTE)
		{
			if (dq->use_size != 0 && str[*(int *)dq->peek_front(dq)] == S_QUOTE)
				dq->pop_front(dq);
			else
				dq->push_front(dq, &i);
		}
		i++;
	}
	free(str);
	// str = // 다시 할 당을 한다. 
	// quote_removal(str); // 같이 해줘야 겟다. 
	// 확장된 상태로 만들어 놓는다. return 하지 않음. 
	printf("param expand %s\n", str);
	return (TRUE);
}