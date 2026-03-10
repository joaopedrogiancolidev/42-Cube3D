# Parser prototype

Este diretório contém um protótipo isolado para estudar o começo do parser do `cube3d`.
Agora o código do parser fica dentro da pasta `Parser/`.

## Estrutura

- `Parser/includes/` -> headers
- `Parser/src/` -> arquivos `.c`
- `Parser/src/parsing/` -> lógica específica do `.cub`
- `Parser/src/utils/` -> helpers reutilizáveis
- `Parser/obj/` -> objetos gerados pelo `Makefile`
- `sample_maps/` -> exemplos `.cub`

## O que ele faz agora

- abre um arquivo `.cub`
- lê linha por linha
- salva as linhas em memória
- imprime cada linha com índice

## O que ainda não faz

- separar config e mapa
- validar `NO`, `SO`, `WE`, `EA`, `F`, `C`
- normalizar o mapa
- validar fechamento

## Como pensar nesse começo

A primeira meta do parser não é validar o mapa inteiro.
A primeira meta é conseguir responder:

1. quantas linhas existem no arquivo?
2. quais são essas linhas exatamente?
3. onde começa o mapa?

## Próximo passo sugerido

Depois disso, crie uma função que percorre `file_lines.lines[i]` e decide:

- linha vazia
- linha de elemento (`NO`, `SO`, `WE`, `EA`, `F`, `C`)
- linha de mapa

## Como testar

```bash
cd Parser
make
./parser_demo ../sample_maps/valid_minimal.cub
```

## Visualização sem texturas

Para abrir uma janela MLX e visualizar o mapa em cores (sem usar `NO/SO/WE/EA`):

```bash
cd Parser
make visual
./visual_demo ../sample_maps/valid_minimal.cub
```

Você também pode abrir um mapa inválido para inspeção visual:

```bash
./visual_demo ../sample_maps/invalid_open.cub
```

## Observação

Este protótipo usa `getline` por simplicidade didática.
No projeto final da 42, você pode trocar essa leitura por `get_next_line`.
