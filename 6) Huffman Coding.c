#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NODE
{
    char data;
    int freq;
    struct NODE *left;
    struct NODE *right;
};

typedef struct NODE NODE;

NODE *createNode(char data, int freq)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    node->data = data;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    return node;
}

NODE *buildHuffmanTree(char data[], int freq[], int n)
{
    int i;
    NODE *nodes[100];

    NODE *newNode;

    for (i = 0; i < n; i++)
    {
        nodes[i] = createNode(data[i], freq[i]);
    }

    while (n > 1)
    {
        int min1 = 0, min2 = 1;
        if (nodes[min1]->freq > nodes[min2]->freq)
        {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        for (i = 2; i < n; i++)
        {
            if (nodes[i]->freq < nodes[min1]->freq)
            {
                min2 = min1;
                min1 = i;
            }
            else if (nodes[i]->freq < nodes[min2]->freq)
            {
                min2 = i;
            }
        }

        newNode = createNode('\0', nodes[min1]->freq + nodes[min2]->freq);
        newNode->left = nodes[min1];
        newNode->right = nodes[min2];
        nodes[min1] = newNode;
        nodes[min2] = nodes[n - 1];
        n--;
    }
    return nodes[0];
}

void printHuffmanCodes(NODE *root, char code[], int top)
{
    if (root->left)
    {
        code[top] = '0';
        printHuffmanCodes(root->left, code, top + 1);
    }

    if (root->right)
    {
        code[top] = '1';
        printHuffmanCodes(root->right, code, top + 1);
    }

    if (!root->left && !root->right)
    {
        code[top] = '\0';
        printf("%c: %s\n", root->data, code);
    }
}

int main()
{
    int i, n;
    char data[100];
    int freq[100];
    char code[100];
    NODE *root;

    printf("Enter the number of characters: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter character %d: ", i + 1);
        scanf(" %c", &data[i]);

        printf("Enter frequency for character %c: ", data[i]);
        scanf("%d", &freq[i]);
    }

    root = buildHuffmanTree(data, freq, n);

    printf("Huffman Codes:\n");
    printHuffmanCodes(root, code, 0);

    return 0;
}


/*OUTPUT
/tmp/AR1DdXjNnG.o
Enter the number of characters: 4
Enter character 1: A
Enter frequency for character A: 5
Enter character 2: B
Enter frequency for character B: 1
Enter character 3: C
Enter frequency for character C: 6
Enter character 4: D
Enter frequency for character D: 3
Huffman Codes:
C: 0
B: 100
D: 101
A: 11
*/