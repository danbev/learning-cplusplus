# Detailed Explanation of std::vector, Heap Data Structure, and Memory Usage

## 1. std::vector and Memory

A `std::vector` uses dynamic memory allocation (the first type of "heap"), but
it's not inherently a heap data structure.

Let's visualize a `std::vector`:

```
Stack Memory:
+------------------------+
| vector object          |
| (contains pointer,     |
|  size, and capacity)   |
+------------------------+
        |
        | (points to)
        v
Heap Memory:
+---+---+---+---+---+---+
| 3 | 1 | 4 | 1 | 5 | 9 |
+---+---+---+---+---+---+
```

The vector object itself is typically on the stack, but the actual data it
contains is in dynamic memory (often called the "heap").

## 2. Heap Data Structure

Now, let's talk about the heap data structure. A heap is a tree-based structure
that satisfies the heap property. For a max-heap, this means that for any given
node, the parent node has a value greater than or equal to the values of its
children.

Our initial vector `{3, 1, 4, 1, 5, 9}` is not a heap. Let's visualize it as a binary tree:

```
       3
     /   \
    1     4
   / \   /
  1   5 9
```

This doesn't satisfy the heap property for a max-heap.

## 3. std::make_heap

When we call `std::make_heap(v.begin(), v.end())`, it rearranges the elements
to satisfy the heap property. For a max-heap:

```
       9
     /   \
    5     4
   / \   /
  1   3 1
```

In memory, our vector now looks like this:

```
+---+---+---+---+---+---+
| 9 | 5 | 4 | 1 | 3 | 1 |
+---+---+---+---+---+---+
```

## 4. Adding a New Element

When we do `v.push_back(6)`, it adds 6 to the end of the vector:

```
+---+---+---+---+---+---+---+
| 9 | 5 | 4 | 1 | 3 | 1 | 6 |
+---+---+---+---+---+---+---+
```

As a tree, it looks like this:

```
       9
     /   \
    5     4
   / \   / \
  1   3 1   6
```

This no longer satisfies the heap property.

## 5. std::push_heap

`std::push_heap(v.begin(), v.end())` restores the heap property by moving the
new element (6) up the tree as needed:

```
       9
     /   \
    5     6
   / \   / \
  1   3 1   4
```

In memory:

```
+---+---+---+---+---+---+---+
| 9 | 5 | 6 | 1 | 3 | 1 | 4 |
+---+---+---+---+---+---+---+
```
