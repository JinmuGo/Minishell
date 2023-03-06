# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgo <jgo@student.42seoul.fr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 13:42:33 by jgo               #+#    #+#              #
#    Updated: 2023/03/06 09:49:16 by jgo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef TOPDIR
		TOPDIR = $(abspath ../../)
endif

include $(TOPDIR)/config/Rules.mk
include $(TOPDIR)/config/color_rules.mk

bonus :
	$(MAKE) TOPDIR=$(TOPDIR) -C src_b $@

all $(PROJECT_NAME):
	$(MAKE) TOPDIR=$(TOPDIR) -C src_m $@

clean fclean :
	$(MAKE) TOPDIR=$(TOPDIR) -C src_m $@
# $(MAKE) TOPDIR=$(TOPDIR) -C src_b $@

re : fclean
	$(MAKE) TOPDIR=$(TOPDIR) -C src_m $@

.PHONY: all clean fclean re bonus
