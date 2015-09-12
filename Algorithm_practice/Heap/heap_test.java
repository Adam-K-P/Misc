class heap_test {
   
   public static void main (String[] args) {
      heap H = new heap();
      int[] tree = {0, 16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
      H.tree = tree;
      H.size = 10;
      int[] tmp = H.min_heap_sort();
      for (int i = 1; i <= 10; ++i) 
         System.out.printf("%d\n", tmp[i]);
   }
}
