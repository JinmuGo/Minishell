# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/05 08:31:25 by jgo               #+#    #+#              #
#    Updated: 2023/03/17 16:10:40 by sanghwal         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

ifndef TOPDIR
		TOPDIR = $(abspath ../../../)
endif

include $(TOPDIR)/config/Rules.mk
include $(TOPDIR)/config/color_rules.mk

SRCS = signal_controller.c \
	signal_init.c \
	signal_child.c \
	signal_heredoc.c

NAME = signal_controller.a
	

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
-include $(DEPS)

all bonus :
	$(Q)$(call color_printf,$(CYAN),$(NAME),🎯 starting compile $(NAME))
	$(Q)$(MAKE) $(NAME)
	$(Q)$(call color_printf,$(GREEN),$(NAME),🔰 done!)

$(NAME): $(OBJS)
	$(Q)$(call color_printf,$(GREEN),$(NAME),📚 archive object)
	$(AR) $(ARFLAGS) $@ $^
	$(Q)$(MAKE) files="$(NAME)" src_dir=`pwd` dst_dir=$(TOPDIR)/src/src_m/lib link_files
	
clean:
	$(Q)$(MAKE) files="$(NAME)" src_dir=`pwd` dst_dir=$(TOPDIR)/src/src_m/lib unlink_files
	$(Q)$(call color_printf,$(RED),$(NAME),🗑️  remove Objects && Dependency file)
	$(RM) $(OBJS) $(DEPS)

fclean: clean
		$(Q)$(call color_printf,$(RED),$(NAME),🗑️  remove $(NAME))
		$(RM) $(NAME)
	
re : fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus