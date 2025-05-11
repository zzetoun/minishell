/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   freedom.h										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: zzetoun <zzetoun@student.42abudhabi.ae>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/30 15:51:08 by zzetoun		   #+#	#+#			 */
/*   Updated: 2025/04/16 19:26:40 by zzetoun		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef FREEDOM_H
# define FREEDOM_H

void	ft_free_ptr(void *pointer);
void	ft_close_fd(int	fd[]);
void	ft_free_array(char **array);
void	free_env(t_env_info *env);
void	free_env_data(t_envp *envp);

#endif
