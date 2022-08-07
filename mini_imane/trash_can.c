// void	empty_pipes(t_list *pipes_lst)
#include "minishell.h"

void	free_red_list(t_list *lst)
{
	t_node			*node;
	t_node			*tmp;
	t_redirection	*file;

	node = lst->head;
	while (node)
	{
		tmp = node->next;
		file = node->content;
		free(file->name);
		if (file->fd > 0)
			close (file->fd);
		free (file);
		free (node);
		node = tmp;
	}
	free (lst);
}

void	empty_pipes(t_list *pipes_lst)
{
	char	**args;
	t_node	*pipe;
	t_node	*tmp;

	pipe = pipes_lst->head;
	pipes_lst->head = NULL;
	pipes_lst->last = NULL;
	while (pipe)
	{
		tmp = pipe->next;
		args = ((t_pipe *)(pipe->content))->arg;
		while (args && *args)
			free (*args++);
		free (((t_pipe *)(pipe->content))->arg);
		free_red_list(((t_pipe *)(pipe->content))->input);
		free_red_list(((t_pipe *)(pipe->content))->output);
		free(pipe->content);
		free (pipe);
		pipe = tmp;
	}
}

void	free_list(t_list *lst)
{
	t_node	*node;
	t_node	*tmp;

	node = lst->head;
	while (node)
	{
		tmp = node->next;
		free(node->content);
		free (node);
		node = tmp;
	}
	free(lst);
}

void	free_all(t_data *data)
{
	empty_pipes(data->pipes);
	free (data->pipes);
	// free_list(data->env);
	free_list(get_exp(NULL));
	free (data->envp);
	free (data);
}
