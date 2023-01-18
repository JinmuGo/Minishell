# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgo <jgo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 13:49:09 by jgo               #+#    #+#              #
#    Updated: 2023/01/04 20:09:42 by jgo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef TOPDIR
		TOPDIR = $(abspath ../..)
endif
include $(TOPDIR)/config/Rules.mk
include $(TOPDIR)/config/color_rules.mk

CPPFLAGS = -I$(TOPDIR)/includes

NAME = libftprintf.a

HEAD = ft_printf.h
SRCS = ft_printf.c \
		ft_printf_c.c \
		ft_printf_d.c \
		ft_printf_p.c \
		ft_printf_s.c \
		ft_printf_u.c \
		ft_printf_x.c \
		ft_putchar.c \
		ft_putstr.c \
		utils.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
-include $(DEPS)

all bonus:
	$(Q)$(call color_printf,$(CYAN),$(NAME),🎯 starting compile libft)
	$(Q)$(MAKE) $(NAME)
	$(Q)$(call color_printf,$(GREEN),$(NAME),🔰 done!)

$(NAME): $(OBJS)
		$(Q)$(call color_printf,$(GREEN),$(NAME),📚 archive object)
		$(AR) $(ARFLAGS) $@ $^
		$(Q)$(MAKE) files="$(NAME)" src_dir=`pwd` dst_dir=$(TOPDIR)/lib link_files
		$(Q)$(MAKE) files="$(HEAD)" src_dir=`pwd` dst_dir=$(TOPDIR)/includes link_files
		
clean:
		$(Q)$(MAKE) files="$(NAME)" src_dir=`pwd` dst_dir=$(TOPDIR)/lib unlink_files
		$(Q)$(MAKE) files="$(HEAD)" src_dir=`pwd` dst_dir=$(TOPDIR)/includes unlink_files
		$(Q)$(call color_printf,$(RED),$(NAME),🗑️  remove Objects && Dependency file)
		$(RM) $(OBJS) $(DEPS)

fclean: clean
		$(Q)$(call color_printf,$(RED),$(NAME),🗑️  remove $(NAME))
		$(RM) $(NAME)
	
re : fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus