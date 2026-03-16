// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include <math.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 900
#define screenHeight 900

static mlx_image_t* backgroud;
static mlx_image_t* player;


int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void apagar_pixel(void* param)
{
    uint32_t color = ft_pixel(0, 0, 0, 255);

    for (int y = 0; y < screenHeight; y++) // Percorre as linhas do array
    {
        for (int x = 0; x < screenWidth; x++) // Percorre as colunas do array
        {
            mlx_put_pixel(backgroud, x, y, color);
            
        }
    }
}

void verLine(mlx_image_t* img, int x, int drawStart, int drawEnd, uint32_t color)
{
    int y = drawStart;

    while (y <= drawEnd)
    {
        // Proteção para não desenhar fora da imagem e dar Segfault
        if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
        {
            mlx_put_pixel(img, x, y, color);
        }
        y++;
    }
}


void ft_hook(void* param)
{
    mlx_t* mlx = param;
    int tile_size = screenWidth / 24;
	apagar_pixel(mlx);
    // 1. TORNAR AS VARIÁVEIS ESTÁTICAS PARA PERSISTIREM ENTRE FRAMES
    static double posX = 4.0;
    static double posY = 4.0;
    static double dirX = -1.0; 
    static double dirY = 0.0;
    static double planeX = 0.0; 
    static double planeY = 0.66;

    // 2. LIMPAR A TELA (Essencial: senão o frame novo desenha sobre o antigo)
    // Você pode criar uma função para pintar o background de preto/cinza aqui
    // ft_memset(backgroud->pixels, 0, backgroud->width * backgroud->height * 4);

    for(int x = 0; x < screenWidth; x++)
    {
        double cameraX = 2 * x / (double)screenWidth - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        int mapX = (int)posX;
        int mapY = (int)posY;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        double sideDistX;
        double sideDistY;
        int stepX;
        int stepY;

        if(rayDirX < 0) {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if(rayDirY < 0) {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        int hit = 0;
        int side;
        while(hit == 0) {
            if(sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (mapY >= 0 && mapY < 24 && mapX >= 0 && mapX < 24) {
                if(worldMap[mapY][mapX] > 0) hit = 1; // [Y][X] Correto
            } else break;
        }

        double perpWallDist;
        if(side == 0) perpWallDist = (sideDistX - deltaDistX);
        else          perpWallDist = (sideDistY - deltaDistY);

        int lineHeight = (int)(screenHeight / perpWallDist);

        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if(drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        uint32_t color;
        // CORREÇÃO: Usar [mapY][mapX] para bater com a declaração do mapa
        switch(worldMap[mapY][mapX])
        {
            case 1:  color = ft_pixel(255, 0, 0, 255);    break;
            case 2:  color = ft_pixel(0, 255, 0, 255);    break;
            case 3:  color = ft_pixel(0, 0, 255, 255);    break;
            default: color = ft_pixel(255, 255, 255, 255); break;
        }
        if(side == 1) color = (color >> 1) & 0x7F7F7FFF; // Escurecer lado Y

        verLine(backgroud, x, drawStart, drawEnd, color);
    }
    
    // --- TEMPO E VELOCIDADE ---
    double time = mlx_get_time(); 
    static double oldTime = 0;
    double frameTime = time - oldTime;
    oldTime = time;

    double moveSpeed = frameTime * 5.0; 
    double rotSpeed = frameTime * 3.0;

    // --- ENTRADA DE TECLADO (Usando as variáveis static posX/posY) ---
    if (mlx_is_key_down(mlx, MLX_KEY_UP)) {
        if(worldMap[(int)posY][(int)(posX + dirX * moveSpeed)] == 0) posX += dirX * moveSpeed;
        if(worldMap[(int)(posY + dirY * moveSpeed)][(int)posX] == 0) posY += dirY * moveSpeed;
    }
    if (mlx_is_key_down(mlx, MLX_KEY_DOWN)) {
        if(worldMap[(int)posY][(int)(posX - dirX * moveSpeed)] == 0) posX -= dirX * moveSpeed;
        if(worldMap[(int)(posY - dirY * moveSpeed)][(int)posX] == 0) posY -= dirY * moveSpeed;
    }

    // Rotação (Atrás do cálculo do Raycast para o próximo frame)
    if (mlx_is_key_down(mlx, MLX_KEY_RIGHT)) {
        double oldDirX = dirX;
        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    if (mlx_is_key_down(mlx, MLX_KEY_LEFT)) {
        double oldDirX = dirX;
        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
        double oldPlaneX = planeX;
        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }

    // Atualiza a imagem 2D do player (Minimapa) baseada na posição double
    player->instances[0].x = (int)(posX * tile_size);
    player->instances[0].y = (int)(posY * tile_size);
}

// -----------------------------------------------------------------------------

int32_t main(void)
{
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(screenWidth, screenHeight, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(backgroud = mlx_new_image(mlx, screenWidth, screenHeight)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	printf("backgroud created with");
	//draw_minimap(mlx);
	if (mlx_image_to_window(mlx, backgroud, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	
	
	if (!(player = mlx_new_image(mlx, 24, 24)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	printf("player created with");
	//draw_player(mlx);
	if (mlx_image_to_window(mlx, player, 300, 300) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	printf("player put pixel");

	
	// mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
