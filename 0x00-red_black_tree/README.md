# 🔴⚫ Red-Black Tree

A self-balancing binary search tree where every node carries a **RED** or **BLACK** color, enforcing strict balance rules to guarantee **O(log n)** operations.

---

## 📐 Rules

1. Every node is RED or BLACK
2. Root is always BLACK
3. No two consecutive RED nodes (RED node → BLACK children)
4. Every path from a node to its NULL descendants has the same number of BLACK nodes

---

## 📁 Files

| File | Description |
|---|---|
| `0-rb_tree_node.c` | Creates a new Red-Black tree node |
| `1-rb_tree_is_valid.c` | Validates a Red-Black tree |
| `2-rb_tree_insert.c` | Inserts a value, rebalances the tree |
| `3-array_to_rb_tree.c` | Builds a Red-Black tree from an array |
| `4-rb_tree_remove.c` | Removes a node, rebalances the tree |
| `5-O` | Big O complexity file |
| `rb_trees.h` | Structs, enums, and function prototypes |

---

## 🧩 Data Structures

```c
typedef enum rb_color_e { RED = 0, BLACK, DOUBLE_BLACK } rb_color_t;

typedef struct rb_tree_s {
    int n;
    rb_color_t color;
    struct rb_tree_s *parent;
    struct rb_tree_s *left;
    struct rb_tree_s *right;
} rb_tree_t;
```

---

## 🔧 API

```c
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color);
int        rb_tree_is_valid(const rb_tree_t *tree);
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value);
rb_tree_t *array_to_rb_tree(int *array, size_t size);
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n);
void       rotate_left(rb_tree_t **tree, rb_tree_t *node);
void       rotate_right(rb_tree_t **tree, rb_tree_t *node);
```

---

## ⏱️ Complexity

| Operation | Time |
|---|---|
| Insert | O(log n) |
| Delete | O(log n) |
| Search | O(log n) |
| Space  | O(n) |
