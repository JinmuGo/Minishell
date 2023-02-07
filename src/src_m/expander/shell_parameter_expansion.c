/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parameter_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:13:40 by jgo               #+#    #+#             */
/*   Updated: 2023/02/07 19:18:41 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"
#include "stack.h"

// $$에 대해서는 지원하지 않도록 한다. 
// we are not support $ var it is special parameter
// $$USER -> 위의 에러 메시지와 $$USER command not found

// ${ENV_ARGS}가 들어왔을 때는 {} <- 특수문자는 해석하지 않기로하였기 때문에,
// ${ENV_ARGS} -> ${ENV_ARGS} command not found가 떠야한다.  

// export 12311=13 -> 되지 않는다. (숫자는 제외해야한다.)
// export _12311=13 -> 성공!

// 쉘의 지역변수와 전역변수를 구분하지 않는다.
// a=3 <- 이것은 command not found a=3으로 처리한다.

// "$PATH"
// '$PATH;

// export a="\|"
// echo hihi $a cat 
// pipe가 문자열로 취급된다.

// $
// $"U""S""E""E""R"

//echo "$U"S""E""R""
//U=hihihi
//echo "$U"S""E""R""
//hihihiSER

// echo "$U"SER
// hihihiSER
// echo "$U"S""E""R""
// hihihiSER 이 예시는 single quote일때는 해석하지 않는다. 

// stack 자료형을 사용해야겠다. quote처리를 위해선. 
// '(single) "(double)인지 확인. 
t_bool	shell_param_expand(char *str)
{
	t_stack	stack;
	int	i;

	if (str == NULL)
		return (FALSE);
	i = 0;
	stack_init(&stack);
	while (str[i])
	{
		if (str[i] == S_QUOTE || str[i] == D_QUOTE)
		{
			if ((char)stack.peek(&stack) == str[i])
				stack.pop(&stack);
			else
				stack.push(&stack, &str[i]);
		}
		i++;
	}
	
	
	// 확장된 상태로 만들어 놓는다. return 하지 않음. 
	printf("param expande%s\n", str);
	return (TRUE);
}