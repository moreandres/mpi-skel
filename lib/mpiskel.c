#include <stdlib.h>
#include <assert.h>

#include <config.h>
#include <mpiskel.h>

#include <argp.h>

const char * string = PACKAGE_STRING;
const char * report = PACKAGE_BUGREPORT;

const char description[] = 
  "mpiskel -- a framework for MPI applications using callbacks";

static struct argp_option options[] = 
  {
    {"verbose",  'v', 0,      0,  "Produce verbose output" },
    {"output",   'o', "FILE", 0,
     "Output to FILE instead of standard output" },
    { 0 }
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
  arguments.file = '-';
  
  argp_parse(&argp, argc, argv,  0, 0, &arguments);

  /* signal handler? */

  /* mpi initialization? */
  
  return 0;
}

struct mpiskel * mpiskel_alloc(int length, 
			       const struct mpiskel_ops * ops)
{
  struct mpiskel * skel = NULL;
  
  /* ensure function parameters are OK */
  
  assert(length > 0);
  assert(ops != NULL);
  
  return skel;
}
