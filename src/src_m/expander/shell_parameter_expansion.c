/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parameter_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:13:40 by jgo               #+#    #+#             */
/*   Updated: 2023/02/06 21:36:44 by jgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "defines.h"

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
// ' single, " double인지 확인. 
void    shell_param_expand(char *str)
{
	int	i;	

	if (str == NULL)
		return ;
	i = 0;
	while (str[i])
	{
		
		i++;
	}

}