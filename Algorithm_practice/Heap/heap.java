/*Adam Pinarbasi
 * heap.java
 * implementation of heap ADT */

class heap {

   //fields
   
   int size;
   int[] tree;

   //methods
   
   /* returns a sorted, descending array */
   int[] max_heap_sort () {
      int size_cpy = size; 
      int[] sorted = new int[size + 1];
      build_max_heap();

      for (int i = 1; i <= size_cpy; ++i) {
         max_heapify(1);

         int temp = tree[size];
         tree[size] = tree[1];
         tree[1] = temp;

         sorted[i] = tree[size];
         --size;
      }
      return sorted;
   }

   /* returns a sorted, ascending array */
   int[] min_heap_sort () {
      int size_cpy = size;
      int[] sorted = new int[size + 1];
      build_min_heap();

      for (int i = 1; i <= size_cpy; ++i) {
         min_heapify(1);

         int temp = tree[size];
         tree[size] = tree[1];
         tree[1] = temp;

         sorted[i] = tree[size];
         --size;
      }
      return sorted;
   }

   void build_max_heap () {
      for (int i = size / 2; i >= 1; --i) 
         max_heapify(i);
   }

   void build_min_heap () {
      for (int i = size / 2; i >= 1; --i)
         min_heapify(i);
   }

   /* Precondition: left[index] and right[index] must be max heaps */
   void max_heapify (int index) {
      if (2 * index > size) return;
      else if (2 * index + 1 > size) {
         if (tree[2 * index] > tree[index]) {
            int temp = tree[2 * index];
            tree[2 * index] = tree[index];
            tree[index] = temp;
         }
         return; //must be final node
      }

      int left        = tree[2 * index];
      int right       = tree[2 * index + 1];
      int greater_ind = (left > right ? 2 * index : 2 * index + 1);
      if (tree[greater_ind] > tree[index]) {
         int temp = tree[greater_ind];
         tree[greater_ind] = tree[index];
         tree[index] = temp;
      }
      max_heapify(greater_ind);
   }

   /* Precondition: left[index] and right[index] must be min heaps */
   void min_heapify (int index) {
      if (2 * index > size) return;
      else if (2 * index + 1 > size) {
         if (tree[2 * index] < tree[index]) {
            int temp = tree[2 * index];
            tree[2 * index] = tree[index];
            tree[index] = temp;
         }
         return; //must be final node
      }

      int left      = tree[2 * index];
      int right     = tree[2 * index + 1];
      int lower_ind = (left < right ? 2 * index : 2 * index + 1);
      if (tree[lower_ind] < tree[index]) {
         int temp = tree[lower_ind];
         tree[lower_ind] = tree[index];
         tree[index] = temp;
      }
      min_heapify(lower_ind);
   }
}
