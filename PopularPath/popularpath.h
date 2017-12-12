#ifndef _popularpath_h_
#define _popularpath_h_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct path {
	int vertex;
	struct path *next;
	struct path *prev;
} path;

typedef struct all_paths {
	struct path *x;
	int repeat;
	struct all_paths *next;
	struct all_paths *prev;
} all_paths;

typedef struct thread_bundle {
	pthread_mutex_t *mutex;
	all_paths *all;
	int *matrix;
	int vertex;
	int number;
} thread_bundle;

typedef struct bundle {
	all_paths *all;
	all_paths *full_set;
	pthread_mutex_t *mutex;
	int index;
	int group_count;
} bundle;

void push_vertex (path*, int);

void pop_vertex (path*);

int find_vertex (path*, int);

path* create_path ();

void display_vertexes (path*);

int count_vertexes (path*);

path* duplicate_path (path*);

void push_path (all_paths*, path*);

void pop_path (all_paths*);

all_paths* create_all_paths ();

void display_paths (all_paths*);

int count_paths (all_paths*);

#endif
