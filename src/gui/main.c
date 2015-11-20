#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DRAWING_AREA_WIDTH 300
#define DRAWING_AREA_HEIGHT 300

struct Coord {
  int row;
  int col;
};

struct CoordPairList {
  struct Coord start;
  struct Coord end;
  struct CoordPairList *next;
};

struct Board {
  int width;
  int height;
  char *content;
  struct CoordPairList *coords;
};

static struct Board *newBoard(FILE *, FILE *);
static void deleteBoard(struct Board **);
static struct Coord readCoord(char *);
static struct CoordPairList *newCoordPairList(FILE *);
static void deleteCoordPairList(struct CoordPairList **);
static FILE *printCoordPairList(struct CoordPairList *, FILE *);

static gboolean cb_draw(GtkWidget *, cairo_t *, gpointer);
static void drawBound(cairo_t *, struct Coord, struct Coord, double, double);
static void create_controls(struct Board *);

static struct Board *newBoard(FILE *board_input, FILE *answer) {
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
  for (i = 0; i < m; ++i) {
    fgets(buf, n + 2, board_input);
    strncpy(board->content + i * n, buf, n);
  }
  free(buf);

  board->coords = newCoordPairList(answer);

  return board;
}

static void deleteBoard(struct Board **bpp) {
  struct Board *board;

  board = *bpp;
  free(board->content);
  board->content = NULL;
  deleteCoordPairList(&board->coords);

  free(*bpp);
  *bpp = NULL;
}

static struct Coord readCoord(char *left) {
  struct Coord coord;
  char *comma, *right;
  comma = strchr(left, ',');
  right = strchr(left, ')');
  *comma = *right = '\0';
  coord.row = atoi(left + 1);
  coord.col = atoi(comma + 1);
  return coord;
}

static struct CoordPairList *newCoordPairList(FILE *answer) {
  struct CoordPairList *root, *working;
  char buf[BUFSIZ] = {0};
  char *start, *end;

  root = (struct CoordPairList *)malloc(sizeof(struct CoordPairList));
  fgets(buf, BUFSIZ, answer);
  start = strchr(buf, '(');
  end = strrchr(buf, '(');
  root->start = readCoord(start);
  root->end = readCoord(end);
  root->next = NULL;
  working = root;
  fgets(buf, BUFSIZ, answer);
  while (!feof(answer)) {
    working->next = (struct CoordPairList *)malloc(sizeof(struct CoordPairList));
    start = strchr(buf, '(');
    end = strrchr(buf, '(');
    working = working->next;
    working->start = readCoord(start);
    working->end = readCoord(end);
    working->next = NULL;

    fgets(buf, BUFSIZ, answer);
  }
  return root;
}

static void deleteCoordPairList(struct CoordPairList **lpp) {
  struct CoordPairList *list;
  if (lpp == NULL || *lpp == NULL) {
    return;
  }
  list = *lpp;
  deleteCoordPairList(&list->next);
  free(*lpp);
  *lpp = NULL;
}

static FILE *printCoordPairList(struct CoordPairList *coords, FILE *stream) {
  while (coords) {
    fprintf(stream, "(%d,%d) (%d,%d)\n", coords->start.row, coords->start.col, coords->end.row, coords->end.col);
    coords = coords->next;
  }
  return stream;
}

static gboolean cb_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
  int i, j, m, n;
  double x, y, px, ux, uy;
  guint canvas_width, canvas_height;
  cairo_font_extents_t fe;
  cairo_text_extents_t te;
  struct Board *board_info;
  struct CoordPairList *coords;
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
  coords = board_info->coords;

  cairo_font_extents(cr, &fe);
  x = (canvas_width * px - n * fe.max_x_advance) / 2.0;
  y = (canvas_height * px - m * fe.max_x_advance) / 2.0;

  for (i = 0; i < m; ++i) {
    for (j = 0; j < n; ++j) {
      *letter = '\0';
      strncat(letter, board_info->content + i * n + j, 1);

      cairo_text_extents(cr, letter, &te);
      cairo_move_to(cr,
          x + j * fe.max_x_advance - te.x_bearing - te.width / 2.0,
          y + i * fe.max_x_advance);
      cairo_show_text(cr, letter);
    }
  }

  cairo_set_source_rgba(cr, 0.5, 0.0, 0.0, 0.5);
  cairo_set_line_width(cr, px);

  while (coords) {
    drawBound(cr, coords->start, coords->end, x, y);
    coords = coords->next;
  }

  return FALSE;
}

static void drawBound(cairo_t *cr, struct Coord start, struct Coord end,
                                                      double x, double y) {
  int x_disp, y_disp;
  double ux, uy, px, size;
  double ax, ay;
  double radius, angle1, angle2, c1x, c1y, c2x, c2y, dist;
  struct Coord pt1, pt2;
  cairo_font_extents_t fe;

  ux = uy = 1;
  cairo_device_to_user_distance(cr, &ux, &uy);
  px = ux > uy ? ux : uy;

  cairo_font_extents(cr, &fe);
  size = fe.max_x_advance;

  radius = 8 * px;
  angle1 = 0;
  angle2 = 2 * M_PI;

  if (start.col < end.col) {
    pt1 = start;
    pt2 = end;
  } else if (start.col == end.col) {
    if (start.row < end.row) {
      pt1 = start;
      pt2 = end;
    } else {
      pt1 = end;
      pt2 = start;
    }
  } else {
    pt1 = end;
    pt2 = start;
  }

  c1x = x + pt1.col * size;
  c1y = y + pt1.row * size - fe.ascent / 2.0;
  c2x = x + pt2.col * size;
  c2y = y + pt2.row * size - fe.ascent / 2.0;
  x_disp = pt2.col - pt1.col;
  y_disp = pt2.row - pt1.row;
  dist = radius / sqrt(2);

  if (pt1.col < pt2.col && pt1.row == pt2.row) {
    ax = c1x;
    ay = c1y + radius;
    angle1 = M_PI / 2.0;
    angle2 = 3.0 * M_PI / 2.0;
  } else if (pt1.col == pt2.col && pt1.row < pt2.row) {
    ax = c1x - radius;
    ay = c1y;
    angle1 = M_PI;
    angle2 = 2.0 * M_PI;
  } else if (pt1.col < pt2.col && pt1.row < pt2.row) {
    ax = c1x - dist;
    ay = c1y + dist;
    angle1 = 3.0 * M_PI / 4.0;
    angle2 = 7.0 * M_PI / 4.0;
  } else {
    ax = c1x + dist;
    ay = c1y + dist;
    angle1 = M_PI / 4.0;
    angle2 = 5.0 * M_PI / 4.0;
  }

  cairo_move_to(cr, ax, ay);
  cairo_arc(cr, c1x, c1y, radius, angle1, angle2);
  cairo_rel_line_to(cr, x_disp * size, y_disp * size);
  cairo_arc(cr, c2x, c2y, radius, angle2, angle1);
  cairo_rel_line_to(cr, -x_disp * size, -y_disp * size);

  cairo_stroke(cr);
}

static void create_controls(struct Board *board) {
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

int main(int argc, char *argv[]) {
  FILE *board_input, *answer_input;
  struct Board *board_info;

  if (argc < 3) {
    fprintf(stderr, "Usage: %s board_input answer_input\n", argv[0]);
    return EXIT_FAILURE;
  }

  board_input = fopen(argv[1], "r");
  if (!board_input) {
    perror("fopen");
    return EXIT_FAILURE;
  }

  answer_input = fopen(argv[2], "r");
  if (!answer_input) {
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
