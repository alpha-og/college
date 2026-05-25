#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct DistanceVectorEntry {
  int destination;
  int distance;
  int next_hop;
};

void display_graph(int *graph, int node_count);
void display_distance_vector(struct DistanceVectorEntry *distance_vector,
                             int node_count, int node_id);

int main() {
  /* srand(time(NULL)); */
  int node_count;
  printf("Nodes: ");
  scanf("%d", &node_count);

  // initialize graph with random weights as an adjacency matrix
  int *graph = (int *)(calloc(node_count * node_count, sizeof(int)));
  for (int i = 0; i < node_count; i++) {
    for (int j = 0; j < node_count; j++) {
      int distance = i == j ? 0 : rand() % 100 < 30 ? INT_MAX : rand() % 10 + 1;
      *(graph + node_count * i + j) = distance;
    }
  }

  display_graph(graph, node_count);

  // initialize distance vectors for each node
  struct DistanceVectorEntry **distance_vectors =
      (struct DistanceVectorEntry **)(calloc(
          node_count, sizeof(struct DistanceVectorEntry *)));
  for (int i = 0; i < node_count; i++) {
    struct DistanceVectorEntry *distance_vector =
        (struct DistanceVectorEntry *)calloc(
            node_count, sizeof(struct DistanceVectorEntry));
    *(distance_vectors + i) = distance_vector;
  }
  for (int i = 0; i < node_count; i++) {
    struct DistanceVectorEntry *distance_vector = *(distance_vectors + i);
    for (int j = 0; j < node_count; j++) {
      struct DistanceVectorEntry *distance_vector_entry = (distance_vector + j);
      int distance = *(graph + node_count * i + j);
      distance_vector_entry->distance = distance;
      distance_vector_entry->destination = j;
      distance_vector_entry->next_hop = i == j                ? i
                                        : distance == INT_MAX ? -1
                                                              : j;
    }
  }

  int updated = 1;

  while (updated) {
    updated = 0;

    for (int i = 0; i < node_count; i++) {
      struct DistanceVectorEntry *distance_vector = *(distance_vectors + i);
      for (int j = 0; j < node_count; j++) {
        struct DistanceVectorEntry *distance_vector_entry =
            (distance_vector + j);
        for (int k = 0; k < node_count; k++) {

          int cost_i_k = *(graph + node_count * i + k);
          int cost_k_j = (*(distance_vectors + k) + j)->distance;

          if (cost_i_k == INT_MAX || cost_k_j == INT_MAX)
            continue;
          int new_distance = cost_i_k + cost_k_j;
          if (new_distance < distance_vector_entry->distance) {
            distance_vector_entry->distance = new_distance;
            distance_vector_entry->destination = j;
            distance_vector_entry->next_hop = k;
            updated = 1;
          }
        }
      }
    }
  }

  for (int i = 0; i < node_count; i++) {
    display_distance_vector(*(distance_vectors + i), node_count, i);
  }

  free(graph);
  for (int i = 0; i < node_count; i++) {
    free(*(distance_vectors + i));
  }
  free(distance_vectors);

  return EXIT_SUCCESS;
}

void display_graph(int *graph, int node_count) {
  // display adjacency matrix of a graph
  for (int i = 0; i < node_count; i++) {
    printf("\t%d", i);
  }
  printf("\n");
  for (int i = 0; i < node_count; i++) {
    printf("%d", i);
    for (int j = 0; j < node_count; j++) {
      int distance = *(graph + node_count * i + j);
      if (distance == INT_MAX) {
        printf("\tINF");
      } else {
        printf("\t%d", distance);
      }
    }
    printf("\n");
  }
}
void display_distance_vector(struct DistanceVectorEntry *distance_vector,
                             int node_count, int node_id) {
  printf("\nDistance Vector for Node %d\n", node_id);
  printf("Destination\tDistance\tNext Hop\n");
  for (int i = 0; i < node_count; i++) {
    struct DistanceVectorEntry *entry = distance_vector + i;
    if (entry->distance == INT_MAX) {
      printf("%d\t\tINF\t\t%d\n", entry->destination, entry->next_hop);
    } else {
      printf("%d\t\t%d\t\t%d\n", entry->destination, entry->distance,
             entry->next_hop);
    }
  }
}
