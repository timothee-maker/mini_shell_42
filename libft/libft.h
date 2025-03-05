/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:30:56 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/21 10:39:53 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
void	ft_bzero(void *tab, size_t n);
void	*ft_memset(void *tab, int c, size_t count);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbrbase_fd(int nb, char *base, int fd);
void	ft_putunsnb_fd(unsigned int nb, int fd);
int		ft_strlen(char const *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t nb);
int		ft_atoi(const char *str);
int		ft_isalpha(int a);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnew(size_t size);
char	*ft_strncat(char *s1, char *s2, unsigned int nb);
char	*ft_strcat(char *s1, char *s2);
char	*ft_strcpy(char *dst, char *src);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, size_t size);
char	*ft_strncpy(char *dst, char *src, unsigned int a);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

#endif