# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 13:42:33 by jgo               #+#    #+#              #
#    Updated: 2023/02/17 15:22:46 by jgo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef TOPDIR
		TOPDIR = $(abspath ..)
endif

include $(TOPDIR)/config/Rules.mk
include $(TOPDIR)/config/color_rules.mk

LIBS = libft

all bonus clean fclean re:
		$(Q)$(foreach lib, $(LIBS), $(MAKE) TOPDIR=$(TOPDIR) -C $(lib) $@;)

.PHONY: all clean fclean re bonus
