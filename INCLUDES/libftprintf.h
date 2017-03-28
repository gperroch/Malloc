/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/17 10:45:55 by gperroch          #+#    #+#             */
/*   Updated: 2016/03/25 11:48:15 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# define BUFF_SIZE_GNL 32
# include <string.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <wchar.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>

typedef	struct			s_list_gnl
{
	int					fd;
	char				*poubelle;
	struct s_list_gnl	*next;
}						t_list_gnl;

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

int						ft_atoi(const char *str);
void					ft_bzero(void *s, size_t n);
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
char					*ft_itoa(int n);
void					*ft_memalloc(size_t size);
void					*ft_memccpy(void *dst, const void *src,
		int c, size_t n);
void					*ft_memchr(const void *str, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					ft_memdel(void **ap);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memset(void *s, int c, size_t len);
void					ft_putchar(char c);
void					ft_putchar_fd(char c, int fd);
void					ft_putendl(char const *s);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr(int n);
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr(char const *s);
void					ft_putstr_fd(char const *s, int fd);
double					ft_sqrt(double nb);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strchr(const char *s, int c);
void					ft_strclr(char *s);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strcpy(char *dst, const char *src);
void					ft_strdel(char **as);
char					*ft_strdup(const char *s1);
int						ft_strequ(char const *s1, char const *s2);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
size_t					ft_strlen(const char *s);
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s,
		char (*f)(unsigned int, char));
char					*ft_strncat(char *s1, const char *s2, size_t n);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strncpy(char *dst, const char *src, size_t n);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strnew(size_t size);
char					*ft_strnstr(const char *s1, const char *s2, size_t n);
char					*ft_strrchr(const char *s, int c);
char					**ft_strsplit(char const *s, char c);
char					*ft_strstr(const char *s1, const char *s2);
char					*ft_strsub(char const *s, unsigned int start,
		size_t len);
char					*ft_strtrim(char const *s);
int						ft_tolower(int c);
int						ft_toupper(int c);
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstadd(t_list **alst, t_list *new);
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
size_t					ft_lstlen(t_list *beginlist);
t_list					*ft_lstdup(t_list *beginlist);
size_t					ft_strlenchr(const char *str, int c);
char					*ft_strdupchr(const char *str, int c);
char					*ft_strndup(const char *str, size_t n);
int						ft_printf(char *const format, ...);
void					ft_close_regex(char *restrict *format, char specifier);
int						ft_print_regex(char *restrict *format, va_list ap);
char					*ft_print_conv(char *format, va_list ap,
		char specifier, int *size_s);
char					*ft_print_extra(char *format, char **regex_printed,
		char specifier, int size_s);
char					*ft_print_integers(char *convchars, va_list ap);
char					*ft_print_ptr(char *convchars, va_list ap, int *size_s);
char					*ft_itoabase(intmax_t nb, int base);
char					*ft_itoabase_unsigned(uintmax_t nb, int base);
void					ft_swap(char *a, char *b);
char					ft_print_specifier(char *format);
void					ft_modif_flags(char *format, char **regex_printed,
		char specifier, char *flags);
int						ft_fieldwidth(char *format, char **regex_printed,
		char specifier);
int						ft_precision(char *format, char **regex_printed,
		char specifier, int size_s);
int						ft_bitoint(char *str);
int						ft_power(int a, int b);
char					*ft_wchar_display(uintmax_t arg);
char					*ft_one(unsigned int value);
char					*ft_two(unsigned int value);
char					*ft_three(unsigned int value);
char					*ft_four(unsigned int value);
char					*ft_intostring(int *mask, int size);
int						ft_wrong_specifier(char c);
void					ft_freetab_str(char **tab, int length);
void					ft_freetab_int(int **tab, int length);
int						*ft_tabjoin_int(int **tab, int length, int nbr);
char					**ft_tabjoin_str(char ***tab, int length, char *str);
char					**ft_tabjoin_tabstr(char **tab1, int length1,
		char **tab2, int length2);
void					ft_printtab_str(char **tab, int length,
		char *separator);
void					ft_printtab_int(int *tab, int length, char *separator);
int						ft_tablen_str(char **tab);
int						get_next_line(int const fd, char **line);

#endif
