# parser flow tree (short)
parse_expression
		|
		v
	  OR (||)
		|
		v
	 AND (&&)
		|
		v
	PIPE (|)
		|
		v
 COMMAND
		|
		+--> SUBSHELL ( )
		|
		+--> EXEC
		|
		+--> REDIR (< > >> <<)

# parser flow tree
parse_expression()
		|
		v
	parse_or()
		|
		+--> find top-level ||
		|
		+--> OR found:
		|	   |
		|	   +--> parse_or(left)
		|	   |
		|	   +--> parse_and(right)
		|	   |
		|	   +--> create N_OR
		|
		v
	parse_and()
		|
		+--> find top-level &&
		|
		+--> AND found:
		|	   |
		|	   +--> parse_and(left)
		|	   |
		|	   +--> parse_pipeline(right)
		|	   |
		|	   +--> create N_AND
		|
		v
	parse_pipeline()
		|
		+--> find top-level |
		|
		+--> PIPE found:
		|	   |
		|	   +--> parse_pipeline(left)
		|	   |
		|	   +--> parse_command(right)
		|	   |
		|	   +--> create N_PIPE
		|
		v
	parse_command()
		|
		+--> parse_primary()
		|	   |
		|	   +--> Parentheses found:
		|	   |	   |
		|	   |	   +--> parse_or(content)
		|	   |	   |
		|	   |	   +--> create N_SUBSHELL
		|	   |
		|	   +--> Otherwise:
		|			   |
		|			   +--> create N_EXEC
		|
		+--> parse_redirs()
				|
				+--> wrap command with N_REDIR nodes
				|
				+--> return final AST

# parser exec path
parse_expression(tokens)
│
├── check_syntax(tokens)
│
└── parse_or(start, end)
	│
	├── find_last_top_level(T_OR)
	│
	├── if OR exists:
	│	   │
	│	   ├── left  = parse_or(start, op)
	│	   │
	│	   ├── right = parse_and(op->next, end)
	│	   │
	│	   └── create N_OR node
	│
	└── if no OR:
			│
			└── parse_and(start, end)
				│
				├── find_last_top_level(T_AND)
				│
				├── if AND exists:
				│	   │
				│	   ├── left  = parse_and(start, op)
				│	   │
				│	   ├── right = parse_pipeline(op->next, end)
				│	   │
				│	   └── create N_AND node
				│
				└── if no AND:
						│
						└── parse_pipeline(start, end)
							│
							├── find_last_top_level(T_PIPE)
							│
							├── if PIPE exists:
							│	   │
							│	   ├── left  = parse_pipeline(start, op)
							│	   │
							│	   ├── right = parse_command(op->next, end)
							│	   │
							│	   └── create N_PIPE node
							│
							└── if no PIPE:
									│
									└── parse_command(start, end)
										│
										├── parse_primary(start, end)
										│   │
										│   ├── get_subshell_end(start)
										│   │   │
										│   │   └── find_matching_rparen(start)
										│   │
										│   ├── if '(' ')' found:
										│   │	   │
										│   │	   ├── inner =
										│   │	   │	  parse_or(start->next, close)
										│   │	   │
										│   │	   └── create N_SUBSHELL
										│   │
										│   └── otherwise:
										│		   │
										│		   └── parse_exec(start, end)
										│			   │
										│			   ├── tokens_to_argv()
										│			   │
										│			   └── create N_EXEC
										│
										└── parse_redirs(cmd, start, end)
											│
											├── scan tokens backwards
											│
											├── for each redirection:
											│	   │
											│	   └── wrap_redir()
											│		   │
											│		   └── create N_REDIR
											│
											└── return final command tree