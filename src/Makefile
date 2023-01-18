# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgo <jgo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 13:42:33 by jgo               #+#    #+#              #
#    Updated: 2023/01/05 08:32:01 by jgo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef TOPDIR
		TOPDIR = $(abspath ..)
endif

include $(TOPDIR)/config/Rules.mk
include $(TOPDIR)/config/color_rules.mk

bonus :
	$(MAKE) TOPDIR=$(TOPDIR) -C src_b $@

all : 
	$(MAKE) TOPDIR=$(TOPDIR) -C src_m $@

clean fclean :
	$(MAKE) TOPDIR=$(TOPDIR) -C src_m $@
	$(MAKE) TOPDIR=$(TOPDIR) -C src_b $@

re : fclean
	$(MAKE) TOPDIR=$(TOPDIR) -C src_m $@

.PHONY: all clean fclean re bonus
