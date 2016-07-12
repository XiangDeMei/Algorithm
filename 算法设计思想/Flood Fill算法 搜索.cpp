//http://dsqiu.iteye.com/blog/1689130
//Recursive 4-way floodfill, crashes if recursion stack is full 
void floodFill4(int x, int y, int newColor, int oldColor) 
{ 
    if(x >= 0 && x < w && y >= 0 && y < h && screenBuffer[x][y] == oldColor && screenBuffer[x][y] != newColor) 
    { 
        screenBuffer[x][y] = newColor; //set color before starting recursion
        
        floodFill4(x + 1, y,     newColor, oldColor);
        floodFill4(x - 1, y,     newColor, oldColor);
        floodFill4(x,     y + 1, newColor, oldColor);
        floodFill4(x,     y - 1, newColor, oldColor);
    }     
}