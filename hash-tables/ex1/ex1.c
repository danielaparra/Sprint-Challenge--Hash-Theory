#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "ex1.h"

Answer *get_indices_of_item_weights(int *weights, int length, int limit)
{
  // Create hash table to store weights and their indices.
  HashTable *ht = create_hash_table(16);

  // Iternate through weights array to add weights and their indices to the hash table.
  for (int i = 0; i < length; i ++) {
    hash_table_insert(ht, weights[i], i);
  }

  // Iterate through weights array to find 2 weights that sum up to given limit.
  for (int i = 0; i < length; i ++) {
    // Grab index of key for limit minus weight at index i.
    int index = hash_table_retrieve(ht, limit - weights[i]);
    // Check that value exists in hash table by checking its index (shouldn't equal -1).
    if (index != -1) {
      // Create answer struct.
      Answer *answer = malloc(sizeof(Answer));
      // Find out which weight is greater and make index 1 the greater weight's index.
      if (weights[i] > (limit - weights[i])) {
        answer->index_1 = i;
        answer->index_2 = index;
      } else {
        answer->index_1 = index;
        answer->index_2 = i;
      }
      // Destroy hash table to avoid memory leaks.
      destroy_hash_table(ht);
      // Return answer with indices for 2 weights.
      return answer;
    }
  }  
  // Destroy hash table to avoid memory leaks.
  destroy_hash_table(ht);
  // If couldn't find 2 weights that sum up to limit, return NULL.
  return NULL;
}

void print_answer(Answer *answer)
{
  if (answer != NULL) {
    printf("%d %d\n", answer->index_1, answer->index_2);
  } else {
    printf("NULL\n");
  }
}

#ifndef TESTING
int main(void)
{

  // TEST 1
  int weights_1 = {9};
  Answer *answer_1 = get_indices_of_item_weights(&weights_1, 1, 9);
  print_answer(answer_1);  // NULL

  // TEST 2
  int weights_2[] = {4, 4};
  Answer* answer_2 = get_indices_of_item_weights(weights_2, 2, 8);
  print_answer(answer_2);  // {1, 0}

  // TEST 3
  int weights_3[] = {4, 6, 10, 15, 16};
  Answer* answer_3 = get_indices_of_item_weights(weights_3, 5, 21);
  print_answer(answer_3);  // {3, 1}

  // TEST 4
  int weights_4[] = {12, 6, 7, 14, 19, 3, 0, 25, 40};
  Answer* answer_4 = get_indices_of_item_weights(weights_4, 9, 7);
  print_answer(answer_4);  // {6, 2}

  return 0;
}
#endif
