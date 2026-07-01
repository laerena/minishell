TODO:
- use the new struct to treat multilpe redirs as a single node with a list of redirs

SUGGESTION:
struct: new redircmd to fix redirs problem (should accumulate all successives redirs in ONE node)
// typedef struct s_redircmd
// {
// 	t_cmd				*cmd;
// 	t_redir_type		type;
// 	char				*file; //will be limiter for heredoc (could rename it)
// 	int					heredoc_expand;
// 	struct s_redircmd	*next //used to chain successive redirs
// }	t_redircmd;