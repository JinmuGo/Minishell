# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 14:05:59 by jgo               #+#    #+#              #
#    Updated: 2023/01/28 18:01:15 by jgo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef TOPDIR
		TOPDIR = $(abspath ..)
endif

include $(TOPDIR)/config/Rules.mk
include $(TOPDIR)/config/color_rules.mk

MINISHELL = MINISHELL
NAME = $(MINISHELL)

DIRS = draw hooks utils
LIBS = $(addsuffix _bonus.a, $(addprefix lib/, $(DIRS)))

HEADS = minishell_bonus.h \
		error_bonus.h	\
		declaration_bonus.h \
		utils_bonus.h

SRCS = minishell_bonus.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
-include $(DEPS)

all bonus :
		$(Q)$(foreach dir, $(DIRS), $(MAKE) TOPDIR=$(TOPDIR) -C $(dir) $@;)
		$(Q)$(call color_printf,$(YELLOW),$(MINISHELL),🎯 Start compiling)
		$(MAKE) $(NAME)
		$(Q)$(call color_printf,$(GREEN),$(MINISHELL),✨ compiled!)

$(NAME): $(OBJS) $(LIBS)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@
	$(MAKE) files="$(HEADS)" src_dir=`pwd`/includes dst_dir=$(TOPDIR)/includes link_files
	$(MAKE) files="$(NAME)" src_dir=`pwd` dst_dir=$(TOPDIR) link_files
	
clean:
	$(Q)$(foreach dir, $(DIRS), $(MAKE) TOPDIR=$(TOPDIR) -C $(dir) $@;)
	$(MAKE) files="$(HEADS)" src_dir=`pwd` dst_dir=$(TOPDIR)/includes unlink_files
	$(RM) $(DEPS) $(OBJS)

fclean: clean
	$(Q)$(foreach dir, $(DIRS), $(MAKE) TOPDIR=$(TOPDIR) -C $(dir) $@;)
	$(MAKE) files="$(NAME)" src_dir=`pwd` dst_dir=$(TOPDIR) unlink_files
	$(RM) $(NAME)

re: fclean
	$(Q)$(foreach dir, $(DIRS), $(MAKE) TOPDIR=$(TOPDIR) -C $(dir) $@;)
	$(MAKE)

.PHONY: all clean fclean re bonus