# include "./minishell.h"

void execution_muliproc(t_nodes *nds,char **env, t_env *tenv)
{
	char *cmd;
	cmd = NULL;
	
		 	if(nds->cmd[0])
				built_in(nds,nds->cmd,env,&tenv);
			if(nds->cmd[0])
				cmd = acc(nds->cmd[0],tenv);
				if(cmd != NULL)
				{
						signal(SIGINT,handler);
						if(nds->cmd[0])
							if(!if_built_in(nds->cmd[0]))
							{
								if(nds->cmd[0][0] == '/' || nds->cmd[0][0] == '.')
									execve(nds->cmd[0],nds->cmd,env);
								else
									execve(cmd,nds->cmd,env);
							}
				}
}
void do_infile_multiproc(t_nodes *nds,t_env *tenv,char **env)
{
		int fd_tmp;
		int i;

		i = -1;
		if(*nds->infile)
			{	
				i = -1;
				fd_tmp = dup(1);
				while(nds->infile[++i])
				{
					 infile_redirect(nds->infile[i],fd_tmp); 
					if(nds)
						execution_muliproc(nds,env,tenv);
				}
				dup2(fd_tmp,1);
				
			}
			else
				execution_muliproc(nds,env,tenv);

}
void single_proc(t_nodes *nds,t_env *tenv,char **env)
{
	int i;
	int cpy;

	i = -1;
	cpy = dup(0);
	if(nds)
	{
			do_hrd(nds);
			do_infile(nds,tenv,env);
			if(*nds->append)
				while(nds->append[++i])
					append_redirect(nds->append[i]);
				//do_outfile(nds,tenv,env);
			//nds = nds->next;
			dup2(cpy,0);
	}
}

void multi_proc(t_nodes *nds,t_env *tenv,char **env)
{
	int i;
	int cpy;
	int pd[2];
	int pid;

	i = -1;
	cpy = dup(0);
	
	while (nds != NULL)
	{
		pipe(pd);
		pid = fork();
		if (pid == 0)
		{
			dup2(pd[1],1);
			do_hrd(nds);
			do_infile_multiproc(nds,tenv,env);
			nds = nds->next;
			dup2(cpy,0);
			exit(1);
		}
		else
		 	wait(NULL);		
			dup2(pd[0],0);
		close(pd[1]);
		
	}
	

	/* while(nds!= NULL)
		{
			int i = -1;
			do_hrd(nds);
			do_infile(nds,tenv,env);
			if(*nds->append)
				while(nds->append[++i])
					append_redirect(nds->append[i]);
				//do_outfile(nds,tenv,env);
			nds = nds->next;
			dup2(cpy,0);
		} */
}