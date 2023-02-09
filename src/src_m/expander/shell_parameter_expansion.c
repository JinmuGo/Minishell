/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parameter_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:13:40 by jgo               #+#    #+#             */
/*   Updated: 2023/02/09 20:32:10 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "stack.h"

// 확장 부분.
// echo "\"$USER\"\"SHELL\""
// 확장된 문자와 $이후의 문자의 len차이만큼 return 한다. 
// valid 체크는 export에서 한다. 여기서는 envp에 있는지만 판단하고 업으면 \0을 리턴한다. 
// echo "$USERk$SHELL" ???
// echo "$USER=$SHELL"
// jgo=/bin/zsh
int	expand_variable(char *str)
{
	const t_list *envp = get_meta()->envp;
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
//  echo "$$SHELL>>$USER" 얘는 되야함.
// 	echo "$1??$ISER" 얘도 되야함.  
// 확장된 문자와 $이후의 문자의 len차이만큼 return 한다. 
int	dollar_control(char *str, char c)
{
	if (c == S_QUOTE || !str[1]) // '$USER' $\0 $$ $3
		return (0);
	// if (str[1] == '?')
		// confirm_last_return_val(); // $?
	expand_variable(str);
}

// ft_strtrim 사용. 
// $$ <- 하지않음.
		// 0		8
// echo "$SHELL""$USER" $SHELL
// echo $USER
t_bool	shell_param_expand(char *str)
{
	t_stack	stack; // idx를 저장하자! quote의 idx single quote만.
	char *tmp; // 이 변수에 expand된 문자열을 할당하고 매개변수로 들어온 str에 대입한다.
	// quote가 있으면 tmp에 넣어두고 만약 stack의 짝을 찾으면 expand를 진행한다.
	
	int	i;

	if (str == NULL)
		return (FALSE);
	i = 0;
	stack_init(&stack);
	while (str[i])
	{
		if (str[i] == DOLLAR)
			i += dollar_control(&str[i], str[(int)stack.peek(&stack)]);
		if (str[i] == S_QUOTE)
		{
			if (!stack.is_empty(&stack) && \
				str[*(int *)stack.peek(&stack)] == S_QUOTE)
				stack.pop(&stack);
			else
				stack.push(&stack, &i);
		}
		i++;
	}
	
	// quote_removal(str); // 같이 해줘야 겟다. 
	// 확장된 상태로 만들어 놓는다. return 하지 않음. 
	printf("param expand %s\n", str);
	return (TRUE);
}