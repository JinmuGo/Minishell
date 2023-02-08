/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parameter_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:13:40 by jgo               #+#    #+#             */
/*   Updated: 2023/02/08 22:09:07 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "stack.h"

// stack에들어 있는게 single이 아니라면 expand


// 확장 부분.
// 
void	expand_variable(char *str)
{
	
}

// $$
// ''
// $1
void	dollar_control(char *str, char c)
{
	if (c == S_QUOTE || !str[1])
		return ;
	if (str[1] == DOLLAR)
		return ;
	if (ft_isdigit(str[1]))
		return ;
	if (str[1] == '?')
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
	const t_meta *meta = get_meta();
	t_stack	stack; // idx를 저장하자! quote의 idx
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
			dollar_control(&str[i], str[(int)stack.peek(&stack)]);
		if (str[i] == S_QUOTE || str[i] == D_QUOTE)
		{
			if (!stack.is_empty(&stack) && str[*(int *)stack.peek(&stack)] == str[i])
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