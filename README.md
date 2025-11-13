# 📂 File System Simulator (Tree)

A **C language** console application that simulates a hierarchical **file system** (like Windows or Linux) using a **multi-way tree** data structure. This project demonstrates core concepts of data structures (trees, linked lists) and memory management (dynamic allocation, recursion for cleanup) by allowing users to interact with files and folders through common command-line interface (CLI) commands.

---

## 🚀 Features

* **Hierarchical Structure:** Simulates files and folders organized in a **tree** structure.
* **CLI Commands:** Supports essential file system operations like `mkdir`, `touch`, `ls`, `cd`, `rm`, and `tree`.
* **Case-Insensitive Operations:** Implements custom case-insensitive comparison for file/folder names.
* **Sorted Contents:** Automatically inserts new nodes in **alphabetically sorted order** within their parent directory.
* **Path Tracking:** Displays the current full working directory path (e.g., `/Root/FolderA`).
* **Recursive Deletion:** Allows deletion of non-empty folders after user confirmation, recursively freeing all associated memory.

---

## ⚙️ Data Structure

The file system uses a tree structure where each node represents a file or folder:

```c
struct Node {
    char name[50];
    int isFile; // 0 = folder, 1 = file
    struct Node* child;    // First child in the directory
    struct Node* sibling;  // Next item in the directory list
    struct Node* parent;
};
```

---

## 🛠️ Installation & Usage

1️⃣ Clone the Repository

```
git clone https://github.com/ranjanvrma/file-system-simulator.git
cd file-system-simulator
```

2️⃣ Compile and Run the App

```
gcc -o filesystem main.c
./filesystem
```

---

## 🧮 Menu Options

The application uses a CLI loop for interaction.

```
====================================
     FILE SYSTEM SIMULATOR Tree
====================================

Available Commands:
------------------------------------
mkdir folder_name       -> Create a new folder
touch file_name         -> Create a new file
ls                      -> List contents of current folder
cd folder_name          -> Change directory
cd ..                   -> Go back to parent folder
rm file/folder_name     -> Delete a file or folder
tree                    -> Display full directory structure
exit                    -> Quit
------------------------------------
```

---

## 🧭 Example Run

```
/Root$ mkdir Documents
/Root$ cd Documents
/Root/Documents$ mkdir Files
/Root/Documents$ touch Notebook.txt
/Root/Documents$ tree

====== Directory Structure ======
Folder: Root
   Folder: Documents
      Folder: Files
      File: Notebook.txt
=================================
/Root/Documents$ exit
Memory cleared. Exiting...
```

---

## 🧠 How It Works
- Tree Structure: The tree is built using a first-child, next-sibling representation, efficient for directories.
- Sorting: The addNodeSorted function ensures alphabetical, case-insensitive sorting using the sibling pointers.
- Deletion: deleteNode handles recursive cleanup of contents before freeing a folder node, essential for memory safety.

---

## 🧱 File Structure

```
file-system-simulator/
|
├── main.c           # All source code for the file system simulator
├── README.md        # Project documentation
```

---

## 🧑‍💻 Tech Stack

- Language: C
- Data Structure: Multi-way Tree (First-Child, Next-Sibling)
- Algorithms: Recursive Traversal, Sorted Linked List Insertion

---

## 💡 Future Enhancements

- Absolute/Relative Paths: Implement support for full path navigation (e.g., cd /Root/FolderA/).
- rename Command: Add functionality to change the name of files and folders.
- File Permissions: Extend the structure to include basic read/write permission handling.

---

## 👨‍💻 Author

Ranjan Verma | ranjanverma2310@gmail.com | [Github Profile](https://github.com/ranjanvrma)
