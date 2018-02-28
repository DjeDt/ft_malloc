/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 20:10:22 by ddinaut           #+#    #+#             */
/*   Updated: 2018/01/18 14:43:48 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

/*
** buff_size used for get_next_line
*/
# define BUFF_SIZE 1

/*
** defined color for print color func
*/
# define RED_COL		"\e[31m"
# define CYAN_COL		"\e[36m"
# define BLUE_COL		"\e[34m"
# define GREEN_COL		"\e[32m"
# define YELLOW_COL		"\e[33m"
# define MAGENTA_COL	"\e[35m"
# define LIGHT_RED		"\e[91m"
# define LIGHT_GRAY		"\e[37m"
# define LIGHT_CYAN		"\e[96m"
# define LIGHT_BLUE		"\e[94m"
# define LIGHT_GREEN	"\e[92m"
# define LIGHT_YELLOW	"\e[93m"
# define LIGHT_MAGENTA	"\e[95m"
# define DARK_GRAY		"\e[90m"
# define WHITE			"\e[97m"
# define END_COL		"\e[0m"

/*
** func used to compare data in red&black_tree
*/
typedef int	(*compare_func)(void *left, void *right);

/*
** Struct used for list func
*/
typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

/*
** Struct used for binary tree
*/
typedef struct		s_btree
{
	struct s_btree	*root;
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;

/*
** Enum used for red&black tree
*/
typedef enum		s_color
{
	RED,
	BLACK
}					t_color;

/*
** Struct used for red&black tree
*/
typedef struct		s_rbtree
{
	int				hash;
	void			*data;
	t_color			color;
	struct s_rbtree	*left;
	struct s_rbtree	*right;
	struct s_rbtree	*parent;
}					t_rbtree;

/*
** str func
*/
size_t				ft_strlen(const char *str);
size_t				ft_strnlen(const char *str, char c);
int					ft_count_char(const char *str, const char c);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strdup(const char *src);
char				*ft_strndup(const char *src, size_t n);
void				ft_strreplace(char *old, char *new);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big, const char *lit, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strfsub(char *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_fl(char *s1, const char *s2);
char				*ft_strjoin_fr(char const *s1, char *s2);
char				*ft_strjoin_fb(char *s1, char *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				**ft_strtok(const char *str, const char *delim);
void				ft_bzero(void *s, size_t n);
char				*ft_itoa(int n);
char				*ft_itoa_base(int value, int base);
int					ft_atoi(const char *str);

/*
** Array func
*/
char				**ft_arrcpy(char **dst, char **src);
char				**ft_arrdup(char **array);
char				**ft_arrldup(char **arr, size_t max);
char				**ft_arrjoin(char **array, char *add);
char				**ft_arrfjoin(char **array, char **add);
void				ft_arrprint(char **array);
void				ft_arrfree(char ***array);
size_t				ft_arrlen(char **array);
char				**ft_split_whitespaces(char *str);

/*
** List Func
*/
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** Mem func
*/
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/*
** Print func
*/
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr(const char *str);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int nb);
void				ft_putnbr_fd(int n, int fd);
void				ft_print_binary(unsigned int n);
void				ft_putendl_col(const char *str, char *color);
void				ft_putendl_col_fd(const char *s, int fd, char *color);
void				ft_putstr_col(const char *str, char *color);

/*
** Binary_tree func
*/
t_btree				*btree_create_node(void *item);
void				btree_insert_data(t_btree **root, void *item, \
										int (*cmpf)(void *, void *));
void				btree_apply_prefix(t_btree *root, void(*applyf)(void *));
void				btree_apply_infix(t_btree *root, void(*applyf)(void *));
void				btree_apply_suffix(t_btree *root, void(*applyf)(void *));
void				*btree_search_item(t_btree *root, void *data_ref, \
										int (*cmpf)(void *, void *));
void				btree_apply_by_lvl(t_btree *root, void (*applyf)(void *item,
													int cur_lvl, int is_first));
int					btree_lvl_count(t_btree *root);
int					count_node(t_btree *tr);

/*
** Red & black tree
*/
void				insert_case1(t_rbtree *n);
void				insert_case2(t_rbtree *n);
void				insert_case3(t_rbtree *n);
void				insert_case4(t_rbtree *n);
void				insert_case5(t_rbtree *n);

void				delete_case1(t_rbtree *n);
void				delete_case2(t_rbtree *n);
void				delete_case3(t_rbtree *n);
void				delete_case4(t_rbtree *n);
void				delete_case5(t_rbtree *n);
void				delete_case6(t_rbtree *n);

void				rotate_right(t_rbtree *n, t_rbtree *g);
void				rotate_left(t_rbtree *n, t_rbtree *g);
int					compare_node(void *leftp, void *rightp);
t_rbtree			*new_node(void *data, t_rbtree *parent);
void				insert_node(t_rbtree **root, void *data,
								compare_func compare);
t_rbtree			*search_node(t_rbtree **root, void *data,
								compare_func compare);
t_rbtree			*uncle(t_rbtree *n);
t_rbtree			*sibling(t_rbtree *n);
t_rbtree			*grandparent(t_rbtree *n);

/*
** Utils
*/
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					open_file(const char *str);
int					brackets(char *s);
int					get_next_line(const int fd, char **line);

#endif
