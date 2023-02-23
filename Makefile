# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/02 20:10:46 by jgo               #+#    #+#              #
#    Updated: 2023/02/23 19:24:28 by jgo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ./config/Rules.mk
include ./config/color_rules.mk

NAME = $(PROJECT_NAME)

all bonus clean fclean re:
	$(MAKE) TOPDIR=`pwd` -C lib $@
	$(MAKE) TOPDIR=`pwd` -C src $@

$(NAME):
	$(MAKE) TOPDIR=`pwd` -C lib
	$(MAKE) TOPDIR=`pwd` -C src $@

norm:
	@norminette ./src/ ./lib/

leaks: all
	leaks ./$(NAME)

.PHONY: all clean fclean re bonus norm leaks