# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 13:42:33 by jgo               #+#    #+#              #
#    Updated: 2023/01/28 15:15:44 by jgo              ###   ########.fr        #
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
