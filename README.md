# git submodule:
# clones the repo and clone libft inside
git clone --recurse-submodules <minishell.repo>

# gets the libft at the commit the repo expects
git submodule update --init --recursive
# updates libft to the latest commit on its remote branch
# uses when libft get new commits to update the -v we dl here
git submodule update --remote

# SO COOL
