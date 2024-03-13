/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpardini <gpardini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:24:11 by gpardini          #+#    #+#             */
/*   Updated: 2024/02/27 13:12:07 by gpardini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void calcularNovaPosicao(double x, double y, double angulo, double distancia, double *novoX, double *novoY)
{
    // Convertendo o ângulo para radianos
    double anguloRadianos = angulo * M_PI / 180.0;

    // Calculando as novas coordenadas
    *novoX = x + distancia * cos(anguloRadianos);
    *novoY = y + distancia * sin(anguloRadianos);
}

int c(double valorDouble) {
    int valorInt = (int)valorDouble;
    return valorInt;
}

double cast_ray(double p_x, double p_y, double angulo)
{
    //sem usar dda.
    double result = 0;
    double int_px = p_x;
    double int_py = p_y;
    while(p_x < 10 && p_y < 10)
    {
        calcularNovaPosicao(p_x, p_y, angulo, 0.1, &p_x, &p_y);
        printf("vaitomarnocu\n");
        if(data()->map[c(p_y)][c(p_x)] && data()->map[c(p_y)][c(p_x)] == 1)
        {
            printf("vaitomarnocdfasdfasdfu\n");
            break;
        }
    }
    result = sqrt(pow(p_x - int_px, 2) + pow(p_y - int_py, 2));
    return (result);
}

void    draw_vertical_line(t_img *img, double distance, int pos)
{
    double tamanho = 64 / distance * 277;
    int y = 150;
    while(y < tamanho)
    {
        my_mlx_pixel_put(img, pos, (y), 0x00FF0000);
        y++;
    }
}

void render_this_shit(t_img *img)
{
    double p_y = 3.5;
    double p_x = 3.5;
    double fov = 60;
    double angulo = 90;
    int largura = 600;
    int i = 0;
    double angulo_cast = angulo + (fov / 2);
    double distancia = 0;

    while (i < largura)
    {
        distancia = cast_ray(p_x, p_y, angulo_cast);
        angulo_cast = angulo_cast - 0.1;
        draw_vertical_line(img, distancia, i);
        i++;
    }
}
