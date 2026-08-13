Here's a breakdown of this doubly-ended queue (deque) implementation using a doubly linked list.

## Structure

```c
struct node {
    int data;
    struct node *prev, *next;
};
```
Each node stores a value plus pointers to the previous and next nodes. Two global pointers, `head` and `tail`, track the front and rear of the deque.

## Core Functions

**`createNode(data)`** — allocates a new node, sets its `data`, and initializes both `prev` and `next` to `NULL`. Exits the program if `malloc` fails.

**`enqueueAtFront(data)`** — inserts at the front:
- If the deque is empty, the new node becomes both `head` and `tail`.
- Otherwise, it links the new node before the current `head`, then updates `head` to point to it.

**`enqueueAtRear(data)`** — mirror image of the above, inserting after `tail`.

**`dequeueAtFront()`** — removes the front node:
- If there's only one node, both `head` and `tail` are reset to `NULL`.
- Otherwise, `head` moves to `head->next`, and the new head's `prev` is set to `NULL`.
- The old node is freed.

**`dequeueAtRear()`** — mirror image, removing from `tail` and moving it to `tail->prev`.

**`display()`** — walks from `head` to `NULL` via `next` pointers, printing each value left-aligned in a 3-character field (`%-3d`).

## `main()` — Menu Loop

Runs an infinite loop presenting a menu (enqueue front/rear, dequeue front/rear, display, exit). It reads the choice with `scanf`, and:
- Breaks out of the loop entirely if `scanf` fails to read an integer (e.g., EOF or bad input).
- On exit (`case 6`), it drains all remaining nodes via repeated `dequeueAtFront()` calls before calling `exit(0)`, avoiding memory leaks.

## Notable Design Points / Minor Issues

1. **Correctness**: The logic is sound — head/tail are properly maintained, and single-node edge cases are handled correctly in both enqueue and dequeue operations.
2. **No `NULL` head/tail race**: Since `head` and `tail` are checked consistently (`head == NULL` for enqueue-front-empty check, `tail == NULL` for enqueue-rear-empty check), there's no drift between them.
3. **`exit(0)` inside `switch`**: This works but is a bit unusual — typically you'd `break` out of the `while(1)` loop and `return 0` from `main` instead of calling `exit()` directly. Functionally equivalent here since cleanup is already done before the call.
4. **No dynamic freeing of `newnode` on malloc failure path**: Not an issue since `exit(1)` terminates immediately, but worth knowing this pattern doesn't scale to more complex cleanup needs.
5. **`display()` doesn't show `prev` traversal**: It only prints front-to-rear; a reverse display (rear-to-front using `prev`) could be added to demonstrate the "doubly" linked nature more fully, though it's not required for correctness.

Here's both — a reverse-display function, plus a step-by-step trace.

## Reverse Display Function

```c
// Display all elements from rear to front
void displayReverse() {
    if (tail == NULL) {
        printf("Queue is empty\n");
        return;
    }

    struct node *temp = tail;
    while (temp != NULL) {
        printf("%-3d", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}
```
This walks backward from `tail` using the `prev` pointers — the mirror of `display()`, which is the whole point of a doubly linked list: you can traverse it either direction in O(n).

To hook it into the menu, add a case (e.g. `7`) and update the menu text/switch accordingly.

## Trace Through Example Operations

Starting state: `head = NULL`, `tail = NULL`

**1. `enqueueAtFront(10)`** — deque empty, so:
`head = tail → [10]`

**2. `enqueueAtRear(20)`** — not empty, attach after tail:
`head → [10] ⇄ [20] ← tail`

**3. `enqueueAtFront(5)`** — attach before head:
`head → [5] ⇄ [10] ⇄ [20] ← tail`

**4. `enqueueAtRear(30)`** — attach after tail:
`head → [5] ⇄ [10] ⇄ [20] ⇄ [30] ← tail`

**5. `dequeueAtFront()`** — head ≠ tail, so `head` moves to next node (`10`), new head's `prev` set to `NULL`, old node `[5]` freed:
`head → [10] ⇄ [20] ⇄ [30] ← tail`

**6. `dequeueAtRear()`** — tail moves to previous node (`20`), new tail's `next` set to `NULL`, old node `[30]` freed:
`head → [10] ⇄ [20] ← tail`

**7. `display()`** prints: `10  20`
**`displayReverse()`** prints: `20  10`

The key invariant at every step: `head->prev` is always `NULL` and `tail->next` is always `NULL` — that's what makes both traversal directions terminate correctly.
