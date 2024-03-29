/*
 * Copyright (c) 1995, 1996 Sun Microsystems, Inc. All Rights Reserved.
 *
 * Permission to use, copy, modify, and distribute this software
 * and its documentation for NON-COMMERCIAL purposes and without
 * fee is hereby granted provided that this copyright notice
 * appears in all copies. Please refer to the file "copyright.html"
 * for further important copyright and licensing information.
 *
 * SUN MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, OR NON-INFRINGEMENT. SUN SHALL NOT BE LIABLE FOR
 * ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR
 * DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */
import java.awt.*;
import java.applet.Applet;
/*
 * This applet animates graphics that it generates. This example eliminates
 * flashing by overriding the update() method. For the graphics this example
 * generates, overriding update() isn't quite good enough -- on some systems,
 * you can still see a crawling effect.
 */
import java.awt.event.*;//for the mouse

public class GameApplet extends Applet implements Runnable, MouseListener {
    int frameNumber = -1;
    int delay;
    Thread animatorThread;
    boolean updirection = false;
    boolean reachedSurface = false;
    boolean landed = false;
    String landedMessage = "Safely on the ground";
    String crashedMessage = "Reduced to a rubble of bits";
    Image myImage;
    Image myImageLander;
    Image myImageLanderB;
    Rocket herrosoviets;
    private static final double noBurn = 0.0;
    private static final double fullBurn = 1.0;

    int squareSize = 20;
    boolean fillColumnTop = true;

    public void init() {
        // Initialize the rocket and planet

        String str;
        int fps = 10;
        /* make a planet named Pluto with gravity 0.3 and surface 0.0 */
        Planet pluto = new Planet(0.2, 0.0, "pluto");  // Change this to correct constructor

        myImage = getImage(getCodeBase(), "landscape.gif");
        myImageLander = getImage(getCodeBase(), "lander.gif");
        myImageLanderB = getImage(getCodeBase(), "landerburned.gif");
        // How many milliseconds between frames?
        str = getParameter("fps");
        try {
            if (str != null) {
                fps = Integer.parseInt(str);
            }
        } catch (Exception e) {
        }
        /* calculate the inter-frame time (in milliseconds) */
        delay = (fps > 0) ? (1000 / fps) : 100;

        // How many pixels wide is each square?
        str = getParameter("squareWidth");
        try {
            if (str != null) {
                squareSize = Integer.parseInt(str);
            }
        } catch (Exception e) {
        }
        /* create a rocket */
		herrosoviets = new Rocket(2.0, 20.0, pluto);
		herrosoviets.setHeight(200);
		
		addMouseListener(this);
    }

    public void start() {
        // Start animating!
        if (animatorThread == null) {
            animatorThread = new Thread(this);
        }
        animatorThread.start();
    }

    public void stop() {
        // Stop the animating thread.
        animatorThread = null;
    }
	public void mouseClicked(MouseEvent me)
	{
		//here to complete the override
	}	
	public void mouseEntered(MouseEvent me)
	{
		//here to complete the override
	}	
	public void mouseExited(MouseEvent me)
	{
		//here to complete the override
	}
	public void mousePressed(MouseEvent me)
	{
		updirection = true;
	}
	
	public void mouseReleased(MouseEvent me)
	{
		updirection = false;
	}

    public void run() {
        // Just to be nice, lower this thread's priority
        // so it can't interfere with other processing going on.
        Thread.currentThread().setPriority(Thread.MIN_PRIORITY);

        // Remember the starting time
        long startTime = System.currentTimeMillis();

        // This is the animation loop.
        while (Thread.currentThread() == animatorThread) {
            // Advance the animation frame.
            try {
					if(updirection) {
					herrosoviets.move(delay/100, fullBurn);
				}
				else {
					herrosoviets.move(delay/100, noBurn);
				}
                /*
                 * note: delay is in milliSeconds but the dt parameter of
                 * Rocket.move is in seconds. Compensate accordingly.
                 */
                /* ... execute a Rocket.move ... */
            } catch (RocketException e) {
            }

            // Display it.
            repaint();

            // Delay depending on how far we are behind.
            try 
			{
                startTime += delay;
                Thread.sleep(Math
                        .max(0, startTime - System.currentTimeMillis()));
            } 
			catch (InterruptedException e) 
			{                
                repaint();
                break;
            }
			//check to see if rocket has landed
			if(herrosoviets.getHeight() <= herrosoviets.getPlanetGround()) 
			{
				reachedSurface = true;
				if(herrosoviets.getVelocity()>herrosoviets.getSafeVelocity()) 
				{
					landed = true;
				}
			}
        }
    }

    public void paint(Graphics g) {
        update(g);
    }

    public void update(Graphics g) {
        g.setColor(Color.white);
        if (reachedSurface) {
            g.drawImage(myImage, 0, 0, this);
            g.drawImage(myImageLander, 300, 350 - (int) herrosoviets.getHeight(), this);
            if (landed)
                g.drawString(landedMessage, 50, 50);
            else
                g.drawString(crashedMessage, 50, 50);
            stop();
        } else {
            g.drawImage(myImage, 0, 0, this);
            if (updirection)
                g.drawImage(myImageLanderB, 300, 355 - (int) herrosoviets.getHeight(),
                        this);
            else
                g.drawImage(myImageLander, 300, 355 - (int) herrosoviets.getHeight(),
                        this);
        }
        g.drawString(herrosoviets.getState(), 10, 20);
    }
}
