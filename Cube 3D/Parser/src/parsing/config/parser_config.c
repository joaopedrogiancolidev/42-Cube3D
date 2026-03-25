#include "parser.h"

/*
** Initializes the element configuration structure to a safe empty state.
** Called once at the start of load_file_lines().
*/
void	init_parser_config(t_parser_config *cfg)
{
	cfg->no_path = NULL;
	cfg->so_path = NULL;
	cfg->we_path = NULL;
	cfg->ea_path = NULL;
	cfg->f_raw = NULL;
	cfg->c_raw = NULL;
}

/*
** Releases every dynamically stored element value.
** Called on all parser exits (success and error) to avoid leaks.
*/
void	free_parser_config(t_parser_config *cfg)
{
	free(cfg->no_path);
	free(cfg->so_path);
	free(cfg->we_path);
	free(cfg->ea_path);
	free(cfg->f_raw);
	free(cfg->c_raw);
}