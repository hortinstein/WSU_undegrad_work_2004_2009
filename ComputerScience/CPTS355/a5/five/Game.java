//To compiles javac Planet.java Rocket.java RocketException.java Game.java

import java.io.*;

class Game {
    private static final double noBurn = 0.0;

    private static final double fullBurn = 1.0;

    private static final double deltaTime = 0.5;

    private static void play(Rocket rocket) throws RocketException 
	{
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        while (true) 
		{
			try
			{
				/* read input and decide whether to burn or not */
				String inputstring = input.readLine();
					
				if(inputstring.equals("b"))
				{
					rocket.move(deltaTime, fullBurn); // move rocket for 0.5 second at full burn
				}
				else if(inputstring.equals("")) 
				{
					rocket.move(deltaTime, noBurn); // move rocket for 0.5 second at no burn
				} 
			    System.out.println(rocket.getHeightString());
			}
			catch(IOException e) 
			{
				System.out.println(e);
			}        
		}

    }

    public static void main(String[] args) {
        /* create a planet with gravity 0.3 and surface at 0.0 */
		Planet pluto = new Planet(0.3, 0.0, "pluto");        
		/* create a rocket with engine strength 2.0, 20.0 units of fuel */
        Rocket rocket = new Rocket(2.0, 20.0, pluto);
        rocket.setHeight(50.0);
        try {
            play(rocket);
        } catch (RocketException v) {
            System.out.println(v.getMessage());
        }
    }

} // end of Game class
