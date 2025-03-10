/* Athul Anoop
 * Roll no: 25
 * Description: C program to fork a new process and load a custom binary into
 * the child process
 */

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

float *parseInput(int count, char **input);
float *calcMean(float *input);
float *calcMedian(float *input);
float *calcSd(float *input);
float *sorted(float *input);

int inputSize = 0;
float *mean;
float *median;
float *sd;
pthread_t threads[3];

int main(int argc, char *argv[]) {
  float *input = parseInput(argc, argv);
  pthread_create(threads + 0, NULL, (void *)(calcMean), (void *)input);
  pthread_join(threads[0], (void *)&mean);
  pthread_create(threads + 1, NULL, (void *)(calcMedian), (void *)input);
  pthread_create(threads + 2, NULL, (void *)(calcSd), (void *)input);
  pthread_join(threads[1], (void *)&median);
  pthread_join(threads[2], (void *)&sd);

  printf("\nMean: %f\nMedian: %f\nStandard Deviation: %f\n", *mean, *median,
         *sd);
  return 0;
}

float *sorted(float *input) {
  // copy array
  float *result = calloc(inputSize, sizeof(float));
  for (int i = 0; i < inputSize; i++) {
    result[i] = input[i];
  }

  // sort
  for (int i = 0; i < inputSize; i++) {
    for (int j = 0; j < inputSize - i - 1; j++) {
      if (result[j] > result[j + 1]) {
        float tmp = result[j];
        result[j] = result[j + 1];
        result[j + 1] = tmp;
      };
    }
  }

  return result;
}

float *parseInput(int count, char **input) {
  float *parsedInput = calloc(count - 1, sizeof(float));
  for (int i = 0; i < count - 1; i++) {
    parsedInput[i] = atof(input[i + 1]);
  }
  inputSize = count - 1;
  return parsedInput;
}

float *calcMean(float *input) {
  float *mean = calloc(1, sizeof(float));
  for (int i = 0; i < inputSize; i++) {
    *mean += input[i];
  }
  *mean /= inputSize;
  return mean;
}

float *calcMedian(float *input) {
  float *median = calloc(1, sizeof(float));
  float *sortedInput = sorted(input);
  int middle = inputSize / 2;
  if (inputSize % 2 == 0) {
    *median = (sortedInput[middle] + sortedInput[middle - 1]) / 2;
  } else {
    *median = sortedInput[middle];
  }
  return median;
}

float *calcSd(float *input) {
  float *sd = calloc(1, sizeof(float));
  for (int i = 0; i < inputSize; i++) {
    *sd += pow(input[i] - *mean, 2);
  }
  *sd /= inputSize - 1;
  *sd = pow(*sd, 0.5);
  return sd;
}
