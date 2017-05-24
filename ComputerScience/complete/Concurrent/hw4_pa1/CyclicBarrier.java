////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Alex Hortin
//PA1
//CPTS 483 
//March 2009
//CyclicBarrier.java
//
//	CyclicBarrier is described in section 5.5.4. The constructor initializes a counter. The await()
//	method decrements the counter and waits until the counter reaches zero at which point all waiting
//	threads are released, the counter is reset to its initial value, and subsequent calls to await again
//	block until the counter reaches 0. Undergrads: you do not need to implement the handling of
//	timeouts and interruptions described in the text; Grads should do a full implementation. Nobody
//	needs to implement the barrier action feature described in the first line of p. 101.) Note: my Race
//	program for assignment 1 contained a barrier implementation but it does not fully meet the re-
//	usability requirements for this assignment. You may use it as a starting point if you wish.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public class CyclicBarrier {
	//////////////////////////////////////////////////////////////////////////
	//	Member Variables
 	private int nThreads;
 	private int waitingthreads = 0;
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	//
	//	CyclicBarrier()		 
	//
	//This is the CyclicBarrier constructor it takes in a set number of 
	//threads that the barrier will wait to reach.  
	//   
	// 	pre		iThreads >= 0    
   	//	post    nThreads >= 0
   	//	param	iThreads:	the ammount of threads the barrier waits for  
   	//	return 
   	//	throw  
	//////////////////////////////////////////////////////////////////////////	
	CyclicBarrier(int iThreads)   throws IllegalArgumentException
	{
		if (iThreads < 0){
			throw new IllegalArgumentException( "# of threads greater or equal to 0");//if n less than zero throw an illegal argument exception
		}
		this.nThreads = iThreads;//setting the 
	}
	//////////////////////////////////////////////////////////////////////////
	//
	//		await() 
	//
	//The await method blocks until the count reaches the ammount of threads 
	//established in the creation of the barrier.  Whenever a thread enters
	//await, it will increment the waiting threads and than check to see if 
	//the ammount is equal to the number of threads it's waiting for.  If it
	//is it notifies all sleeping threads, than resets the waiting threads. If
	//there still needs to be more the thread will go to sleep, and wait for 
	//more to wait.  Since it modifies the state, it needs to be synchronized.
	//It will not deadlock since sleep give up the lock.
	//   
	// 	pre    count >= 0
   	//	post   count == 0
   	//	param  none
   	//	return none
   	//	throw  none
	//////////////////////////////////////////////////////////////////////////	
	public synchronized void await()  throws InterruptedException 
	{	    
		this.waitingthreads++;	//adding to the waiting threads when another enters
    	//System.out.println(this.waitingthreads);
    	if (this.waitingthreads == this.nThreads){//if the number of threads is equal to the waiting number reset
			notifyAll();//lets all sleeping threads know
			this.waitingthreads = 0;//reset the waiting count
			
		}
		else{//goto sleep bro!
			try{			
					wait();//puts the program to sleep and releases the lock
			}
			finally{
			}
		}
	}

}