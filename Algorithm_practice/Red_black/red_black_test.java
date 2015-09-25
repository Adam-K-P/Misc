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

      test.delete(1);
      test.delete(3);
      test.delete(10);
      test.delete(5);

      test.print();
   }
}
