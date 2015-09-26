class red_black_test {

   public static void main (String[] args) {
      red_black test = new red_black();

      test.insert(1);
      test.insert(2);
      test.insert(0);
      test.insert(5);
      test.insert(4);
      test.insert(10);
      test.insert(3);
      test.insert(6);
      test.insert(7);
      test.insert(9);
      test.insert(11);
      test.insert(8);
      test.insert(100);

      test.delete(1);
      test.print();
      System.out.printf("\n\n");
      test.delete(5);
      test.print();
      System.out.printf("\n\n");
      test.delete(3);
      test.print();
      System.out.printf("\n\n");
      test.delete(10);
      test.print();
      test.delete(100);
      test.print();
      test.delete(8);
      test.print();
   }
}
