#include "popularpath.h"

// This function inserts new element to path structure
void push_vertex(path* target, int v){
	if (target != NULL) {
		path *temp = target;
		
		while (temp->next != NULL) {
			temp = temp->next;
		}
		
		path *last = malloc(sizeof(path));
		last->next = NULL;
		last->vertex = v;
		temp->next = last;
		last->prev = temp;
	}
}

// This function removes last element from given path structure
void pop_vertex(path* target){
	if (target != NULL) {
		path *temp = target;
		
		while (temp->next != NULL) {
			temp = temp->next;
		}

		if (temp->prev != NULL) {
			temp = temp->prev;
			path *pop = temp->next;
			free(pop);
			temp->next = NULL;
		} else {
			temp->vertex = -1;
		}
		
	}
}

// find_vertex function says you that the vertex member of path
int find_vertex(path* target, int vertex) {
	path *temp = target;
	int result = 0;
	while (temp->next != NULL) {
		temp = temp->next;
		if (temp->vertex == vertex) {
			result = 1;
		}
	}
	
	return result;
}

// It creates new path
path* create_path () {
	path *init = malloc(sizeof(path));
	init->prev = NULL;
	init->next = NULL;
	init->vertex = -1;
	return init;
}

// It prints all elements of path
void display_vertexes(path* target) {
	if (target == NULL) return;
	target = target->next;
	if (target != NULL) {
		path * temp = target;
		
		while (temp != NULL) {
			printf("%d ", temp->vertex + 1);
			
			if (temp->next != NULL) {
				temp = temp->next;
			} else {
				break;
			}
		}
	}
}

// Calculates lenght of path
int count_vertexes(path* target) {
	target = target->next;
	if (target != NULL) {
		path *temp = target;
		int count = 0;
		while (temp != NULL) {
			count++;
			
			if (temp->next != NULL) {
				temp = temp->next;
			} else {
				break;
			}
		}
		return count;
	} else {
		return 0;
	}
}

// It creates new path and then it clones data from source path as given parameter
path* duplicate_path(path* source) {
	if (source != NULL) {
		path *clone = create_path();
		if (source->next != NULL) {
			while (source->next != NULL) {
				source = source->next;
				push_vertex(clone, source->vertex);
			}
		}
		return clone;
	} else {
		return NULL;
	}
}

// This function inserts new element to all_paths structure
void push_path(all_paths* head, path* last) {
	if (head != NULL) {
		all_paths *temp = head;
		
		while (temp->next != NULL) {
			temp = temp->next;
		}
		
		all_paths *last_all = malloc(sizeof(all_paths));
		last_all->next = NULL;
		last_all->x = last;
		last_all->repeat = 0;
		temp->next = last_all;
		last_all->prev = temp;
	}
}

// This function removes last element from given all_paths structure
void pop_path(all_paths* head){
	if (head != NULL) {
		all_paths *temp = head;
		
		while (temp->next != NULL) {
			temp = temp->next;
		}

		if (temp->prev != NULL) {
			temp = temp->prev;
			all_paths *pop = temp->next;
			free(pop);
			temp->next = NULL;
		} else {
			temp->x = NULL;
		}
		
	}
}

// It creates new all_paths structure
all_paths* create_all_paths () {
	all_paths *init = malloc(sizeof(all_paths));
	init->prev = NULL;
	init->next = NULL;
	init->x = NULL;
	init->repeat = 0;
	return init;
}

// It prints all elements of all_paths
void display_paths(all_paths* target) {
	if (target == NULL) {
		return;
	}
	target = target->next;
	if (target != NULL) {
		all_paths *temp = target;
		
		while (temp != NULL) {
			display_vertexes(temp->x);
			printf("\n");
			
			if (temp->next != NULL) {
				temp = temp->next;
			} else {
				break;
			}
		}
	}
}

// Calculates lenght of all_paths
int count_paths(all_paths* target) {
	if (target == NULL) {
		return (int) NULL;
	}
	target = target->next;
	if (target != NULL) {
		all_paths *temp = target;
		int count = 0;
		while (temp != NULL) {
			count++;
			
			if (temp->next != NULL) {
				temp = temp->next;
			} else {
				break;
			}
		}
		return count;
	} else {
		return 0;
	}
}
