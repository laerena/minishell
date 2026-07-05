"minishell$ ls "*.txt"

ls: cannot access '*.txt': No such file or directory

minishell$ ls '*.txt'

ls: cannot access '*.txt': No such file or directory

minishell$ ls "*"

ls: cannot access '*': No such file or directory

minishell$ ls '*'

ls: cannot access '*': No such file or directory

minishell$ echo "$HOME"

/home/vrb

minishell$ echo '$HOME'

$HOME

minishell$ echo "$USER.txt"

vrb.txt

minishell$ echo $USER"abc"

vrbabc

minishell$ echo "$USER""$USER"

vrbvrb

minishell$ echo ""



minishell$ echo ''



minishell$ echo ""



minishell$ echo



minishell$ ls ""

ls: cannot access '': No such file or directory

minishell$ ls ''

ls: cannot access '': No such file or directory", "minishell$ ls *

a.supp  Makefile  minishell  README.md  t1.txt  t2.txt



doc:

executor.md  notes210526.txt  parser.md



include:

builtins.h  executor.h  init.h   minishell.h   parser.h  utils.h

error.h     expander.h  lexer.h  ms_signals.h  struct.h



libft:

include  libft.a  Makefile  README.md  src



src:

builtins  expander  lexer   main.o  signals    utils

executor  init      main.c  parser  signals.o  wildcards

minishell$ ls *.nonexistentextension

ls: cannot access '*.nonexistentextension': No such file or directory

minishell$ ls ****

a.supp  Makefile  minishell  README.md  t1.txt  t2.txt



doc:

executor.md  notes210526.txt  parser.md



include:

builtins.h  executor.h  init.h   minishell.h   parser.h  utils.h

error.h     expander.h  lexer.h  ms_signals.h  struct.h



libft:

include  libft.a  Makefile  README.md  src



src:

builtins  expander  lexer   main.o  signals    utils

executor  init      main.c  parser  signals.o  wildcards

minishell$ ls *.*

a.supp  README.md  t1.txt  t2.txt

minishell$ ls .*

.gitignore  .gitmodules



.:

a.supp  doc  include  libft  Makefile  minishell  README.md  src  t1.txt  t2.txt



..:

minishell



.git:

branches        config       FETCH_HEAD  hooks  info  modules  ORIG_HEAD    refs

COMMIT_EDITMSG  description  HEAD        index  logs  objects  packed-refs

minishell$ ", "minishell$ cat < infile

open: No such file or directory

minishell$ echo "Inside infile" > infile

minishell$ ls

a.supp  include  libft     minishell  src     t2.txt

doc     infile   Makefile  README.md  t1.txt

minishell$ cat < infile

Inside infile

minishell$ cat < "infile"

open: No such file or directory

minishell$ cat < 'infile'

open: No such file or directory

minishell$ cat > outfile

i m writing in terminal

^Cminishell$ ls

a.supp  include  libft     minishell  README.md  t1.txt

doc     infile   Makefile  outfile    src        t2.txt

minishell$ cat >> outfile

continuing to append in terminal



^Cminishell$ cat outfile 

i m writing in terminal



continuing to append in terminal





minishell$ cat > "out put"

creating new file  

^Cminishell$ 

"out put"    .gitmodules  a.supp       infile       outfile      t2.txt

.git/        Makefile     doc/         libft/       src/         

.gitignore   README.md    include/     minishell    t1.txt       

minishell$ cat "out put"

cat: 'out put': No such file or directory

minishell$ ls

 a.supp   include   libft      minishell  '"out put"'   src      t2.txt

 doc      infile    Makefile   outfile     README.md    t1.txt

minishell$ cat '"out put"'

creating new file



minishell$ cat < ""

open: No such file or directory

minishell$ cat > *

i m writing in * so weird

^Cminishell$ 

minishell$ ls

'*'       doc       infile   Makefile    outfile      README.md   t1.txt

 a.supp   include   libft    minishell  '"out put"'   src         t2.txt

minishell$ cat '*'

i m writing in * so weird



minishell$ ", "minishell$ cat << eof

> hello

> world

> eof

hello

world

minishell$ cat << "eof"

> $HOME

> eof

> "eof"

/home/vrb

eof

minishell$ cat << eof > file

> test

> eof

minishell$ cat file

test

minishell$ ", "minishell$ ls | grep txt | wc -l

2

minishell$ echo hello | cat | cat | cat

hello

minishell$ ls | ls | ls | ls

'*'       doc    include   libft      minishell  '"out put"'   src      t2.txt

 a.supp   file   infile    Makefile   outfile     README.md    t1.txt

minishell$ false && echo nope

minishell$ true && echo yes

yes

minishell$ false || echo fallback

fallback

minishell$ true || echo nope

minishell$ ", "minishell$ echo "a*b" | cat

a*b

minishell$ ls "*"

ls: cannot access 'out put': No such file or directory

minishell$ echo "$USER*" | cat

vrb*

minishell$ echo $NOT_EXISTING_VAR



minishell$ echo $?

0

minishell$ echo $$$$

$$$$

minishell$ echo $?

0

minishell$ echo "$?"

0

minishell$ ls |

minishell: syntax error: unexpected operator

minishell$ ls &&

minishell: syntax error: unexpected operator

minishell$ ls ||

minishell: syntax error: unexpected operator

minishell$ |

minishell: syntax error: unexpected operator

minishell$ ", "minishell$ echo > >

minishell: syntax error: expected file

minishell$ echo < <

minishell: syntax error: expected file

minishell$ "   "

   : command not found

minishell$ '   '

   : command not found

minishell$ echo             hello

hello

minishell$ echo "hello           world"

hello           world

minishell$ echo "$USER"*.txt

vrb*.txt

minishell$ ls "$HOME"/*

ls: cannot access '/home/vrb/*': No such file or directory

minishell$ ls "$HOME"/*.c

ls: cannot access '/home/vrb/*.c': No such file or directory

minishell$ ", 