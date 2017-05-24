class StacksizeTest implements Runnable {
   	int depth = 0;
   	public void run() {
      	try {
         		doOverflow();
      		} 
		catch (StackOverflowError e) {
         		System.out.println("Overflow occured at depth" + depth + ".");
				
   			}
	}
   	void doOverflow() { depth += 1; doOverflow(); }
  	public static void main(String argv[]) {
	 	StacksizeTest thread = new StacksizeTest();
	 	thread.run();
	}
}

