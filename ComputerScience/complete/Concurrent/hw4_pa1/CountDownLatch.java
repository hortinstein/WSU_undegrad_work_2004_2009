////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Alex Hortin
//PA1
//CPTS 483 
//March 2009
//CountDownLatch.java
//
//	CountDownLatch is described in section 5.5.1. The constructor initializes a counter to the
//	provided value. The countdown() method decrements the counter (by 1); the await()
//	method returns when the counter is no longer positive.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public class CountDownLatch {
	//////////////////////////////////////////////////////////////////////////
	//	Member Variables
	private int count;//this is the count variable that countdown() and await() use 
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//
	//		CountDownLatch(int initialCount)
	//
	//This is the constructor for the CountDownLatch and the argument is the
	//number the initial count will be set to for the countdown 
	//
	// 	pre	initialCount >= 0    
   	//	post   	count >= 0
   	//	param  	intialCount:	Tells what the initial count is
   	//	return  none
   	//	throw   none
	//////////////////////////////////////////////////////////////////////////	
	CountDownLatch(int initialCount) throws IllegalArgumentException
	{
		if (initialCount < 0){
			throw new IllegalArgumentException( "# of permits must be greater or equal to 0");//if n less than zero throw an illegal argument exception
		}
		this.count = initialCount;//setting the initial count value
	}
	//////////////////////////////////////////////////////////////////////////
	//
	//		countdown() 
	//
	//This method decrements the count by 1.  It needs to be synchronized due
	//to the state modification to get a valid number.  
	//   
	// 	pre    count >= 0
   	//	post   count >= 0
   	//	param  none
   	//	return none
   	//	throw  none
	//////////////////////////////////////////////////////////////////////////	
	public synchronized void countdown()
	{
		
		if (this.count-1 <= 0){//if the count after decrement is zero
			this.count--;
			notifyAll();
			return;
		}
		this.count--;//decrement the countdown
		
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//		await() 
	//
	//The await method blocks until the count reaches zero.  Once the count
	//reaches zero the await method will return.  This does not need to be 
	//synchronized since it does not modify the state of any variables.  
	//	
	//   
	// 	pre    count >= 0
   	//	post   count == 0
   	//	param  none
   	//	return none
   	//	throw  none
	//////////////////////////////////////////////////////////////////////////	
	public void await()  throws InterruptedException 
	{	
    	try{			
				wait();//puts the program to sleep waiting for permits to be available
		}
		finally{
		}
	}
	
}
