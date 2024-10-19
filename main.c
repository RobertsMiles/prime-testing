// TODO tidy-up code; add java docs; re-impliment Node.coprimes as linked list for dynamic allocation; add user input

#include <stdio.h>
#include <stdlib.h>

#define COPRIME_ARRAY_LENGTH 8100

typedef struct Node {
    int value;
    int numberOfCoprimes;
    struct Node* next;
    struct Node* coprimes[COPRIME_ARRAY_LENGTH];
} Node;

// Returns the greatest common divisor for integers a and b
int gcd(int a, int b) {
    int maxNum;

    // find if a or b is smaller
    if (a < b) maxNum = a;
    else maxNum = b;

    // test possible divisors
    for (int divisor = maxNum; divisor > 1; divisor--) {
        if (a % divisor == 0 && b % divisor == 0) return divisor;
    }
    return 1;
}

// Finds the node that contains value n.
Node* findNode(Node* head, int n) {
    Node* node = head;
    while(/*node != NULL*/ 1) {
        if ((*node).value == n) return node;
        else node = (*node).next;
    }
    // return NULL;
}

void findCoprimes(Node* head, Node* node, int maxNum) {
    // 1 is always coprime
    (*node).coprimes[0] = head;

    // loop through each potential coprime from 2 to maxNum (inclusive)
    for (int coprimeCandidate = 2; coprimeCandidate < maxNum + 1; coprimeCandidate++) {
        // node and candidate are coprime if their gcd is 1
        if (gcd((*node).value, coprimeCandidate) == 1) {
            // add candidate to list of coprimes of node
            (*node).coprimes[(*node).numberOfCoprimes] = findNode(head, coprimeCandidate);
            (*node).numberOfCoprimes++;
        }
    }
}

// Generates graph of numbers that each link to their coprimes.
// Returns a pointer to the head node of the graph (holding the number 1).
Node* generateGraph(int maxNum) {
    // initialize head node which contains the number 1
    Node* head = (Node*) malloc(sizeof(Node));
    (*head).value = 1;
    (*head).numberOfCoprimes = 1;
    (*head).next = NULL;
    for (int j = 0; j < COPRIME_ARRAY_LENGTH; j++) {
        (*head).coprimes[j] = NULL;
    }

    // findCoprimes(head, head, maxNum);

    // initialize body nodes
    Node* nodeOld = head;
    for (int i = 2; i < maxNum + 1; i++) {
        // initialize next node
        Node* node = (Node*) malloc(sizeof(Node));
        (*node).value = i;
        (*node).numberOfCoprimes = 1;
        for (int j = 0; j < COPRIME_ARRAY_LENGTH; j++) {
            (*node).coprimes[j] = NULL;
        }

        (*nodeOld).next = node;

        nodeOld = node;
    }
    (*nodeOld).next = NULL;

    // link coprimes
    Node* node = head;
    for (int i = 0; i < maxNum; i++) {
        findCoprimes(head, node, maxNum);
        node = (*node).next;
    }

    return head;
}

void printNode(Node* node, char* verbose) {
    printf("%d\n", (*node).value);
    if (*verbose == 'y') {
        for (int i = 0; i < (*node).numberOfCoprimes; i++) {
            if (i == (*node).numberOfCoprimes - 1)
                printf("└── %d\n", (*(*node).coprimes[i]).value);
            else
                printf("├── %d\n", (*(*node).coprimes[i]).value);
        }
    }
}

void printGraph(Node* node, char* verbose) {
    while (node != NULL) {
        // printf("%d\n", (*node).value);
        // for (int i = 0; i < (*node).numberOfCoprimes; i++) {
        //     if (i == (*node).numberOfCoprimes - 1)
        //         printf("└── %d\n", (*(*node).coprimes[i]).value);
        //     else
        //         printf("├── %d\n", (*(*node).coprimes[i]).value);
        // }

        printNode(node, verbose);

        node = (*node).next;
    }
}

int main() {
    int max;
    char verbose;

    printf("Enter max: ");
    scanf("%d", &max);

    printf("Verbose? (y/n): ");
    scanf(" %c", &verbose);

    printGraph(generateGraph(max), &verbose);
}
