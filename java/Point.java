/**
 * Class representing a point on the Map, which has a x-value and a y-value.
 */
public class Point {
    private int x;
    private int y;

    /**
     * Default Ctor, initialize point as (0,0).
     */
    public Point() {
        this(0, 0);
    }

    /**
     * Initializes the point as (x,y).
     *
     * @param x x-value of point.
     * @param y y-value of point.
     */
    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    /**
     * @return the x value of the point.
     */
    public int getX() {
        return x;
    }

    /**
     * @return the y value of the point.
     */
    public int getY() {
        return y;
    }

    /**
     * Convenience method.
     *
     * @param x x-value to be checked.
     * @param y y-value to be checked.
     * @return true if the values are equal to the values of the point, otherwise false.
     */
    public boolean isEqual(int x, int y) {
        return this.x == x && this.y == y;
    }

    /**
     * @param other other point to compare.
     * @return true if the points are equal, otherwise false.
     */
    public boolean isEqual(Point other) {
        return isEqual(other.getX(), other.getY());
    }
}
