/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpardini <gpardini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:12:18 by gpardini          #+#    #+#             */
/*   Updated: 2024/02/06 15:25:17 by gpardini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//static function that return my variable anywhere in the code
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
    while(f && f[i])
        i++;
    if  (f[i] && (f[i] == 'b' && f[i - 1] == 'u' && f[i - 2] == 'c' && f[i - 3] == '.'))
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
        else if (s[0] == 'C')
            return (6);
    }
    return(0);
}

//cut white spaces from the begginig and the end of a string
char    *clean_string(char *s, int i)
{
    int start;
    int end;
    char *new;

    while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
        i++;
    start = i;
    i = ft_strlen(s) - 1;
    while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
        i--;
    new = (char *)malloc(sizeof(char *) * (i - start + 1));
    end = i;
    new[end + 1] = '\0';
    i = 0;
    while (start <= end)
    {
        //printf("new[%d] = |%c| old[%d] = |%c|\n", i, new[i], start, s[start]);
        new[i] = s[start];
        i++;
        start++;
    }
    return(new);
}

//choose the varible to store the clean_string()
void    start_token(char *s, int flag)
{   
    //printf("start token = |%s|\n", s);
    if (flag == 1)
        data()->map_NO = clean_string(s, 2);
    else if (flag == 2)
        data()->map_SO = clean_string(s, 2);
    else if (flag == 3)
        data()->map_WE = clean_string(s, 2);
    else if (flag == 4)
        data()->map_EA = clean_string(s, 2);
    else if (flag == 5)
        data()->map_F = clean_string(s, 1);
    else if (flag == 6)
        data()->map_C = clean_string(s, 1);
}

//check and save the texture paths give by the map using GET_NEXT_LINE
//and count and save the map_y for future processing "flag and data()->"
int file_settings(int fd)
{
    char *tmp;
    int flag;
    
    flag = 0;
    if (fd < 0)
        return(0);
    while ((tmp = get_next_line(fd)) != NULL)
    {
        if(check_for_token(tmp) > 0)
        {
           start_token(tmp, check_for_token(tmp));
           if (check_for_token(tmp) == 6)
                flag = 1;
        }
        if (flag == 1)
            data()->map_y = data()->map_y + 1;
        free(tmp);
    }
    return (1);
}

//debugging function that print tokens variables and the map
void    map_print(void)
{
    printf("------------ PARSING MAP_TOKENS -----------\n");
    printf("Value NO -> |%s|\n", (data()->map_NO));
    printf("Value SO -> |%s|\n", (data()->map_SO));
    printf("Value WE -> |%s|\n", (data()->map_WE));
    printf("Value EA -> |%s|\n", (data()->map_EA));
    printf("Value F  -> |%s|\n", (data()->map_F));
    printf("Value C  -> |%s|\n", (data()->map_C));
    printf("---------------- PRINT MAP ----------------\n");
    int i = 0;
    while(data()->map[i])
    {
        printf("MAP->|%s", data()->map[i]);
        i++;
    }
    printf("------------------- END -------------------\n");
}

//Malloc the map into data() using GET_NEXT_LINE
void    file_to_map(int fd)
{
    char *tmp;
    int flag;
    int i;

    flag = 0;
    i = 0;
    data()->map = (char **)malloc(sizeof(char *) * (data()->map_y + 1));
    //if (!data()->map)
    while ((tmp = get_next_line(fd)) != NULL)
    {
        if (flag == 1 && tmp[0] != '\n')
        {
            data()->map[i] = tmp;
            i++;
        }
        if (check_for_token(tmp) == 6)
            flag = 1;
    }
    data()->map[i] = NULL;
}

void    file_check(void)
{
    
}

//Save and check every imput before the game starts
void    parsing(char **av)
{
    file_is_cub(av[1]);
    file_settings(open(av[1], O_RDONLY));
    file_to_map(open(av[1], O_RDONLY));
    file_check();
    map_print();
}

int main(int ac, char **av)
{
    (void)ac;
    parsing(av);
    return(0);
}

