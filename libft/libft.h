/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoyzuet <vgoyzuet@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:48:23 by vgoyzuet          #+#    #+#             */
/*   Updated: 2025/06/27 05:51:29 by vgoyzuet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

# include <stdarg.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define MAX_FD 1024

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*Libft->mandatory*/

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strcpy(char *s2, char *s1);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t num, size_t size);
char	**ft_realloc(char **envp, int size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putcharfd(char c, int fd);
void	ft_putstrfd(char *str, int fd);
void	ft_putendlfd(char *s, int fd);
void	ft_putnbrfd(int n, int fd);

long	ft_atol(const char *str);
int		ft_abs(int x);

/*Libft->linked list*/

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*ft_printf*/
int		ft_printf(char const *format, ...);
int		ft_printf_fd(int fd, char const *format, ...);
void	ft_perror(char *error);
void	ft_print_stack(t_list *stack, char *str);

int		ft_putchar_fd(char ch, int fd);
int		ft_putstr_fd(char *str, int fd);
int		ft_putptr_fd(void *ptr, int fd);
int		ft_putnbr_fd(int nbr, int fd);
int		ft_putunsnbr_fd(unsigned int unsnbr, int fd);
int		ft_puthex_fd(unsigned long long num, char format, int fd);

/*get_next_line*/
char	*get_next_line(int fd);

/*free*/
void	free_array(char **arr, int i);

#endif
