#include <stdio.h>
#include <stdlib.h>

int majority(int *vector, int length);
int majorityR(int *vector, int l, int r);

int main() {
    int *vector;                                                            // the vector
    int i;                                                                  // the index
    int major;                                                              // the majority element
    int length;                                                             // the length of the vector

    fprintf(stdout, "Insert the length of the vector: ");
    fscanf(stdin, "%d", &length);
    vector = (int *) malloc(length * sizeof(int));
    for(i = 0; i < length; i++) {                                           // cycle on the vector
        fprintf(stdout, "Insert the %d element of the vector: ", i + 1);
        fscanf(stdin, "%d", &vector[i]);
    }
    major = majority(vector, length);
    if(major == -1) {                                                       // if that checks if the majority exists
        fprintf(stdout, "The majority element doesn't exists");
    } else {
        fprintf(stdout, "The majority element is: %d", major);
    }
    return 0;
}

int majority(int *vector, int length) {
    int l, r;                                   // the index of the extreme of the vector

    l = 0;
    r = length - 1;
    return majorityR(vector, l, r);
}
int majorityR(int *vector, int l, int r) {
    int q;                                                                              // the index of middle element of the vector
    int firstMajority;                                                                  // the majority of the first subvector
    int secondMajority;                                                                 // the majority of the second subvector
    int counterfirstMajority;                                                           // the counter of the majority of the first subvector
    int countersecondMajority;                                                          // the counter of the majority of the second subvector

    if(r <= l) {                                                                        // if that checks if the right extreme is less or equal to the left extreme
        return vector[r];
    }
    q = (l + r) / 2;
    firstMajority = majorityR(vector, l, q);
    secondMajority = majorityR(vector, q + 1, r);
    for(q = l, counterfirstMajority = countersecondMajority = 0; q <= r; q++) {         // cycle on the vector
        if(vector[q] == firstMajority) {                                                // if that checks if the element of the vector is equal to the first majority
            counterfirstMajority++;
        } else if(vector[q] == secondMajority) {                                        // if that checks if the element of the vector is equal to the second majority
            countersecondMajority++;
        }
    }
    if (counterfirstMajority > (r - l + 1) / 2) {                                       // if that checks if the first majority is an effective majority
        return firstMajority;
    }
    if (countersecondMajority > (r - l + 1) / 2) {                                      // if that checks if the second majority is an effective majority
        return secondMajority;
    }
    return -1;
}