Priorité 1 — Corrections importantes
Faire un ft_cleanup() global (AST, env, allocations temporaires, readline, FDs)
Lancer Valgrind après cleanup et corriger les leaks mémoire
Vérifier les leaks de FD avec --track-fds=yes
Tester les erreurs de redirections (<, >, >>, permissions, fichiers inexistants)
Vérifier les pipes (fermeture des FDs, deadlocks, status final)
Vérifier les signaux (Ctrl-C, Ctrl-D, heredoc)

Priorité 2 — Tests comportement bash
Tester les heredocs complexes (<< a << b, pipe, &&, ||)
Vérifier le status $? après toutes les erreurs (126, 127, 130, etc.)
Tester builtins avec et sans pipe (export, cd, unset, exit)
Vérifier les cas limites de PATH (unset PATH, PATH=)

Priorité 3 — Nettoyage avant rendu
Supprimer les debug prints
Retirer les anciens commentaires/tests temporaires
Passer norminette
Vérifier tous les malloc, open, pipe, fork, dup2, close
Faire une dernière campagne de tests bash vs minishell

Déjà validé
Execve + gestion errno
command not found
Permission denied
Is a directory
Exec format error
Gestion des heredoc FD
Fermeture des heredoc après exécution/erreur