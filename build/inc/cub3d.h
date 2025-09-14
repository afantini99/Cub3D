/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afantini <afantini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:14:55 by luigi             #+#    #+#             */
/*   Updated: 2024/06/26 15:48:45 by afantini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../libft/libft.h"
# include "../../minilibx/mlx.h"

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdbool.h>

# define SPEED			0.05
# define SUCCESS		0
# define FAILURE		1	

// texture (.xpm file):
# define TEX_SIZE 64
/* SCREEN_W 960 * SCREEN_H 720 */
/* SCREEN_W 640 * SCREEN_H 480 */
# define SCREEN_W		1280
# define SCREEN_H		720

//00200000 (in ottale) è una MASCHERA DI BIT utilizzata per indicare che 
//un file deve essere una directory quando viene aperto.
//O_DIRECTORY diventa disponibile nel codice anche se non è
//predefinita nell'ambiente di sviluppo.
# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# define NO				0
# define SO 			1
# define EA 			2
# define WE				3

# define FLOOR			5
# define CEILING		6

# define KEY_W				119
# define KEY_S				115
# define KEY_A				97
# define KEY_D				100
# define KEY_ARROW_LEFT		65361
# define KEY_ARROW_RIGHT	65363

# define KEY_ESC			65307

struct	s_image
{
	void	*image;					// Ptr all'immagine (serve a MiniLibX)
	int		*addr;					// Indirizzo di memoria dell'immagine
	int		bits_per_pixel;			// N_bits per pixel (profondità di colore)
	int		line_length;			// Lungh. dell' linea dell'immagine in byte
	int		endian;					// Endianness dell'immagine (ordine bytes)
	int		height;					// Altezza dell'immagine
	int		width;					// Larghezza dell'immagine
};

typedef struct s_image	t_image;

//pos, dir --> point of view
struct	s_player
{
	double		pos_x;				// Posizione X del giocatore
	double		pos_y;				// Posizione Y del giocatore
	double		dir_x;				// Dir_X del giocatore (vettore direzione)
	double		dir_y;				// Dir_Y del giocatore (vettore direzione)
	double		plane_x;			// Componente X del campo visivo
	double		plane_y;			// Componente Y del campo visivo
};

typedef struct s_player	t_player;

struct	s_ray
{
	double		ray_dir_x;			// Direzione X del raggio
	double		ray_dir_y;			// Direzione Y del raggio
	double		side_dist_x;		// Dist_X pos. attuale/pross. inters. bordo
	double		side_dist_y;		// Dist_Y pos. attuale/pross. inters. bordo
	double		d_dist_x;			// Dist_X tra i bordi di due c. contigue
	double		d_dist_y;			// Dist_Y tra i bordi di due c. contigue
	double		p_wall_dist;		// Dist. perp. dal player al muro colpito
	double		tex_pos;			// Posizione della texture sul muro
	double		wall_x;				// Coordinata (double) dove "ray hits wall"
	int			x_cell;				// Coordinata X della cella attraversata
	int			y_cell;				// Coordinata Y della cella attraversata
	int			step_x;				// Dir. in cui il raggio deve spostarsi (X)
	int			step_y;				// Dir. in cui il raggio deve spostarsi (Y)
	int			hit;				// hit wall --> cella piena == 1
	int			side;				// Lato verticale (0), lato orizzontale (1)
	int			line_height;		// Altezza della linea da disegnare
	int			draw_start;			// Inizio della linea da disegnare
	int			draw_end;			// Fine della linea da disegnare
	int			tex_num;			// Numero della texture del muro colpito
	int			tex_x;				// Coordinata X della texture da applicare
	int			tex_y;				// Coordinata Y della texture da applicare
};

typedef struct s_ray	t_ray;

struct	s_game
{
	t_image		texture;			// Struct dell'immagine per la texture		
	t_player	*player;			// Puntatore alla struttura del giocatore
	void		*mlx;				// Puntatore alla connessione MiniLibX
	void		*win;				// Puntatore alla finestra di gioco
	int			**wall;				// Array delle texture dei muri
	int			size;				// Dimensione della mappa
	int			x;					// Coordinata X 
	int			y;					// Coordinata Y 
	int			pl_pos_cnt;			// Flag per il giocatore
	int			info;				// Flag
	int			key_a;				// Flag per il tasto A (sinistra)
	int			key_w;				// Flag per il tasto W (avanti)
	int			key_s;				// Flag per il tasto S (indietro)
	int			key_d;				// Flag per il tasto D (destra)
	int			key_right;			// Flag per la rotazione a destra
	int			key_left;			// Flag per la rotazione a sinistra
	int			floor;				// Colore del pavimento
	int			ceiling;			// Colore del soffitto
	char		**cub;				// Rappr. del file della mappa (.cub)
	char		**map;				// Mappa del gioco (matrice di caratteri)
	char		*no;				// Path della texture per il lato Nord
	char		*so;				// Path della texture per il lato Sud
	char		*ea;				// Path della texture per il lato Est
	char		*we;				// Path della texture per il lato Ovest
};

typedef struct s_game	t_game;

/* ----------------------------------- WIN ---------------------------------- */

int				close_win_free(t_game *game);
int				keydown_hook(int keycode, t_game *game);
int				keyup_hook(int keycode, t_game *game);

/* ----------------------------------- MAP ---------------------------------- */

int				check_map_contents(t_game *game);
char			*read_map_lines(t_game *game, int fd);
bool			check_map_wall(t_game *game);
void			read_map_cells(t_game *game, char *filename);
void			read_map_visual_data(t_game *game, char **line, int *i);
void			render_texture_to_img(t_game *game);
void			map_background(t_game *game, char *line, int info);

/* ---------------------------------- INIT ---------------------------------- */

void			initialize_data(t_game *game);
void			initialize_game_env(t_game *game);
void			initialize_map(t_game *game, int fd);
void			initialize_dda(t_game *game, t_ray *ray);

/* --------------------------------- RENDER --------------------------------- */

void			run_dda(t_game *game, t_ray *ray);
void			raycasting_setup(t_game *game, t_ray *ray, int x);
void			pixel_line_draw_setup(t_game *game, t_ray *ray, int x);

/* --------------------------------- PLAYER --------------------------------- */

void			player_actions(t_game *game);

/* ---------------------------------- UTILS --------------------------------- */

int				ft_strcmp(const char *s1, const char *s2);
int				ft_isspace(int c);
int				skip_spaces(char *line);
unsigned int	control_brightness(unsigned int color, int factor);
char			*check_strjoin(t_game *game, char *tmp, char *line, int fd);

/* ------------------------------ FREE & ERRORS ----------------------------- */

void			write_error_n_exit(int er, char *msg, char *str, t_game *game);
void			free_strings(char *s1, char *s2);
void			free_array(char **str);
void			free_cube(t_game *game);
void			free_malloc(t_game *game);

#endif //CUB3D_H
