#ifndef LOG_H
#define LOG_H

#define FILENAME_SIZE 64

typedef struct log_data_s *log_data_t;
typedef struct log_s {
	log_data_t data;
	int (*create) (char *prefix);
	int (*destroy) (void);
	int (*print) (void);
} log_t;

log_t *get_log(void);

#endif /* LOG_H */
