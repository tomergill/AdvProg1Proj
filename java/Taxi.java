import javafx.scene.image.Image;

/**
 * Class representing a single Taxi, which has an id, a location (point) and an image.
 */
public class Taxi {
    private int id;
    private Point location;
    private Image image;

    private static int numOfTaxies = 0;
    private static final int taxiImagesTypes = 4;

    /**
     * Ctor which initializes the taxi with an id, places it in (0, 0) and provides it an image.
     *
     * @param id the id for the new taxi.
     */
    public Taxi(int id) {
        this.id = id;
        this.location = new Point();
        image = new Image("./resources/taxi" + (numOfTaxies++ % taxiImagesTypes) + ".png");
    }

    private Taxi(int id, Point p, Image i) {
        this.id = id;
        this.location = p;
        this.image = i;
    }

    /**
     * @return the id of the Taxi.
     */
    public int getId() {
        return id;
    }

    /**
     * @return the image of the new Taxi.
     */
    public Image getImage() {
        return image;
    }

    /**
     * @return the location of the taxi.
     */
    public Point getLocation() {
        return location;
    }

    /**
     * Sets the location of the cab.
     *
     * @param location the new location.
     */
    public void setLocation(Point location) {
        this.location = location;
    }

    /**
     * Convenience method.
     * Sets the location of the cab.
     *
     * @param x x-values of the new location.
     * @param y y-values of the new location.
     */
    public void setLocation(int x, int y) {
        setLocation(new Point(x, y));
    }

    /**
     * Convenience method.
     *
     * @return the x-value of the location of the taxi.
     */
    public int getX() {
        return location.getX();
    }

    /**
     * Convenience method.
     *
     * @return the y-value of the location of the taxi.
     */
    public int getY() {
        return location.getY();
    }

    /**
     * @param id id to check.
     * @return true if id is the same, otherwise false.
     */
    public boolean isEqual(int id) {
        return this.id == id;
    }

    /**
     * @param other other taxi to compare.
     * @return True if the taxies ar equal, otherwise false.
     */
    public boolean isEqual(Taxi other) {
        return isEqual(other.getId());
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        return new Taxi(this.id, this.location, this.image);
    }
}
