/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabisco <vabisco@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:20:17 by vbisco            #+#    #+#             */
/*   Updated: 2026/05/25 17:25:11 by vabisco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

/* ** struct ********** */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
/* ******************** */

/* ** root ************ */
/* ******************** */

/* ** char/ *********** */
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
/* ******************** */

/* ** conv/ *********** */
int				ft_atoi(char const *str);
char			*ft_itoa(int n);
/* ******************** */

/* ** lst/ ************ */
t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
int				ft_lstsize(t_list *lst);
/* ******************** */

/* ** mem/ ************ */
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t nelem, size_t elsize);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
/* ******************** */

/* ** put/ ************ */
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
/* ******************** */

/* ** str/ ************ */
char			*ft_strchr(char const *s, int c);
char			*ft_strdup(char const *s);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, char const *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, char const *src, size_t dstsize);
size_t			ft_strlen(char const *s);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(char const *s1, char const *s2, size_t n);
char			*ft_strnstr(char const *haystack, char const *needle,
					size_t len);
char			*ft_strrchr(char const *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			**ft_split(char const *s, char c);
/* ******************** */

/* ** added *********** */
long long int	ft_atoll(char const *str);
int				ft_isspace(const char c);
int				ft_isvalid_base(char *base, size_t base_len);
char			*ft_itoa_base(int n, char *base);
char			*ft_llitoa(long long int n);
char			*ft_llitoa_base(long long int n, char *base);
char			*ft_llutoa(unsigned long long int n);
char			*ft_llutoa_base(unsigned long long int n, char *base);
char			*ft_strjoin2(int size, char **strs, char *sep);
char			*ft_strnjoin(char const *s1, char const *s2,
					size_t len1, size_t len2);
char			*ft_strset(char c, size_t size); //malloc and then memset
void			ft_strswapchar(char *str, char a, char b);
char			*ft_utoa(unsigned int n);
char			*ft_utoa_base(unsigned int n, char *base);
size_t			ft_strclen(char const *s, char c);
char			*ft_split2(char *str, char *charset);
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void			ft_strarr_free(char **arr);
int				ft_strcmp(char const *s1, char const *s2);
size_t			ft_arrlen(void **arr);
size_t			ft_ptr_index(const void *base, const void *ptr);
/* ******************** */

#endif
