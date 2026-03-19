#ifndef PARSER_CONFIG_H
# define PARSER_CONFIG_H

typedef struct s_parser_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*f_raw;
	char	*c_raw;
}t_parser_config;

void	init_parser_config(t_parser_config *cfg);
void	free_parser_config(t_parser_config *cfg);

#endif