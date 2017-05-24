class Planet {

    private double gravity; /* units: (m/s/s) */
    private double ground;  /* units: m */
    private String name;

    /* constructors and accessors go here--you are to complete them */
    public Planet(double gravityC, double groundC, String nameC) 
	{
		gravity = gravityC;//initializes the local varibles
		ground = groundC;//initializes the local varibles
		name = nameC;//initializes the local varibles
	}
	//Returns the gravity stored locally
	public double getGravity() 
	{
		return gravity;
	}
	//Returns the ground in meters
	public double getGround() 
	{
		return ground;
	}
	//Returns the name of the planet
	public String getName() 
	{
		return name;
	}   
    //public Planet() {} // creates a devoid lame planet...
}
