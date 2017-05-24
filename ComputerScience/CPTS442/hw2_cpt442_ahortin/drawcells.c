extern void setCell(int x, int y, double r, double g, double b);

/* drawCells -- draws the desired pattern using (only) setCell() calls */
void drawCells(void)
{
    int i,i2;

    /* draw a square */
    for (i = 0; i <= 30; i++) {
        for (i2 = 0; i2<=30;i2++){        
            setCell(i, i2, .04*i, .03*i2, .02*i);
        }
    }
    for (i = 0; i<=6;i++){    
        setCell(i, 0, 1, 1, 0);
        setCell(i, 6, 1, 1, 0);
        setCell(0, i, 1, 1, 0);
        setCell(6, i, 1, 1, 0);
        
        }
    setCell(2, 4, 1, 1, 0);
    setCell(4, 4, 1, 1, 0);
    setCell(2, 2, 1, 1, 0);
    setCell(3, 2, 1, 0, 0);
    setCell(4, 2, 1, 1, 0);
    setCell(2, 2, 1, 0, 0);
}
