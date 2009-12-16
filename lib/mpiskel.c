#include <stdlib.h>
#include <assert.h>

#include <config.h>
#include <mpiskel.h>

#include <argp.h>

static const char * string = PACKAGE_STRING;
static const char * report = PACKAGE_BUGREPORT;

static const char description[] = 
  "mpiskel -- a framework for MPI applications using callbacks";

static struct argp_option options[] = 
  {
    {"verbose", 'v', NULL, 0, "Produce verbose output" },
    {"output", 'o', "FILE", 0,
     "Output to FILE instead of standard output" },
    { NULL }
  };

struct arguments
{
  char * args[2];
  int verbose;
  char * file;
};

static error_t parse_opt(int key, char * arg, struct argp_state * state)
{
  struct arguments * arguments = state->input;
  
  switch (key)
    {
    case 'v':
      arguments->verbose++;
      break;
    case 'o':
      arguments->file = arg;
      break;
    case ARGP_KEY_END:
      if (state->arg_num > 0)
	argp_usage(state);
      break;
      
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static struct argp argp = { options, parse_opt, NULL, description };

int main(int argc, char * argv[]) 
{
  struct arguments arguments;
  
  /* argp handler? */
  arguments.verbose = 0;
  arguments.file = "-";
  
  argp_parse(&argp, argc, argv,  0, NULL, &arguments);

  /* signal handler? */

  /* mpi initialization? */
  
  return 0;
}

typedef struct pipeline_s {
} pipeline_t;

typedef void * (* fn_t) (void * args);

typedef struct stage_s {
  fn_t fn;
  int options;
} stage_t;

static void setup_signal_handler(void) {
  
  return;
}

static void setup_argp(void) {
  
  return;
}

static void setup_mpi(void) {
  
  return;
}

static void setup_driver(void) {
  
  return;
}

static stage_t * stage_create(fn_t fn, int options) {
  
  stage_t * stage = NULL;

  assert(fn != NULL);
  assert(options > 0);

  stage = calloc(1, sizeof(stage_t));
  
  stage->fn = fn;
  stage->options = options;

  return stage;
}

static int stage_destroy(stage_t * stage, int options) {
  
  int result;
  
  assert(stage != NULL);
  assert(options >= 0);
  
  free(stage);
  stage = NULL;
  
  return result;
}

static int stage_execute(stage_t * stage, int options) {
  
  int result = 1;

  assert(stage != NULL);
  assert(options >= 0);

  return result;
}

static void stage_show(stage_t * stage) {

  assert(stage != NULL);

  return;
}

static pipeline_t * pipeline_create(stage_t ** stages, int count, int options) {
  
  pipeline_t * pipeline = NULL;
  int i = 0;
  
  assert(stages != NULL);
  assert(count > 0);
  assert(options >= 0);

  pipeline = calloc(1, sizeof(pipeline_t));
  
  return pipeline;
}

static int pipeline_destroy(pipeline_t * pipeline, int options) {
  
  int result = -1;
  
  assert(pipeline != NULL);
  assert(options >= 0);

  return result;
}

static int pipeline_start(pipeline_t * pipeline, int options) {
  
  int result = -1;
  
  assert(pipeline != NULL);
  assert(options >= 0);

  return result;
}

static int pipeline_stop(pipeline_t * pipeline, int options) {
  
  int result = -1;
  
  assert(pipeline != NULL);
  assert(options >= 0);

  return result;
}

extern int debug;

#define printd(fmt, args...) do { if (debug) { printf("%s:%d:%s() ", __FILE__, __LINE__, __FUNCTION__); printf(fmt, ## args); } } while (0)

static void pipeline_show(pipeline_t * pipeline, int options) {

  printd("%p, %d", pipeline, options);
  
  assert(pipeline != NULL);
  assert(options >= 0);
  
  return;
}

extern int verbosity;

#define printv(level, fmt, args...) do { if (verbosity >= level) { printf(fmt, ## args); } } while (0)

#include <sys/time.h>
#include <time.h>

static int timestamp(char * buffer, int size) {
  
  int result = -1;
  
  assert(buffer != NULL);
  assert(size >= 0);

  struct timeval tv;
  time_t time;

  gettimeofday(&tv, NULL);
  time = tv.tv_sec;
  
  strftime(buffer, size, "%m%d%y", localtime(&time));

  return result;
}

typedef struct log_s {
} log_t;

static log_t * log_create(int options) {
  
  log_t * log = NULL;
  
  assert(options >= 0);

  return log;
}

static int log_close(log_t * log) {

  int result = -1;

  assert(log != NULL);

  return result;
}

typedef struct mpi_s {
  int rank;
  int count;
  int name;
} mpi_t;

static mpi_t * mpi_init(int options) {
  
  mpi_t * mpi = NULL;
  
  assert(options >= 0);
  
  return mpi;
}

static int mpi_finalize(mpi_t * mpi, int options) {
  
  int result = -1;
  
  assert(mpi != NULL);
  assert(options >= 0);
  
  return result;
}
