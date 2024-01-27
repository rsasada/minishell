/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongykim <jongykim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:21:53 by jongykim          #+#    #+#             */
/*   Updated: 2023/12/10 18:26:16 by jongykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../libft/includes/ft_printf.h"
# include "lexer.h"
# include "parser.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <stdbool.h>

typedef struct s_app
{
	t_list	*env_lst;

}	t_app;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

// error.c
void	exit_with_error(char *error_message);

// init_signal.c
void	config_signal(void);

#endif
