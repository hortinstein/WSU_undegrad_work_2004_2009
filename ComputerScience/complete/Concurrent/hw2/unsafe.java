class UnsafeStates {
    private String[] states = new String[] {
        "AK", "AL" ...
    };
    public String[] getStates() { return states; }
	public static void main(String argv[]) {
	 	System.out.println(getStates[1]);
	}
}



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

