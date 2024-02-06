/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpardini <gpardini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:12:18 by gpardini          #+#    #+#             */
/*   Updated: 2024/02/06 12:28:59 by gpardini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

t_data  *data(void)
{
    static t_data data;
    return(&data);
}

//check if the file is .cub
int    file_is_cub(char *f)
{
    int i;
    
    i = 0;
    while(f[i])
        i++;
    if (f[i] == 'b' && f[i - 1] == 'u' && f[i - 2] == 'c' && f[i - 3] == '.')
        return(1);
    else
        return(0);
}

//function that searchs for tokens in the map
int check_for_token(char *s)
{
    if (s && s[0])
    {
        if (s[0] == 'N' && s[1] == 'O')
            return (1);
        else if (s[0] == 'S' && s[1] == 'O')
            return (2);
        else if (s[0] == 'W' && s[1] == 'E')
            return (3);
        else if (s[0] == 'E' && s[1] == 'A')
            return (4);
        else if (s[0] == 'F')
            return (5);
        else if (s[0] == 'N')
            return (6);
    }
    return(0);
}

char    *clean_string(char *s, int i)
{
    int start;
    char *new;
    while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
        i++;
    start = i;
    i = ft_strlen(s);
    while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
        i--;
    new = (char *)malloc(sizeof(char *) * (i - start + 1));
    new[i + 1] = '\0';
    while (i >= start)
    {
        new[i] = s[i];
        i++;
    }
    return(new);
}

void    start_token(char *s, int flag)
{
    if (flag == 1)
        data()->map_NO = clean_string(s, 1);
    else if (flag == 2)
        data()->map_SO = clean_string(s, 2);
    else if (flag == 3)
        data()->map_WE = clean_string(s, 3);
    else if (flag == 4)
        data()->map_EA = clean_string(s, 4);
    else if (flag == 5)
        data()->map_F = clean_string(s, 5);
    else if (flag == 6)
        data()->map_C = clean_string(s, 6);
}

//check and save the texture paths give by the map
int file_settings(int fd)
{
    //check if open worked;
    char *tmp;
    
    while ((tmp = get_next_line(fd)) != NULL)
    {
        if(check_for_token(tmp) > 0)
        {
           start_token(tmp, check_for_token(tmp)); 
           free(tmp);
        }
        free(tmp);
    }
    return (1);
}

void    map_print(void)
{
    printf("------------ PARSING MAP_TOKENS -----------\n");
    printf("Value NO -> |%s|\n", (data()->map_NO));
    printf("Value SO -> |%s|\n", (data()->map_SO));
    printf("Value WE -> |%s|\n", (data()->map_WE));
    printf("Value EA -> |%s|\n", (data()->map_EA));
    printf("Value F -> |%s|\n", (data()->map_F));
    printf("Value C -> |%s|\n", (data()->map_C));
    printf("---------------- PRINT MAP ----------------\n");
}

void    parsing(char **av)
{
    file_is_cub(av[1]);
    file_settings(open(av[1], O_RDONLY));
    map_print();
}

int main(int ac, char **av)
{
    (void)ac;
    parsing(av);
    return(0);
}

