//
// Created by iqment on 6/1/25.
//

#include "../parser.h"

/**
 * @brief this function setups the output file descriptor when we are have a '>'
 * @param cmd
 * We are going through the command list and checking if there is an output file -
 * if so, we open it with O_WRONLY | O_CREAT | O_TRUNC flags. And -
 * change current file descriptor to the stdout (1) descriptor. Like file output becomes to new file :)
 */
void 	setup_truncate(t_io_fds *io)
{

	if (!io)
		return;
	if (io->outfile)
		io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (io->fd_out == -1)
	{
		errmsg("open", io->outfile, strerror(errno), errno);
		return;
	}
	if (dup2(io->fd_out, STDOUT_FILENO) == -1)
		errmsg("dup2", io->outfile, strerror(errno), errno);
}
/**
 * @brief this function setups the input file descriptor when we have a '<'
 * @param io
 */
void 	setup_input(t_io_fds *io)
{
	if (!io)
		return ;
	if (io->infile)
		io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in == -1)
		errmsg("open", io->infile, strerror(errno), errno);
	if (dup2(io->fd_in, STDIN_FILENO) == -1)
		errmsg("dup2", io->infile, strerror(errno), errno);
}

/**
 * @brief this function setups the output file descriptor when we have a '>>'
 * @param io
 * We are going through the command list and checking if there is an append file -
 * if so, we open it with O_WRONLY | O_CREAT | O_APPEND flags. And -
 * change current file descriptor to the stdout (1) descriptor. Like file output becomes to new file :)
 */
void 	setup_append(t_io_fds *io)
{
	if (!io)
		return ;
	if (io->append_file)
		io->fd_out = open(io->append_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (io->fd_out == -1)
		errmsg("open", io->append_file, strerror(errno), errno);
	if (dup2(io->fd_out, STDOUT_FILENO) == -1)
		errmsg("dup2", io->append_file, strerror(errno), errno);
	if (io->fd_out != STDOUT_FILENO)
	{
		close(io->fd_out);
		io->fd_out = -1;
	}
}

/**
 * @brief this function setups the input file descriptor when we have a '<<'
 * @param io
 * We are going through the command list and checking if there is a heredoc delimiter -
 * if so, we open it with O_WRONLY | O_CREAT | O_APPEND flags. And -
 * change current file descriptor to the stdin (0) descriptor. Like file input becomes to new file :)
 */

void 	close_exists_red_fds(t_io_fds *fds)
{
	if (!fds)
		return ;
	if (fds->fd_in != -1)
	{
		close(fds->fd_in);
		fds->fd_in = -1;
	}
	if (fds->fd_out != -1)
	{
		close(fds->fd_out);
		fds->fd_out = -1;
	}
}
