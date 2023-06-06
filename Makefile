# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/02 20:10:46 by jgo               #+#    #+#              #
#    Updated: 2023/06/06 15:51:44 by jgo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ./make_config/src/Rules.mk
include ./make_config/com/ColorRules.mk

NAME := $(PROJECT_NAME)

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
