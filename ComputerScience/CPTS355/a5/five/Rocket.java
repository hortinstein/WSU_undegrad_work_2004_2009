import java.text.DecimalFormat;

class Rocket {
    static final RocketException crashed = new RocketException("Crashed and Burned");
    static final RocketException landed = new RocketException("Safely Landed");
    private double velocity = 0.0; // default to 0
    private double height = 50.0; // default to 50.0
	private double fuel = 20.0;//the default ammount of fuel is 25
	private double engineStrength = 2.0;// default ammount of strength in engine
    private Planet planet;
    private static final double safeVelocity = -1.0; // Land within this velocity

	public Rocket(double engineStrengthC, double fuelC, Planet planetC) {
		engineStrength = engineStrengthC;
		fuel = fuelC;
		planet = planetC;
	}
	//getplanet returns the planet	
	public double getPlanetGround() 
	{
		return planet.getGround();
	}
	//getHeight - Returns the current height.
	public double getHeight()
	{
		return height;
	}
	//getVelocity - Returns the current velocity.
	public double getVelocity()
	{
		return velocity;
	}
	//getsafeVelocity - Returns -1
	public double getSafeVelocity() 
	{
		return safeVelocity;
	}
	//setHeight sets the height of the rocket to input
	public void setHeight(double newheight) {
		height = newheight;
	}
	//getHeightString returns a string with an asterisk in representing the position of the rocket and a `|' representing the position of the planet's surface.
	public String getHeightString() 
	{
        double maxHeight = (height > 60.0) ? height : 60.0;
        double belowGround = planet.getGround() - 10.0;
        int size = (int) (maxHeight - belowGround) + 1;
        char[] buffer = new char[size];
        DecimalFormat df = new DecimalFormat(" ###.##");

        int groundPosition = (int) (planet.getGround() - belowGround);

        for (int i = 0; i < size; i++)
            buffer[i] = ' ';
        int adjustedPosition = (int) (height - belowGround);
        adjustedPosition = (adjustedPosition <= 0) ? 0 : adjustedPosition;
        /* prove here, using wp logic, that 0 <= adjustedPosition <= size-1 */
        buffer[groundPosition] = '|';
        buffer[adjustedPosition] = '*';
        return (new String(buffer) + " " + df.format(velocity));
    }
	//This method returns a string consisting of the height, velocity, and amount of fuel for the rocket
	public String getState()
	{
		DecimalFormat formatstring = new DecimalFormat(" ###.##");
		//  "HEIGHT -2.5 VELOCITY -7.5 FUEL 200" string will appear like this
		String state = "HEIGHT " + formatstring.format(height) + " VELOCITY " + formatstring.format(velocity) + " FUEL " + formatstring.format(fuel);
		return state;
	}
	//this method 
    private void nextHeight(double deltaTime) throws RocketException
	{
        height += (velocity * deltaTime);
        if (reachedSurface()) 
		{
            if (velocity < safeVelocity) 
	
			{
                /* throw crashed exception */
				throw crashed;
            } 
			else 
			{
                /* throw landed exception */
				throw landed;            
			}
        }
    }
	//this function returns true if rocket is at or below the planet's surface */
    private boolean reachedSurface() 
	{
		if(height > planet.getGround()) 
		{
			return false;
		}
		return true;
    }
	//landed returns a boolean indicating whether or not the rocket landed safely
	private boolean landed()
	{
		if(reachedSurface() && velocity>safeVelocity)
		{
			return true; //The rocket has landed safely if it has reached the surface and the velocity is greater than safeVelocity
		}
		return false;	
		
	}
	//this function computes and stores the remaining fuel with "fuel(t) = fuel(t - dt) - (burnRate*dt)"
	private void nextFuel(double burnRate, double dt)
	{
		fuel-= (burnRate*dt);
	}
	//This method computes the approximate velocity of a rocket as it falls to the surface
    private void nextVelocity(double burnRate, double deltaTime) 
	{
        velocity += ((engineStrength * burnRate) - planet.getGravity()) * deltaTime;
    }
	//This method updates the height, fuel, and velocity, in order to determine where the rocket is.
    public void move(double dt, double burnRate) throws RocketException
	{
        /* note that dt is measured in seconds */
        if (!reachedSurface()) 
		{
			//Enough Fuel
			if(fuel>=(burnRate*dt)) 
			{
				nextVelocity(burnRate, dt);
				nextFuel(burnRate, dt);
			}
			//The rocket may not have enough fuel left to be able to burn at the specified burn rate for all of dt. If there isn't enough fuel, this method 			//should limit the burn rate so that the available fuel is exactly used up during the interval dt.
			else 
			{
				nextVelocity((fuel/dt), dt);
				nextFuel((fuel/dt), dt);
			}
			nextHeight(dt);
            /* update the height, velocity and fuel */
        }

    }

  

}
