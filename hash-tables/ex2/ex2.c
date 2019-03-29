#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

char **reconstruct_trip(Ticket **tickets, int length)
{
  // Create hashtable and route variables.
  HashTable *ht = create_hash_table(16);
  char **route = malloc(length * sizeof(char *));
  // Iterate through hash table to insert tickets' source and destination as key - value pairs.
  for (int i =0; i < length; i++) {
    hash_table_insert(ht, tickets[i]->source, tickets[i]->destination);
  }
  // Create starting value, current city, and index.
  char *start_value = "NONE";
  char *current_city = hash_table_retrieve(ht, start_value);
  int index = 0;

  // Traverse through hash table while current city isn't "NONE".
  while(strcmp(current_city, "NONE") != 0) {
    // Add current city to route at index index.
    route[index] = current_city;
    // Increase index by 1;
    index++;
    // Update current city to the value of the current city in the hash table.
    current_city = hash_table_retrieve(ht, current_city); 
  }
  // Add "NONE" to the end of the route;
  route[index] = "NONE";
  // Return route through all cities.
  return route;
}

void print_route(char **route, int length)
{
  for (int i = 0; i < length; i++) {
    printf("%s\n", route[i]);
  }
}



#ifndef TESTING
int main(void)
{
  // Short test
  Ticket **tickets = malloc(3 * sizeof(Ticket *));

  Ticket *ticket_1 = malloc(sizeof(Ticket));
  ticket_1->source = "NONE";
  ticket_1->destination = "PDX";
  tickets[0] = ticket_1;

  Ticket *ticket_2 = malloc(sizeof(Ticket));
  ticket_2->source = "PDX";
  ticket_2->destination = "DCA";
  tickets[1] = ticket_2;

  Ticket *ticket_3 = malloc(sizeof(Ticket));
  ticket_3->source = "DCA";
  ticket_3->destination = "NONE";
  tickets[2] = ticket_3;

  print_route(reconstruct_trip(tickets, 3), 3); // PDX, DCA, NONE

  return 0;
}
#endif
