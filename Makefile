# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/02 20:10:46 by jgo               #+#    #+#              #
#    Updated: 2023/02/12 13:17:52 by jgo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ./make_config/Rules.mk
include ./make_config/color_rules.mk

MINISHELL = MINISHELL
NAME = $(MINISHELL)

all bonus clean fclean re:
	$(MAKE) TOPDIR=`pwd` -C lib $@
	$(MAKE) TOPDIR=`pwd` -C src $@

$(NAME):
	$(MAKE) TOPDIR=`pwd` -C lib
	$(MAKE) TOPDIR=`pwd` -C src $@

.PHONY: all clean fclean re bonus