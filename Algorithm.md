Algorithm: Double-Ended Queue (Deque) using Doubly Linked List
1. createNode(data)
 * Step 1: Allocate memory dynamically for a new node newnode.
 * Step 2: If allocation fails (newnode == NULL), display "Memory allocation failed" and exit.
 * Step 3: Set newnode->data = data.
 * Step 4: Set newnode->next = NULL and newnode->prev = NULL.
 * Step 5: Return newnode.
2. enqueueAtFront(data)
 * Step 1: Call createNode(data) to create newnode.
 * Step 2: If head == NULL (Queue is empty):
   * Set head = newnode
   * Set tail = newnode
 * Step 3: Else (Queue is not empty):
   * Set newnode->next = head
   * Set head->prev = newnode
   * Set head = newnode
 * Step 4: End.
3. enqueueAtRear(data)
 * Step 1: Call createNode(data) to create newnode.
 * Step 2: If tail == NULL (Queue is empty):
   * Set head = newnode
   * Set tail = newnode
 * Step 3: Else (Queue is not empty):
   * Set tail->next = newnode
   * Set newnode->prev = tail
   * Set tail = newnode
 * Step 4: End.
4. dequeueAtFront()
 * Step 1: If head == NULL, print "Queue Underflow" and return.
 * Step 2: Set temp = head.
 * Step 3: If head == tail (Only one element exists):
   * Set head = NULL
   * Set tail = NULL
 * Step 4: Else:
   * Set head = head->next
   * Set head->prev = NULL
 * Step 5: Free temp.
 * Step 6: End.
5. dequeueAtRear()
 * Step 1: If tail == NULL, print "Queue Underflow" and return.
 * Step 2: Set temp = tail.
 * Step 3: If head == tail (Only one element exists):
   * Set head = NULL
   * Set tail = NULL
 * Step 4: Else:
   * Set tail = tail->prev
   * Set tail->next = NULL
 * Step 5: Free temp.
 * Step 6: End.
6. display()
 * Step 1: If head == NULL, print "Queue is Empty" and return.
 * Step 2: Set temp = head.
 * Step 3: While temp != NULL:
   * Print temp->data
   * Set temp = temp->next
 * Step 4: End.
