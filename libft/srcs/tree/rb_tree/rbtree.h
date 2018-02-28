/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbtree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 17:35:39 by ddinaut           #+#    #+#             */
/*   Updated: 2017/09/25 17:36:06 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_H
# define RBTREE_H

# include <stdlib.h>

typedef enum tree_color
{
	RED,
	BLACK
}			t_color;

typedef struct		s_rbtree
{
	int				hash;
	void			*data;
	t_color			color;
	struct s_rbtree	*left;
	struct s_rbtree	*right;
	struct s_rbtree	*parent;
}					t_rbtree;

typedef int (*compare_func)(void *left, void *right);

/* Insertion */

void		insert_case1(t_rbtree *n);
void		insert_case2(t_rbtree *n);
void		insert_case3(t_rbtree *n);
void		insert_case4(t_rbtree *n);
void		insert_case5(t_rbtree *n);

/* Deletion */

void		delete_case1(t_rbtree *n);
void		delete_case2(t_rbtree *n);
void		delete_case3(t_rbtree *n);
void		delete_case4(t_rbtree *n);
void		delete_case5(t_rbtree *n);
void		delete_case6(t_rbtree *n);

/* Utils */
void		rotate_right(t_rbtree *n, t_rbtree *g);
void		rotate_left(t_rbtree *n, t_rbtree *g);

int			compare_node(void *leftp, void *rightp);
t_rbtree	*new_node(void *data);
void		insert_node(t_rbtree **root, void *data, compare_func compare);
t_rbtree	*search_node(t_rbtree **root, void *data, compare_func compare);

/* Family */

t_rbtree	*uncle(t_rbtree *n);
t_rbtree    *sibling(t_rbtree *n);
t_rbtree	*grandparent(t_rbtree *n);

#endif
