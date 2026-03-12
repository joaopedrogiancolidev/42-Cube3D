#include "parser.h"

static const char	*line_type_name(char *line)
{
	if (is_empty_line(line))
		return ("EMPTY");
	if (is_element_line(line))
		return ("ELEMENT");
	if (is_map_line(line))
		return ("MAP");
	return ("INVALID");
}

int	main(int argc, char **argv)
{
	char	*line;
	char	*line_type;
	int		fd;
	int		has_invalid;
	int		line_no;

	if (argc != 2)
	{
		ft_printf("Usage: ./parser_demo <map.cub>\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: could not open file: %s\n", argv[1]);
		return (1);
	}
	has_invalid = 0;
	line_no = 1;
	line = get_next_line(fd);
	while (line)
	{
		line_type = (char *)line_type_name(line);
		if (ft_strncmp(line_type, "INVALID", 8) == 0)
		{
			has_invalid = 1;
			ft_printf("Error: invalid line at %d\n", line_no);
		}
		ft_printf("line[%d] %s | %s", line_no, line_type, line);
		free(line);
		line = get_next_line(fd);
		line_no++;
	}
	close(fd);
	if (has_invalid)
		return (1);
	return (0);
}

/*
Qual a minha estrutura de retorno do parsing:

- o arquivo (), para cada No, s leste oeste. Criar uma variavel char dentro da estrutura da lista.
- Fazer a mesma coisa com aqueles F e C.
- Para poder "pintar" vamos utilizar hexadecimal, rgb. 
- Struct e dentro dessa struct rgb-> ela receberia o "teto", "chao" int

struct path (n,s, o)

struct name_struct{
       rgb teto;
      rgb  chao;

}
struct rgb{
       int gren;
       int blue;
       int red;
       int opacidade
}

color = ft_pixel(220, 100, 0, 0xFF);
se nao ter opacidade colocar ela como (1).

PRECISAR RETORNAR O MAPA COM ESSAS DIMENSOES

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

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

vou ler a primeira linha do mapa do mapa e ai proxima linha outro linha. (usar para calculo)
*/