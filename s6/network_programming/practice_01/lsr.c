#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct RoutingTableEntry {
  int destination;
  int cost;
  int next_hop;
};

void display_graph(int *graph, int node_count);
void display_routing_table(struct RoutingTableEntry *routing_table,
                           int node_count, int node_id);

int main() {
  int node_count = 0;
  printf("Nodes: ");
  scanf("%d", &node_count);

  // initialize graph
  int *graph = (int *)calloc(node_count * node_count, sizeof(int));
  for (int i = 0; i < node_count; i++) {
    for (int j = 0; j < node_count; j++) {
      *(graph + node_count * i + j) = i == j              ? 0
                                      : rand() % 100 < 30 ? INT_MAX
                                                          : rand() % 10 + 1;
    }
  }

  display_graph(graph, node_count);

  // initialize routing table for each node/ router
  struct RoutingTableEntry **routing_tables =
      (struct RoutingTableEntry **)calloc(node_count,
                                          sizeof(struct RoutingTableEntry *));
  for (int i = 0; i < node_count; i++) {
    struct RoutingTableEntry *routing_table =
        (struct RoutingTableEntry *)calloc(node_count,
                                           sizeof(struct RoutingTableEntry));
    *(routing_tables + i) = routing_table;
  }

  for (int i = 0; i < node_count; i++) {
    struct RoutingTableEntry *routing_table = *(routing_tables + i);
    for (int j = 0; j < node_count; j++) {
      struct RoutingTableEntry *entry = routing_table + j;
      entry->cost = i == j ? 0 : INT_MAX;
      entry->destination = j;
      entry->next_hop = entry->cost == INT_MAX ? -1 : j;
    }
  }

  int *visited = (int *)calloc(node_count, sizeof(int));
  for (int i = 0; i < node_count; i++) {
    memset(visited, 0, node_count * sizeof(int));
    struct RoutingTableEntry *routing_table = *(routing_tables + i);

    // dijkstras
    for (int j = 0; j < node_count; j++) {
      int min_cost = INT_MAX;
      int min_node = -1;
      for (int k = 0; k < node_count; k++) {
        if (!visited[k] && (routing_table + k)->cost < min_cost) {
          min_cost = (routing_table + k)->cost;
          min_node = k;
        }
      }

      if (min_node == -1 || min_cost == INT_MAX)
        break;

      visited[min_node] = 1;

      for (int k = 0; k < node_count; k++) {
        if (visited[k])
          continue;
        int cost_min_node_k = *(graph + node_count * min_node + k);
        if (cost_min_node_k == INT_MAX)
          continue;
        int new_cost = min_cost + cost_min_node_k;
        struct RoutingTableEntry *entry = routing_table + k;
        if (new_cost < entry->cost) {
          entry->cost = new_cost;
          entry->destination = k;
          if (min_node == i) {
            entry->next_hop = k;
          } else {
            entry->next_hop = (routing_table + min_node)->next_hop;
          }
        }
      }
    }
  }
  for (int i = 0; i < node_count; i++) {
    display_routing_table(*(routing_tables + i), node_count, i);
  }

  free(visited);
  free(graph);
  for (int i = 0; i < node_count; i++) {
    free(*(routing_tables + i));
  }
  free(routing_tables);

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
void display_routing_table(struct RoutingTableEntry *routing_table,
                           int node_count, int node_id) {
  printf("\nRouting Table for Node %d\n", node_id);
  printf("Destination\tDistance\tNext Hop\n");
  for (int i = 0; i < node_count; i++) {
    struct RoutingTableEntry *entry = routing_table + i;
    if (entry->cost == INT_MAX) {
      printf("%d\t\tINF\t\t%d\n", entry->destination, entry->next_hop);
    } else {
      printf("%d\t\t%d\t\t%d\n", entry->destination, entry->cost,
             entry->next_hop);
    }
  }
}
