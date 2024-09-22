/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkassel <rkassel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:50:05 by rgrochow          #+#    #+#             */
/*   Updated: 2024/09/16 16:45:10 by rkassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_eof(t_shell *shell)
{
	printf("exit\n");
	clean_shell_within_rl(shell);
	clean_shell_out_rl(shell);
	exit(EC_SUCCESS);
}
