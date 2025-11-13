#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    char name[50];
    int isFile; // 0 = folder, 1 = file
    struct Node* child;
    struct Node* sibling;
    struct Node* parent;
};

// Case-insensitive string compare
int strcasecmp_custom(const char* a, const char* b) {
    while (*a && *b) {
        char ca = tolower(*a);
        char cb = tolower(*b);
        if (ca != cb)
            return (ca - cb);
        a++;
        b++;
    }
    return *a - *b;
}

struct Node* createNode(char name[], int isFile, struct Node* parent) {
    struct Node* newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->name, name);
    newNode->isFile = isFile;
    newNode->child = NULL;
    newNode->sibling = NULL;
    newNode->parent = parent;
    return newNode;
}

int isValidName(char name[]) {
    int i;
    int len = strlen(name);
    if (len == 0)
        return 0;
    for (i = 0; i < len; i++) {
        if (name[i] == '/' || name[i] == '\\')
            return 0;
    }
    return 1;
}

void addNodeSorted(struct Node* parent, char name[], int isFile) {
    struct Node* temp;
    struct Node* prev;
    struct Node* newNode;

    if (!isValidName(name)) {
        printf("Invalid name! Cannot contain '/' or '\\'\n");
        return;
    }

    temp = parent->child;
    while (temp != NULL) {
        if (strcasecmp_custom(temp->name, name) == 0) {
            printf("Error: A file or folder named '%s' already exists in '%s'\n", name, parent->name);
            return;
        }
        temp = temp->sibling;
    }

    newNode = createNode(name, isFile, parent);
    if (parent->child == NULL || strcasecmp_custom(name, parent->child->name) < 0) {
        newNode->sibling = parent->child;
        parent->child = newNode;
        return;
    }

    temp = parent->child;
    prev = NULL;
    while (temp != NULL && strcasecmp_custom(name, temp->name) > 0) {
        prev = temp;
        temp = temp->sibling;
    }

    prev->sibling = newNode;
    newNode->sibling = temp;
}

void displayTree(struct Node* root, int level) {
    int i;
    if (root == NULL)
        return;

    for (i = 0; i < level; i++)
        printf("   ");

    if (root->isFile)
        printf("File: %s\n", root->name);
    else
        printf("Folder: %s\n", root->name);

    displayTree(root->child, level + 1);
    displayTree(root->sibling, level);
}

int deleteNode(struct Node* parent, char name[]) {
    struct Node* temp;
    struct Node* prev;
    int found;
    if (parent == NULL || parent->child == NULL)
        return 0;

    temp = parent->child;
    prev = NULL;
    found = 0;

    while (temp != NULL) {
        if (strcasecmp_custom(temp->name, name) == 0) {
            found = 1;
            break;
        }
        prev = temp;
        temp = temp->sibling;
    }

    if (!found)
        return 0;

    if (temp->isFile == 0 && temp->child != NULL) {
        printf("'%s' is not empty. Delete anyway? (y/n): ", name);
        char confirm;
        scanf(" %c", &confirm);
        if (confirm != 'y' && confirm != 'Y')
            return 0;
    }

    if (prev == NULL)
        parent->child = temp->sibling;
    else
        prev->sibling = temp->sibling;

    while (temp->child != NULL)
        deleteNode(temp, temp->child->name);

    free(temp);
    return 1;
}

void freeTree(struct Node* root) {
    if (root == NULL)
        return;
    freeTree(root->child);
    freeTree(root->sibling);
    free(root);
}

void list(struct Node* folder) {
    struct Node* temp;
    temp = folder->child;
    if (temp == NULL) {
        printf("(empty)\n");
        return;
    }
    while (temp != NULL) {
        if (temp->isFile)
            printf("[File] %s\n", temp->name);
        else
            printf("[Folder] %s\n", temp->name);
        temp = temp->sibling;
    }
}

struct Node* changeDir(struct Node* current, char name[]) {
    struct Node* temp;
    if (strcmp(name, "..") == 0) {
        if (current->parent != NULL)
            return current->parent;
        else {
            printf("Already at root.\n");
            return current;
        }
    }

    temp = current->child;
    while (temp != NULL) {
        if (strcasecmp_custom(temp->name, name) == 0 && temp->isFile == 0)
            return temp;
        temp = temp->sibling;
    }
    printf("Folder not found!\n");
    return current;
}

void getFullPath(struct Node* node, char* path) {
    if (node == NULL)
        return;
    if (node->parent != NULL)
        getFullPath(node->parent, path);
    strcat(path, "/");
    strcat(path, node->name);
}

/* ---------------- MAIN ---------------- */

int main() {
    struct Node* root;
    struct Node* current;
    char command[20];
    char name[50];
    char path[300];
    int running;
    int result;

    root = createNode("Root", 0, NULL);
    current = root;
    running = 1;

    printf("====================================\n");
    printf("     FILE SYSTEM SIMULATOR (Tree)\n");
    printf("====================================\n");
    printf("\nAvailable Commands:\n");
    printf("------------------------------------\n");
    printf("mkdir <folder_name>     -> Create a new folder\n");
    printf("touch <file_name>       -> Create a new file\n");
    printf("ls                      -> List contents of current folder\n");
    printf("cd <folder_name>        -> Change directory\n");
    printf("cd ..                   -> Go back to parent folder\n");
    printf("rm <file/folder_name>   -> Delete a file or folder\n");
    printf("tree                    -> Display full directory structure\n");
    printf("exit                    -> Quit\n");
    printf("------------------------------------\n");

    while (running) {
        path[0] = '\0';
        getFullPath(current, path);
        printf("%s$ ", path);
        scanf("%s", command);

        if (strcasecmp_custom(command, "mkdir") == 0) {
            scanf("%s", name);
            addNodeSorted(current, name, 0);
        } else if (strcasecmp_custom(command, "touch") == 0) {
            scanf("%s", name);
            addNodeSorted(current, name, 1);
        } else if (strcasecmp_custom(command, "ls") == 0) {
            list(current);
        } else if (strcasecmp_custom(command, "cd") == 0) {
            scanf("%s", name);
            current = changeDir(current, name);
        } else if (strcasecmp_custom(command, "rm") == 0) {
            scanf("%s", name);
            if (strcasecmp_custom(current->name, "Root") == 0 && strcasecmp_custom(name, "Root") == 0) {
                printf("Cannot delete Root directory.\n");
            } else {
                result = deleteNode(current, name);
                if (result)
                    printf("Deleted successfully.\n");
                else
                    printf("File/Folder not found.\n");
            }
        } else if (strcasecmp_custom(command, "tree") == 0) {
            printf("\n====== Directory Structure ======\n");
            displayTree(root, 0);
            printf("=================================\n");
        } else if (strcasecmp_custom(command, "exit") == 0) {
            running = 0;
        } else {
            printf("Invalid command!\n");
        }
    }

    freeTree(root);
    printf("Memory cleared. Exiting...\n");
    return 0;
}