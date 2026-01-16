/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatoliy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:42:42 by anatoliy          #+#    #+#             */
/*   Updated: 2026/01/16 18:44:05 by anatoliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	error_exit(const char *error_message)
{
	write(STDERR, "Erorr\n", 6);
	write(STDERR, error_message, ft_strlen(error_message));
	exit(-1);
}

void	free_arr_and_error_exit(char **map_arr, const char *error_message)
{
	free_str_arr(map_arr);
	error_exit(error_message);
}
