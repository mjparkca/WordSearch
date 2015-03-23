#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DRAWING_AREA_WIDTH 300
#define DRAWING_AREA_HEIGHT 300

struct Coord {
  int row;
  int col;
  struct Coord *next;
};

struct CoordList {
  struct Coord *data;
  struct CoordList *next;
};

struct Board {
  int width;
  int height;
  char *content;
  struct CoordList *coords;
};

static struct Board *newBoard(FILE *, FILE *);
static void deleteBoard(struct Board **);
static struct CoordList *newCoordList(FILE *);
static void deleteCoordList(struct CoordList **);

static gboolean cb_draw(GtkWidget *, cairo_t *, gpointer);
static void create_controls(struct Board *);

static struct Board *newBoard(FILE *board_input, FILE *answer)
{
  int i, m, n;
  char *buf;
  struct Board *board;

  board = (struct Board *)malloc(sizeof(struct Board));
  
  fscanf(board_input, "%d,%d", &m, &n);
  board->width = n;
  board->height = m;
  board->content = (char *)calloc(m * n + 1, sizeof(char));
  buf = (char *)malloc((n + 2) * sizeof(char));
  fgetc(board_input);
  for (i = 0; i < m; ++i)
  {
    fgets(buf, n + 2, board_input);
    strncpy(board->content + i * n, buf, n);
  }
  free(buf);

  board->coords = newCoordList(answer);

  return board;
}

static void deleteBoard(struct Board **bpp)
{
  struct Board *board;

  board = *bpp;
  free(board->content);
  deleteCoordList(&board->coords);

  free(*bpp);
  *bpp = NULL;
}

static struct CoordList *newCoordList(FILE *answer)
{
  return NULL;
}

static void deleteCoordList(struct CoordList **lpp)
{
}

static gboolean cb_draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{
  int i, j, m, n;
  double x, y, px, ux, uy;
  guint canvas_width, canvas_height;
  cairo_font_extents_t fe;
  cairo_text_extents_t te;
  struct Board *board_info;
  char letter[2];

  canvas_width = gtk_widget_get_allocated_width(widget);
  canvas_height = gtk_widget_get_allocated_height(widget);
  cairo_scale(cr, canvas_width, canvas_height);

  ux = uy = 1;
  cairo_device_to_user_distance(cr, &ux, &uy);
  px = ux > uy ? ux : uy;

  cairo_set_font_size(cr, 10 * px);
  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);

  board_info = (struct Board *)data;
  m = board_info->height;
  n = board_info->width;

  cairo_font_extents(cr, &fe);
  x = (canvas_width * px - n * fe.max_x_advance) / 2.0;
  y = (canvas_height * px - m * fe.max_x_advance) / 2.0;

  for (i = 0; i < m; ++i)
  {
    for (j = 0; j < n; ++j)
    {
      *letter = '\0';
      strncat(letter, board_info->content + i * n + j, 1);

      cairo_text_extents(cr, letter, &te);
      cairo_move_to(cr,
          x + j * fe.max_x_advance - te.x_bearing - te.width / 2,
          y + i * fe.max_x_advance - fe.descent + fe.height / 2);
      cairo_show_text(cr, letter);
    }
  }
  return FALSE;
}

static void create_controls(struct Board *board)
{
  GtkWidget *window;
  GtkWidget *box;
  GtkWidget *drawing_area;
  GtkWidget *separator;
  GtkWidget *button;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_window_set_title(GTK_WINDOW(window), "Word Search");

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_container_set_border_width(GTK_CONTAINER(box), 10);
  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_widget_show(box);

  drawing_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area, DRAWING_AREA_WIDTH,
                                            DRAWING_AREA_HEIGHT);
  g_signal_connect(G_OBJECT(drawing_area), "draw",
                   G_CALLBACK(cb_draw), board);
  gtk_box_pack_start(GTK_BOX(box), drawing_area, TRUE, TRUE, 0);
  gtk_widget_show(drawing_area);

  separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_box_pack_start(GTK_BOX(box), separator, FALSE, TRUE, 0);
  gtk_widget_show(separator);

  button = gtk_button_new_with_label("Quit");
  g_signal_connect_swapped(button, "clicked",
                           G_CALLBACK(gtk_main_quit), NULL);
  gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0);
  gtk_widget_set_can_default(button, TRUE);
  gtk_widget_grab_default(button);
  gtk_widget_show(button);

  gtk_widget_show(window);
}

int main(int argc, char *argv[])
{
  FILE *board_input, *answer_input;
  struct Board *board_info;

  if (argc < 3)
  {
    fprintf(stderr, "Usage: %s board_input answer_input\n", argv[0]);
    return EXIT_FAILURE;
  }

  board_input = fopen(argv[1], "r");
  if (!board_input)
  {
    perror("fopen");
    return EXIT_FAILURE;
  }

  answer_input = fopen(argv[2], "r");
  if (!answer_input)
  {
    perror("fopen");
    return EXIT_FAILURE;
  }
  board_info = newBoard(board_input, answer_input);

  fclose(board_input);
  fclose(answer_input);

  gtk_init(&argc, &argv);
  create_controls(board_info);
  gtk_main();

  deleteBoard(&board_info);

  return EXIT_SUCCESS;
}
