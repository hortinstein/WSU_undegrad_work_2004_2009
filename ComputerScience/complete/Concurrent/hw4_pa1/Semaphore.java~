//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Alex Hortin
//PA1
//CPTS 483 
//March 2009
//Semaphone.java
//
//	Semaphore semantics are described in section 5.5.3. This is essentially the same as exam problem
//	1 but you will have to deal with exceptions and the methods are more general. Implement a
//	constructor providing the initial number of permits, and public methods for acquire(int n)
//	and release(int n). Overloaded parameterless methods acquire() and release()
//	correspond to passing 1 to the parameter-ful versions.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public class Semaphore {
	//////////////////////////////////////////////////////////////////////////
	//	Member Variables
 	int permits;
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	//
	//		Semaphore(int initialPermits)
	//
	//This is the constructor that takes the initial number of permits the 
	//semaphore is allowed to issue.  This number must be positive
	//	
	// 	pre    	initialPermits >= 0
   	//	post   	initialPermits >= 0
   	//	param  	initialPermits: 	an integer to set the initial ammount of 
	//								permits
   	//	return 	none
   	//	throw  	IllegalArgumentException:	throws if the initial 
	//										permits are less than zero
	//////////////////////////////////////////////////////////////////////////
	Semaphore(int initialPermits) throws IllegalArgumentException
	{
		if (initialPermits < 0){
			throw new IllegalArgumentException( "# of permits must be greater or equal to 0");//if n less than zero throw an illegal argument exception
		}
		this.permits = initialPermits;//initializing the ammount of permits available
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//		acquire(int n) 
	//
	//The acquire method takes a number (n) and trys to acquire that many 
	//permits.  If there are not that many available it blocks.  Since this
	//modifies a variable that could possibly be called through many different
	//threads it is nessecary to synchronize this method to ensure the number
	//of permits is correct.  If there are no permits available, it will block
	//until some become available.  Once notified it will check if the number
	//of available permits is greater or equal to the ammount that it's trying
	//to acquire.  If there are enough it will return, if not it will wait 
	//again 
	//   
	// 	pre    	permits available >= 0
   	//	post   	permits available >= 0
   	//	param  	n:	number of permits to acquire
   	//	return 	none
   	//	throw	InterruptefException:	thrown if a thread is interupted
	//									during wait
	//			IllegalArgumentException:	thrown if n is negitive
	//////////////////////////////////////////////////////////////////////////	
	public synchronized void acquire(int n) throws InterruptedException,IllegalArgumentException 
	{
		if (n < 0){
			throw new IllegalArgumentException( "# of permits must be greater than 0");//if n less than zero throw an illegal argument exception
		}
        	while (this.permits < n){//loop if the ammount of permits is less than the ammount we need
			try{			
				wait();//puts the program to sleep waiting for permits to be available
			}
			finally{
			}
		}
		this.permits-=n;//subtract the permits than return
    }
	//////////////////////////////////////////////////////////////////////////
	//
	//		acquire() 
	//
	//This is an overloaded version of the acquire method that can be called
	//without any parameters.  It simply calls the parameter version with an
	//argument of 1. It does not need synchronization since the method it 
	//calls is already thread safe.
	//   
	// 	pre		permits available >= 0
   	//	post	permits available >= 0
   	//	param 	none
   	//	return	none
   	//	throw  	InterruptefException:	thrown if a thread is interupted
	//									during wait
	//////////////////////////////////////////////////////////////////////////	
	public void acquire() throws InterruptedException
	{
		System.out.println("asda");
		acquire(1);//calls the version of acquire that takes a variable
	}
	//////////////////////////////////////////////////////////////////////////
	//
	//		release() 
	//
	//Release is a method of the semaphore that makes permits available to
	//aquire.  This method takes in (n) and than releases that many permits.  
	//It then notifies all that there is a permit available. This needs to be
	//synchronized since it is modifies a shared variable.  After it adds to
	//the permits, it calls notify to let all the waiting threads know the 
	//permit pool has been modified
	//
	// 	pre    	permits available >= 0
   	//	post   	permits available >= 0
   	//	param  	n:	the number of permits to release
   	//	return 	none
   	//	throw  	none
	//////////////////////////////////////////////////////////////////////////	
	public synchronized void release(int n) throws IllegalArgumentException
	{
		if (n < 0){
			throw new IllegalArgumentException( "# of permits must be greater than 0");//if n less than zero throw an illegal argument exception
		}        	
		this.permits+=n;//adding n to the permits 
		notifyAll();//notifying all waiting threads that there are new permits available
    	}
	//////////////////////////////////////////////////////////////////////////
	//
	//		release() 
	//
	//This is an overloaded version of the release method that can be called
	//without any parameters.  It simply calls the parameter version with an
	//argument of 1. It does not need synchronization since the method it 
	//calls is already thread safe.
	//   
	// 	pre    	permits available >= 0
   	//	post   	permits available >= 0
   	//	param  	none
   	//	return 	none
   	//	throw  	none
	//////////////////////////////////////////////////////////////////////////	
	public void release() 
	{
		release(1);//calls the version of release that takes a variable        	
    	}
}

