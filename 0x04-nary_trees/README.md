# 🌳 N-ary Trees

A generalization of binary trees where each node can have **any number of children**. Useful for modeling hierarchies like file systems, organizational charts, and parse trees.

---

## 📁 Files

| File | Description |
|---|---|
| `0-nary_tree_insert.c` | Inserts a new node into an N-ary tree |
| `1-nary_tree_delete.c` | Recursively deletes an entire N-ary tree |
| `2-nary_tree_traverse.c` | Traverses the tree, calling an action at each node |
| `3-nary_tree_diameter.c` | Computes the diameter (longest path) of the tree |
| `4-path_exists.c` | Checks if a given path of node values exists |
| `nary_trees.h` | Struct definition and function prototypes |

---

## 🧩 Data Structure

```c
typedef struct nary_tree_s {
    char               *content;
    struct nary_tree_s *parent;
    size_t              nb_children;
    struct nary_tree_s *children;  /* head of children linked list */
    struct nary_tree_s *next;      /* next sibling */
} nary_tree_t;
```

---

## 🔧 API

```c
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str);
void         nary_tree_delete(nary_tree_t *tree);
size_t       nary_tree_traverse(nary_tree_t const *root,
                 void (*action)(nary_tree_t const *node, size_t depth));
size_t       nary_tree_diameter(nary_tree_t const *root);
int          path_exists(nary_tree_t const *root, char const * const *path);
```

---

## ⏱️ Complexity

| Operation | Time |
|---|---|
| Insert | O(1) |
| Traverse | O(n) |
| Diameter | O(n) |
| Path exists | O(n × d) — d = path depth |
| Delete | O(n) |
