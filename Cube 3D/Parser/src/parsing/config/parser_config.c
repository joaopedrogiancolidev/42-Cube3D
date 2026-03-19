#include "parser.h"

void	init_parser_config(t_parser_config *cfg)
{
	cfg->no_path = NULL;
	cfg->so_path = NULL;
	cfg->we_path = NULL;
	cfg->ea_path = NULL;
	cfg->f_raw = NULL;
	cfg->c_raw = NULL;
}

void	free_parser_config(t_parser_config *cfg)
{
	free(cfg->no_path);
	free(cfg->so_path);
	free(cfg->we_path);
	free(cfg->ea_path);
	free(cfg->f_raw);
	free(cfg->c_raw);
}