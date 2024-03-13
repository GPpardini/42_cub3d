/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpardini <gpardini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:12:18 by gpardini          #+#    #+#             */
/*   Updated: 2024/02/27 13:03:05 by gpardini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//static function for general that return my variable anywhere in the code
t_data  *data(void)
{
    static t_data data;
    return(&data);
}

//static function for mlx that return my variable anywhere in the code
t_game  *g(void)
{
    static t_game game;
    return(&game);
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

//cut white spaces from the begginig and/or from the end of a string
char    *clean_string(char *s, int i, int flag)
{
    int start;
    int end;
    char *new;

    if (flag == 1)
    {
        while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
            i++;
        start = i;
    }
    else
        start = 0;
    i = ft_strlen(s) - 1;
    while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
        i--;
    new = (char *)malloc(sizeof(char *) * (i - start + 1));
    end = i;
    new[end + 1] = '\0';
    i = 0;
    while (start <= end)
        new[i++] = s[start++];
    return(new);
}

//choose the varible to store the clean_string()
void    start_token(char *s, int flag)
{   
    //printf("start token = |%s|\n", s);
    if (flag == 1)
        data()->map_NO = clean_string(s, 2, 1);
    else if (flag == 2)
        data()->map_SO = clean_string(s, 2, 1);
    else if (flag == 3)
        data()->map_WE = clean_string(s, 2, 1);
    else if (flag == 4)
        data()->map_EA = clean_string(s, 2, 1);
    else if (flag == 5)
        data()->map_F = clean_string(s, 1, 1);
    else if (flag == 6)
        data()->map_C = clean_string(s, 1, 1);
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
        printf("MAP->|%s|\n", data()->map[i]);
        i++;
    }
    printf("------------------- MORE ------------------\n");
    //printf("data()->player_x = |%d|\n", data()->player_x);
    //printf("data()->player_y = |%d|\n", data()->player_y);
    //printf("data()->player_d = |%c|\n", data()->player_d);
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
            data()->map[i] = clean_string(tmp, 0, 0);
            i++;
        }
        if (check_for_token(tmp) == 6)
            flag = 1;
        free(tmp);
    }
    data()->map[i] = NULL;
}

//check for wrong chars in map matriz, and return a value
int     check_char(char c)
{
    if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W'
        && c != 'E' && c != ' ' && c != '\n')
        return(1);
    if ((c == 'N' || c == 'S' || c == 'W' || c == 'E'))
        return(2);
    else
        return(0);
}

//loop the entire matriz searching for chars errors, and save playerPOS
void    map_check_matriz(void)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (data()->map[y])
    {
        while(data()->map[y][x])
        {
            if (check_char(data()->map[y][x]) == 1)
            {
                printf("DEBUG check_char: |%c|\n", data()->map[y][x]);
                printf("Error in file_to_check()\n");
            }
            if (check_char(data()->map[y][x]) == 2)
            {
                data()->player_x = x;
                data()->player_y = y;
                data()->player_d = data()->map[y][x];
            } 
            x++;
        }
        x = 0;
        y++;        
    }
}

//check if the map is surrounded and if have Player exit proportions
void    map_flood_fill(int x, int y, char **map, int size)
{
    if(y < 0 || y >= size || x < 0 || map[y][x] == '1' || map[y][x] == '-' || map[y][x] == 'P')
    {
        return;
    }
    if(ft_strlen(map[y]) <= x)
    {
        return;
    }
	if(map[y][x] == ' ')
    {
        printf("Flood_fill found a leak in the map[%d][%d]\n", y, x);
        return;
    }
    if(check_char(map[y][x]) == 2)
    {
        printf("Flood_fill found a Player[%d][%d]\n", y, x);
        map[y][x] = 'P';
    }
	if (map[y][x] == '0')
		map[y][x] = '-';
	map_flood_fill(x + 1, y, map, size); 
	map_flood_fill(x - 1, y, map, size);
	map_flood_fill(x, y + 1, map, size);
	map_flood_fill(x, y - 1, map, size);
}

//Save and check every imput before the game starts
void    parsing(char **av)
{
    file_is_cub(av[1]);
    file_settings(open(av[1], O_RDONLY));
    file_to_map(open(av[1], O_RDONLY));
    map_check_matriz();
    map_flood_fill(data()->player_x, data()->player_y, data()->map, data()->map_y);
    map_print();
}

//function to simple check if you give a valid AC, exit program if false.
void is_ac_valid(int ac)
{
    if (ac == 2)
        return ;
    else
    {
        printf("Wrong format, you should use -> ./cub3D [path_to_map]\n");
        exit(0);        
    }
}

//function that init mlx and open a new windown
void    init_mlx(void)
{
    g()->mlx = mlx_init();
    g()->mlx_win = mlx_new_window(g()->mlx, 600, 600, "Cub2d");
}

//function that return a trgb pattern to use
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

//test function to learn how to use pixels in mlx
void    init_img(void)
{
    t_img img;
    img.img = mlx_new_image(g()->mlx, 600, 600);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    
    int x = 0;
    int y = 0;
    int color_down = create_trgb(1, 1, 120, 50);
    int color_up = create_trgb(1, 1, 50, 120);
    int color = color_down;
    while (x <= 600)
    {
        if (x > 300)
            color = color_up;
        while(y <= 600)
        {
            my_mlx_pixel_put(&img, y, x, color);
            y++;
        }
        y = 0;
        x++;
        // color = create_trgb(y, x, y, 1);
    }
    render_this_shit(&img);
	mlx_put_image_to_window(g()->mlx, g()->mlx_win, img.img, 0, 0);
}



void close_win(void)
{
    exit(0);
}
int	key_manager(int keycode)
{
	if (keycode == 0xff1b)
		close_win();
	// if (keycode == 0xff52)
	// 	move_up();
	// if (keycode == 0xff54)
	// 	move_down();
	// if (keycode == 0xff53)
	// 	move_right();
	// if (keycode == 0xff51)
	// 	move_left();
	return (0);
}

int main(int ac, char **av)
{
    is_ac_valid(ac);
    parsing(av);
    init_mlx();
    init_img();
    //.
    mlx_key_hook(g()->mlx_win, key_manager, g());
    mlx_hook(g()->mlx_win, 17, 1l << 17, (void *)close_win, g());
    //.
    mlx_loop(g()->mlx);
    return(0);
}

