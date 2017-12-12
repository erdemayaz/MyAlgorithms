#include "popularpath.h"

/*
 * Developed by Erdem AYAZ
 * It was created on December 12th 2017.
 * 
 * Most popular path algorithm on directed graph.
 *
*/


// traverse function is a recursive function that it calls for every new parting of the ways
void traverse(int* matrix, int row, path* set, all_paths* paths, pthread_mutex_t* mutex, int number) {
	int index = row * number;
	int i = index;
	int last = index + number;
	path *duplicate = duplicate_path(set);
	push_vertex(duplicate, row);
	int control = 0;
	for (index; index < last; index++) {
		if (*(matrix + index) == 1) {
			control = 1;
			int found = find_vertex(duplicate, index - i);
			
			if (found == 0) {
				traverse(matrix, index - i, duplicate, paths, mutex, number);
			} else if (found == 1) {
				path *pushing = duplicate_path(duplicate);
				push_vertex(pushing, index - i);
				pthread_mutex_lock(mutex);
				push_path(paths, pushing);
				pthread_mutex_unlock(mutex);
			}
		}
	}
	
	if (control == 0) {
		pthread_mutex_lock(mutex);
		push_path(paths, duplicate);
		pthread_mutex_unlock(mutex);
	}
}

// This function runs as thread. It prepares to graph for recursively call
void* find_paths(void* b) {
	thread_bundle *bundle = (thread_bundle*) b;
	int vertex = bundle->vertex;
	int *matrix = bundle->matrix;
	int number = bundle->number;
	all_paths *paths = bundle->all;
	path *set = create_path();
	traverse(matrix, vertex, set, paths, bundle->mutex, number);
}

// walk function is general function which it splits up data for every thread
void walk (int* graph_matrix, int number, all_paths* paths) {
	if ((number < 0) || (graph_matrix == NULL) || (paths == NULL)) return;
	pthread_t thread[number];
	thread_bundle bundle[number];
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	int i = 0;
	for (i; i < number; i++) {
		bundle[i].vertex = i;
		bundle[i].matrix = graph_matrix;
		bundle[i].all = paths;
		bundle[i].mutex = &mutex;
		bundle[i].number = number;
		pthread_create(&thread[i], NULL, find_paths, (void*)&bundle[i]);
	}
	
	for(i = 0; i < number; i++) {
		pthread_join(thread[i], NULL);
	}
}

/* 
 * This function generates n-level set as integer.
 * Ex (1, 2, 3), (1, 2, 4), (1, 3, 2), (1, 3, 4), ...
*/
all_paths* full_set(int edge_number, int level) {
	if ((level < 1) || (level > edge_number)) {
		return NULL;
	}
	
	all_paths *result = create_all_paths();
	int counter[level];
	int last = level - 1;
	int count = 0, control = 1;
	int i = 0, j = 0;
	for (i; i < level; i++) {
		counter[i] = 0;
	}
	
	while (counter[0] < edge_number) {
		counter[last]++;
		control = 1;
		i = 0;
		while (last - i > 0) {
			if (counter[last - i] == edge_number) {
				counter[last - i] = 0;
				counter[last - i - 1]++;
			}
			i++;
		}
		
		if (counter[0] >= edge_number) {
			break;
		}
		
		if (level > 1) {
			i = 1;
			while (i < level) {
				for(j = 0; j < i; j++) {
					if (counter[j] == counter[i]){
						control = 0;
						break;
					}
				}
				i++;
			}
			
			if (control == 1) {
				path *itemset = create_path();
				i = 0;
				while (i < level) {
					push_vertex(itemset, counter[i]);
					i++;
				}
				
				push_path(result, itemset);
			}
		} else {
			path *itemset = create_path();
			push_vertex(itemset, counter[0]);
			push_path(result, itemset);
		}
	}
	
	return result;
}

// is_subset function is a control function. It control that is 'subset' subset of 'set'?
int is_subset(path* set, path* subset) {
	if (set == NULL || subset == NULL) {
		return (int)NULL;
	} else {
		if (set->next == NULL || subset->next == NULL) {
			return (int)NULL;
		} else {
			set = set->next;
			subset = subset->next;
		}
	}
	
	int i, control = 0;
	int count_set = count_vertexes(set) + 1;
	int count_subset = count_vertexes(subset) + 1;
	if (count_subset > count_set) {
		return (int)NULL;
	}
	
	for (i = 0; i < count_set - count_subset + 1; i++){
		if (set->vertex == subset->vertex) {
			control = 1;
			break;
		}
		set = set->next;
	}
	
	if (control == 0) {
		return 0;
	} else {
		set = set->next;
		subset = subset->next;
		
		while (subset != NULL) {
			if (set->vertex != subset->vertex) {
				control = 0;
				break;
			}
			
			if (subset->next == NULL) {
				break;
			} else {
				set = set->next;
				subset = subset->next;
			}
		}
		
		if (control == 0) {
			return 0;
		} else {
			return 1;
		}
	}
}

// evaluate_repeat is thread function. It evaluates repeats.
void* evaluate_repeat(void* bund) {
	bundle *b = (bundle*) bund;
	int index = b->index;
	int group = b->group_count;
	all_paths *target = b->all;
	all_paths *closed = b->full_set;
	pthread_mutex_t *mutex = b->mutex;
	target = target->next;
	closed = closed->next;
	path *temp_closed;
	all_paths *temp_target;
	int temp_repeat;

	int i = 0;
	for (i = 0; i < index; i++) {
		closed = closed->next;
	}

	for (i = 0; i < group; i++) {
		temp_closed = closed->x;
		temp_target = target;
		temp_repeat = closed->repeat;
		while (temp_target != NULL) {
			if (is_subset(temp_target->x, temp_closed) == 1) {
				temp_repeat++;
			}
			
			if (temp_target->next != NULL) {
				temp_target = temp_target->next;
			} else {
				break;
			}
		}
		closed->repeat = temp_repeat;
		if (closed->next != NULL) {
			closed = closed->next;
		} else {
			break;
		}
	}

}

// This function calculate how many times
void popular_path_calculate(all_paths* paths, all_paths *full) {
	if (paths == NULL || full == NULL) {
		return;
	}
	
	int thread_num = 8;
	int itemset_count = count_paths(full);
	int group_count = (itemset_count / thread_num);
	int indexes[8];
	int i = 0, index = 0;
	for (i; i < thread_num; i++) {
		indexes[i] = index;
		index = index + group_count;
	}
	
	pthread_t thread[8];
	bundle b[8];
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	for (i = 0; i < thread_num; i++) {
		b[i].index = indexes[i];
		b[i].all = paths;
		b[i].full_set = full;
		if (i == thread_num - 1) {
			b[i].group_count = itemset_count - (group_count * (thread_num - 1));
		} else {
			b[i].group_count = group_count;
		}
		b[i].mutex = &mutex;
		pthread_create(&thread[i], NULL, evaluate_repeat, (void*)&b[i]);
	}
	
	for(i = 0; i < thread_num; i++) {
		pthread_join(thread[i], NULL);
	}
}

// This function displays repeats for all subset
void display_repeats(all_paths* target) {
	if (target != NULL) {
		int res = 0;
		target = target->next;
		while (target != NULL) {
			printf("%d --> ", target->repeat);
			display_vertexes(target->x);
			printf("\n");
			res = res + target->repeat;
			target = target->next;
			if (target == NULL) break;
		}
	}
}

// It gives most popular path as path structure
path* popular_path(all_paths* all) {
	if (all == NULL) return (path*)NULL;
	all_paths *temp = all;
	temp = temp->next;
	int max = 0;
	path *result = NULL;
	
	while (temp != NULL) {
		
		if (temp->repeat > max) {
			max = temp->repeat;
			result = temp->x;
		}
		
		temp = temp->next;
		if(temp == NULL) break;
	}
	
	return result;
}

// It gives most popular path as repeat of path
int popular_path_count(all_paths* all) {
	if (all == NULL) return (int) NULL;
	all_paths *temp = all;
	temp = temp->next;
	int max = 0;
	
	while (temp != NULL) {
		if (temp->repeat > max) {
			max = temp->repeat;
		}
		
		temp = temp->next;
		if(temp == NULL) break;
	}
	
	return max;
}

// General API for library users
all_paths* find_popular_path(int* adjacency_matrix, int vertex_number, int togetherness_count) {
	all_paths *paths = create_all_paths();
	walk(adjacency_matrix, vertex_number, paths);

	all_paths *result = (all_paths*) full_set(vertex_number, togetherness_count);
	popular_path_calculate(paths, result);
	
	return result;
}
